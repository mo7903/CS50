from cs50 import get_string
import string

i = 0
words = 1
letters = 0
sentences = 0
L = 0
S = 0
index = 0
text = get_string("Text: ").  # prompts user for text

for i in range(len(text)):  # iterates over every character in the string of text
    if text[i].isalpha():  # counts every letter
        letters += 1
    if text[i].isspace():  # counts every space to be a new word
        words += 1
    if text[i] == "." or text[i] == "!" or text[i] == "?":  # counts every end-punctuation to mark sentences
        sentences += 1

L = 100 * (letters / words)
S = 100 * (sentences / words)
index = 0.0588 * L - 0.296 * S - 15.8.  # calculates the Coleman-Liau index using the collected statistics of the text

if index > 16:  # checks the index and prints the grade level of readability to the user
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {int(round(index))}")