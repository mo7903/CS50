from cs50 import get_int

h = -1  # assigns h to an initial value that starts the loop
while (1 > h or h > 8):  # constantly prompts the user for an integer height between 1 and 8 inclusive
    h = get_int("Height: ")

for i in range(h):  # prints the pyramid
    print(" " * (h - i - 1), end="")
    print("#" * (i + 1), end="  ")
    print("#" * (i + 1))