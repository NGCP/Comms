"""
Native will copy all files in parameter 'source_directory' of defined type 
which is listed under variable 'ACCEPTABLE_FILE_TYPES'
which is currently .cpp .h .txt
all files would be put is parameter 'destination_directory'
"""
import shutil
import os

#used to copy files from only the following types
#avoid copying index files from OS
ACCEPTABLE_FILE_TYPES = ('.cpp', '.h', '.txt')


def generate_native(directory):
    """
    Function will copy all files in "native/src/" and "native/include"
    to directory/include & directory/src/
    """   
    copyFiles("native/src/", directory + "src/")
    copyFiles("native/include/", directory + "include/")


def copyFiles(source_directory, destination_directory):
    """
    function just copies source_directory to destination directory
    print copying message
    """
    #check if native folder exists
    if os.path.isdir(source_directory):
        src_files = os.listdir(source_directory)        
        for file_name in src_files:
            full_file_name = os.path.join(source_directory, file_name)        
            if (os.path.isfile(full_file_name)):
                if(full_file_name.endswith((ACCEPTABLE_FILE_TYPES))):
                    print("Copying: " + file_name)
                    shutil.copy(full_file_name, destination_directory)
    else:#native folder not found
        print("Native file directory Not Found: " + source_directory)