card_number = input("Number: ")

number_length = len(card_number)

def main():
    if number_length != 13 and number_length != 15 and number_length != 16:
        print("INVALID")
        return
    if check_luhns_algorithm(card_number) % 10 != 0:
        print("INVALID")
        return

    first_two_digits = int(card_number[:2])

    if first_two_digits == 34 or first_two_digits == 37:
        print("AMEX")
        return
    elif first_two_digits >= 51 and first_two_digits <= 55:
        print("MASTERCARD")
    elif first_two_digits >= 40 and first_two_digits <= 49:
        print("VISA")
        return
    else:
        print("INVALID")
        return

def check_luhns_algorithm(card_number):
    card_number = card_number[::-1]
    other_digits = card_number[::2]
    every_other_digit = card_number[1::2]
    sum_1 = 0
    sum_2 = sum(int(digit) for digit in other_digits)
    for digit in every_other_digit:
        i = int(digit) * 2
        if i >= 10:
            i = str(i)
            i = int(i[0]) + int(i[1])
        sum_1 += i
    return sum_1 + sum_2

main()