from cs50 import get_int

# Prompt the user for the height
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

# Generate the half-pyramids
for i in range(height):
    # Print spaces on the left side of the first half-pyramid
    for j in range(height - i - 1):
        print(" ", end="")

    # Print hashes for the first half-pyramid
    for j in range(i + 1):
        print("#", end="")

    # Print the gap between the half-pyramids
    print("  ", end="")

    # Print hashes for the second half-pyramid
    for j in range(i + 1):
        print("#", end="")

    # Move to the next line
    print()
