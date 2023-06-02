import re

def identify_language(text):
    regex_english = r'^[A-Za-z\s]+$'
    regex_spanish = r'^[A-Za-zÁÉÍÓÚáéíóúÑñ\s]+$'
    regex_french = r'^[A-Za-zÀÂÆÇÉÈÊËÎÏÔŒÙÛÜÿàâæçéèêëîïôœùûü\s]+$'

    if re.match(regex_english, text):
        return "English"
    elif re.match(regex_spanish, text):
        return "Spanish"
    elif re.match(regex_french, text):
        return "French"
    else:
        return "Unknown"

text = input("Enter some text: ")
language = identify_language(text)
print("Identified language:", language)