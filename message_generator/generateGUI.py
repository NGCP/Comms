"""
Author: Michael Wallace
Project: Python 3+ Tkinter GUI for code generation of NGCP project
         which is a simple message queue communication protocol.
         GUI will allow:
                Selection of native code file location path
                Selection of output file location for c++ code
                Selection of output file location for c# wrapper code
                Generate Button or 'Enter' key will generates code based off location paths
                    Error Messages and Completion messages 
                Default file location from XML file
                Checkbox to set same ouput for cpp and csharp code
Date: 2-5-16
"""
import sys #check what version ptyhon 2 & 3 header files differ. This is not needed for CS 375, but is useful for project

#prevent compiled files being created
sys.dont_write_bytecode = True

from generate.generate_comnet import *
from generate.generate_com_wrapper import *    

if(sys.version_info >= (3,0)):
    from tkinter import Tk, Frame, BOTH, filedialog, messagebox, Entry, E, S, W, END, Button, Label, Checkbutton, BooleanVar
else:
    from Tkinter import Tk, Frame, BOTH, Entry, E, S ,W, END, Button, Label, Checkbutton, BooleanVar
    import tkFileDialog as filedialog
    import tkMessageBox as messagebox
    
import xml.etree.ElementTree as ET


class GenerateGui(Frame):


    def __init__(self, parent):
        #constructor
        Frame.__init__(self, parent)
        self.parent = parent
        self.initUI()        
        
    def initUI(self):
        #basic initialization of window frame    
        self.parent.title("Message Generator")
        self.pack(fill = BOTH, expand = True)
        self.centerWindow(500,200)
        
        
        try:
            tree = ET.parse("message_definition.xml").getroot()
            for paths in tree.find('paths'):
                defaultCppOuputText = paths.get("cppPath")
                defaultCsharpWrapperText = paths.get("csharpPath")
                defaultNativeText = paths.get("nativePath")
        except:    
            messagebox.showerror("Missing", "message_definition.xml not found!") 
        
            defaultCppOuputText = "../comnet"
            defaultCsharpWrapperText = "../comwrapper"
            defaultNativeText = "../native"
        
        padSize = 12        
        
        #lets column 2 span
        self.columnconfigure(2, weight = 1)
                
        #cpp file stuff
        cppOutputLabel = Label(self, text = "C++ ouput folder:", font = "Times 12 bold")
        cppOutputLabel.grid(row = 0, column = 0, padx = padSize, pady = padSize, sticky = W)        
        cppOutputEntry = Entry(self)
        cppOutputEntry.grid(row = 0, column = 2, columnspan = 4,  padx =padSize, pady = padSize, sticky = W + E)
        cppOutputEntry.insert(0, defaultCppOuputText)        
        cppButtonEntry = Button(self, text = "...", command = lambda : self.getPath(cppOutputEntry))
        cppButtonEntry.grid(row = 0, column = 5, padx = padSize, pady = padSize, sticky = E)
                
        #csharp file stuff
        csharpOutputLabel = Label(self, text = "C# wrapper output folder:", font = "Times 12 bold")
        csharpOutputLabel.grid(row = 1, column = 0, padx = padSize, pady = padSize, sticky = W)        
        csharpOutputEntry = Entry(self)
        csharpOutputEntry.grid(row = 1, column = 2, columnspan = 4,  padx =padSize, pady = padSize, sticky = W + E)
        csharpOutputEntry.insert(0, defaultCsharpWrapperText)        
        csharpButtonEntry = Button(self, text = "...", command = lambda : self.getPath(csharpOutputEntry))
        csharpButtonEntry.grid(row = 1, column = 5, padx = padSize, pady = padSize, sticky = E)


        #native file stuff
        nativeFileLabel = Label(self, text = "Native files folder input folder:", font = "Times 12 bold")               
        nativeFileLabel.grid(row = 3, column = 0, padx = padSize, pady = padSize, sticky = W)        
        nativeFileEntry = Entry(self)
        nativeFileEntry.grid(row = 3, column = 2, columnspan = 4,  padx =padSize, pady = padSize, sticky = W + E)
        nativeFileEntry.insert(0, defaultNativeText)        
        nativeFileButtonEntry = Button(self, text = "...", command = lambda : self.getPath(nativeFileEntry))
        nativeFileButtonEntry.grid(row = 3, column = 5, padx = padSize, pady = padSize, sticky = E)

        #same out put directory
        self.var = BooleanVar()
        cb = Checkbutton(self, text = "C++ and C# same output", variable = self.var, command = lambda : self.onCheck(cppOutputEntry, csharpOutputEntry, defaultCsharpWrapperText))
        cb.grid(row = 4, column = 0, padx = padSize, pady = padSize, sticky = W)
                
        #generate documents button
        generateButton = Button(self, text = "Generate", font = "Times 12 bold", command = lambda : self.generate(cppOutputEntry, csharpOutputEntry, nativeFileEntry, self.var.get()), width = 40)        
        generateButton.grid(row =4, column = 2, columnspan = 4, padx = padSize, pady = padSize, sticky = S)
        self.parent.bind('<Return>', lambda someRandomValueNotSureWhyThisMustBeHere : self.generate(cppOutputEntry, csharpOutputEntry, nativeFileEntry, self.var.get()))
        
        
    def centerWindow(self, sizeWidth, sizeHeight):
        #define center window method which finds size of screen and 
        #creates window location based of screen and program window size
        screenWidth = self.parent.winfo_screenwidth()
        screenHeight = self.parent.winfo_screenheight()
        startX = (screenWidth - sizeWidth) / 2
        startY = (screenHeight - sizeHeight) / 2
        self.parent.geometry('%dx%d+%d+%d' % ( sizeWidth,sizeHeight, startX, startY))
    
    def getPath(self, outputEntry):        
        #gets path of folder location for directory
        outputEntry.delete(0, END)
        path = filedialog.askdirectory() 
        outputEntry.insert(0, path)
        
    def onCheck(self,cppOutputEntry, csharpOutputEntry, defaultCsharpWrapperText):
        #check button to maek output of CPP and CSharp the same
        if self.var.get() == True:
            csharpOutputEntry.delete(0, END)
            csharpOutputEntry.insert(0, cppOutputEntry.get())
        else:
            csharpOutputEntry.delete(0, END)
            csharpOutputEntry.insert(0, defaultCsharpWrapperText)
    
    def generate(self, cppOutputEntry, csharpOutputEntry, nativeInputEntry, checkBoxBool):
        #call message generation code here which is too long to include
        if(cppOutputEntry.get() == ""):
            messagebox.showerror("Error", "Missing path for C++ output directory")
        elif(csharpOutputEntry.get() == ""):
            messagebox.showerror("Error", "Missing path for C# output directory")                
        elif(nativeInputEntry.get() == ""):
            messagebox.showerror("Error", "Missing path for native files input directory")    
        else:
            #function calls   
            generate_comnet(cppOutputEntry.get(), ".h", ".cpp", nativeInputEntry.get())
            generate_com_wrapper(csharpOutputEntry.get(), ".h", ".cpp", not checkBoxBool)
            messagebox.showinfo("Success", "Message Generation Complete!")
        
   
def main():
    #define main for creation and looping of tk window     
    root = Tk()
    app = GenerateGui(root)
    root.mainloop()
    
#check if on main file    
if __name__ == '__main__':
    main()
    
