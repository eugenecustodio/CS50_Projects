#include <stdio.h>
#include <cs50.h>

int get_digit_sum(int number);
bool is_valid_card(long card_number);
string get_card_type(long card_number);

int main(void)
{
    long card_number = get_long("Number: ");

    if (is_valid_card(card_number))
    {
        string card_type = get_card_type(card_number);
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_digit_sum(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }

    return sum;
}

bool is_valid_card(long card_number)
{
    int sum = 0;
    bool multiply = false;

    while (card_number > 0)
    {
        int digit = card_number % 10;

        if (multiply)
        {
            digit *= 2;
            sum += get_digit_sum(digit);
        }
        else
        {
            sum += digit;
        }

        card_number /= 10;
        multiply = !multiply;
    }

    return sum % 10 == 0;
}

string get_card_type(long card_number)
{
    int first_two_digits = card_number / 10000000000000;
    int first_digit = card_number / 1000000000000000;

    if ((first_two_digits == 34 || first_two_digits == 37) && (first_digit == 0))
    {
        return "AMEX";
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55)
    {
        return "MASTERCARD";
    }
    else if ((first_digit == 4) && (first_two_digits != 49 && first_two_digits != 48 && first_two_digits != 47 && first_two_digits != 46 && first_two_digits != 45))
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}

