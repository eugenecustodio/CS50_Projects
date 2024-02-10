import csv
import sys

def main():
    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read command-line arguments
    csv_file = sys.argv[1]
    sequence_file = sys.argv[2]

    # Read the CSV file into memory
    database = read_csv(csv_file)
    if not database:
        return

    # Read the DNA sequence into memory
    sequence = read_sequence(sequence_file)
    if not sequence:
        return

    # Compute the STR counts in the DNA sequence
    str_counts = compute_str_counts(sequence, database[0][1:])

    # Find a match in the database
    match = find_match(str_counts, database)
    if match:
        print(match)
    else:
        print("No match")

def read_csv(filename):
    try:
        with open(filename, "r") as file:
            reader = csv.reader(file)
            return [row for row in reader]
    except FileNotFoundError:
        print(f"Could not open file: {filename}")
        return None

def read_sequence(filename):
    try:
        with open(filename, "r") as file:
            return file.read().strip()
    except FileNotFoundError:
        print(f"Could not open file: {filename}")
        return None

def compute_str_counts(sequence, strs):
    counts = {}
    for str in strs:
        counts[str] = longest_match(sequence, str)
    return counts

def longest_match(sequence, str):
    longest = 0
    current = 0
    length = len(str)

    i = 0
    while i < len(sequence):
        # Check if the current substring matches the STR
        if sequence[i:i+length] == str:
            current += 1

            # Update the longest run
            if current > longest:
                longest = current

            i += length
        else:
            current = 0
            i += 1

    return longest

def find_match(str_counts, database):
    for row in database[1:]:
        name = row[0]
        counts = {str: int(count) for str, count in zip(database[0][1:], row[1:])}

        # Check if the STR counts match
        if counts == str_counts:
            return name

    return None

if __name__ == "__main__":
    main()
