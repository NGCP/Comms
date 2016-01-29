
def check_valid_type(type_string):
    """
    Checks if the variable  has a valid data type
    If variable type is valid it will return 1
    If variable type is not listed it will not be valid and return 0
    Function is used to validate data types from xml file for automated message generation
    """
    return {
        'uint8_t': 1,
        'uint16_t': 1,
        'uint32_t': 1,
        'int8_t': 1,
        'int16_t': 1,
        'int32_t': 1,
        'float32_t': 1,
        'float64_t': 1,
        'int32_t': 1,
        'string': 1,
        }.get(type_string, 0) 