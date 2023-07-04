import csv
import sys


def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py database sequence")
        return 1

    with open(sys.argv[1]) as f:  # opens the database file into a list
        database = list(csv.reader(f))

    with open(sys.argv[2]) as f:  # opens the sequence file for reading
        sequence = f.read()

    STR = []
    for subsequence in database[0]:
        if subsequence.isupper():
            STR.append(longest_match(sequence, subsequence))  # writes to the list the number of longest STRs found

    for row in database:  # iterates over every row in the database
        n = 0
        for i in range(len(STR)):  # iterates over every column corresponding to a different STR
            if row[i + 1] == str(STR[i]):  # compares the numbers in database and the results in the sequence
                n += 1
        if n == len(STR):
            match = row[0]
            break  # stops iterating once a match is found
    if n == len(STR):
        print(match)  # prints the name of the matched DNA if found
    else:
        print("No Match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
