def main():
    text = input("Text: ")
    letters, words, sentences = count(text)
    index = round(0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def count(text):
    counter_letters = 0
    counter_words = 1
    counter_sentences = 0
    for char in text:
        if char.isalpha():
            counter_letters += 1
        elif char.isspace():
            counter_words += 1
        elif char in ['.', '!', '?']:
            counter_sentences += 1
    return counter_letters, counter_words, counter_sentences

main()