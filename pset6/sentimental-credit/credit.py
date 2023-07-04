from cs50 import get_int
import re

number = get_int("Number: ")  # prompts user for card number
l = str(number)
temp = number
tempo = number
sum = 0
i = 0
j = 0

while (temp > 1):  # checks that the number has not reached its end
    temp = temp / 10
    i = int(temp % 10)  # gets the number next to last
    i *= 2  # doubles it
    temp = temp / 10
    if i >= 10:
        j = int(i % 10)
        i = i / 10
        sum += int(i + j)
    else:
        sum += i

while (tempo > 1):  # checks that the number has not reached its end
    i = int(tempo % 10)
    tempo = tempo / 100
    sum += int(i)

if sum % 10 == 0:  # checks Luhn's Algorithm
    if l[0] == "4" and len(l) == 16:
        print("VISA")
    elif l[0] == "3" and len(l) == 15:
        if l[1] == "4" or l[1] == "7":
            print("AMEX")
    elif l[0] == "5" and len(l) == 16 and number / 100000000000000 < 56:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")