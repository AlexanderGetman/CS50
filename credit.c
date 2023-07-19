#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int get_card_length(long card);
int check_length(int length);
int check_luhns_algorithm(long card);
void split_number_to_digits(int number, int *digit1, int *digit2);
int get_first_two_digits(long number);
int check_credit_card_company(int first_two_numbers);

int main(void)
{
    long number = get_long("Input your card number: ");
    int length = get_card_length(number);
    int result;

    result = check_length(length);
    if (result == 0) {
        printf("INVALID\n");
        exit(0);
    }

    result = check_luhns_algorithm(number);
    if (result == 0) {
        printf("INVALID\n");
        exit(0);
    }

    int first_two_numbers = get_first_two_digits(number);
    result = check_credit_card_company(first_two_numbers);

    result = check_credit_card_company(first_two_numbers);
    if (result == 1)
    {
        printf("AMEX\n");
    } else if (result == 2)
    {
        printf("MASTERCARD\n");
    } else if (result == 3)
    {
        printf("VISA\n");
    } else
    {
        printf("INVALID\n");
    }
}

int get_card_length(long card)
{
    int length = 1;
    long card_number = card;
    do
    {
        length++;
        card_number /= 10;
    }
    while (card_number > 10);
    return length;
}

int check_length(int length)
{
    if (length != 13 && length != 15 && length != 16)
    {
        return 0;
    } return 1;
}

int check_luhns_algorithm(long card)
{
    long card_number = card;
    int sum1 = 0;
    int sum2 = 0;
    int digit1, digit2, result;

    do
    {
        sum1 = card_number % 10 + sum1;
        card_number /= 10;

        split_number_to_digits(card_number % 10 * 2, &digit1, &digit2);
        sum2 = digit1 + digit2 + sum2;
        card_number /= 10;
    }
    while (card_number > 0);

    result = sum1 + sum2;
    if (result % 10 != 0)
    {
        return 0;
    }
    return 1;
}

void split_number_to_digits(int number, int *digit1, int *digit2)
{
    *digit1 = number / 10;
    *digit2 = number % 10;
}

int get_first_two_digits(long number)
{
    int first_two_digits;
    long card_number = number;
    do
    {
        card_number /= 10;
    }
    while(card_number > 100);
    first_two_digits = card_number;
    return first_two_digits;
}

int check_credit_card_company(int first_two_numbers)
{
    if (first_two_numbers == 34 || first_two_numbers == 37)
    {
        return 1;
    } else if (first_two_numbers >= 51 && first_two_numbers <= 55)
    {
        return 2;
    } else if (first_two_numbers >= 40 && first_two_numbers <= 49)
    {
        return 3;
    } else
    {
        return 0;
    }
}