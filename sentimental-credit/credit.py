from cs50 import get_string

def main():
    # Prompt user for credit card number
    card_number = get_string("Number: ")

    # Perform Luhn's Algorithm
    checksum = calculate_checksum(card_number)
    if checksum % 10 != 0:
        print("INVALID")
        return

    # Check card type
    card_length = len(card_number)
    if card_length == 15 and card_number[0] == "3" and (card_number[1] == "4" or card_number[1] == "7"):
        print("AMEX")
    elif card_length == 16 and card_number[0] == "5" and int(card_number[1]) in range(1, 6):
        print("MASTERCARD")
    elif (card_length == 13 or card_length == 16) and card_number[0] == "4":
        print("VISA")
    else:
        print("INVALID")

def calculate_checksum(card_number):
    total = 0
    for i in range(len(card_number)-2, -1, -2):
        digit = int(card_number[i]) * 2
        if digit > 9:
            digit = digit // 10 + digit % 10
        total += digit
    for i in range(len(card_number)-1, -1, -2):
        total += int(card_number[i])
    return total

if __name__ == "__main__":
    main()
