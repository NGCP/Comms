import re

def lower_case_acronym(input_string):
    """
    This function converts string to lower case, yet it maintains acronym as upper case
    Ex: 'HelloWorld' returns 'helloworld'
    Ex: 'WTF' returns 'WTF'
    Error: 'hellowWORLD' -> error thrown -> Not fixing because I don't understand the functions purpose.
    """
    regex = re.compile('[A-Z]{2,}')
    output = input_string.lower()
    for match in regex.finditer(input_string):
        output_list = list(input_string.lower())
       
        for x in range(match.start(), match.end()):
            output_list[x] = match.group()[x]
        output = "".join(output_list)
    return output