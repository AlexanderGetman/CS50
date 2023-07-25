while True:
    try:
        height = int(input("Height: "))
        if height <= 8 and height > 0:
            break
    except ValueError:
        print("Invalide input. Provide numeric value")

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i  + "  " + "#" * i)