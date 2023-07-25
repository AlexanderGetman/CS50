import csv
import sys


def main():
    # TODO: Check for command-line usage
    try:
        csv_file, txt_file = sys.argv[1], sys.argv[2]
    except:
        print("Provide correct filenames")
        return

    # TODO: Read database file into a variable
    list_of_substrs = []
    database = []
    with open(csv_file, "r") as file:
        reader = csv.reader(file, delimiter = ',')
        for row in reader:
            list_of_substrs = row[1:]
            break

    with open(csv_file, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence = ""
    f = open(txt_file, "r")
    for line in f:
        sequence = line

    # TODO: Find longest match of each STR in DNA sequence
    dna_sequence_matches = {}

    for substr in list_of_substrs:
        dna_sequence_matches[substr] = longest_match(sequence, substr)

    # TODO: Check database for matching profiles
    matches = [str(match) for key,match in dna_sequence_matches.items()]
    for individual in database:
        subseqs = [subseq for key,subseq in individual.items()]
        if matches == subseqs[1:]:
            print(individual['name'])
            return
    print("No match")

    return


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