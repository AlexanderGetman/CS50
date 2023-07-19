#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_chars(string text);
int count_words(string text);
int count_sentences(string text);
float calculate_readability(float number_of_chars, float number_of_words, float number_of_sentences);

int main(void)
{
    // Get input words from user
    string text = get_string("Text: ");
    int number_of_chars = count_chars(text);
    int number_of_words = count_words(text);
    int number_of_sentences = count_sentences(text);
    float readability = calculate_readability(number_of_chars, number_of_words, number_of_sentences);
    int readability_rounded = round(readability);

    if (readability < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readability > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", readability_rounded);
    }
}

int count_chars(string text)
{
    int length = strlen(text);
    int number_of_chars = 0;

    for (int i = 0; i < length; i++)
    {
        int symbol = text[i];
        if (symbol >= 65 && symbol <= 90)
        {
            number_of_chars++;
        }

        else if (symbol >= 97 && symbol <= 122)
        {
            number_of_chars++;
        }
    }

    return number_of_chars;
}

int count_words(string text)
{
    int length = strlen(text);
    int number_of_words = 1;

    for (int i = 0; i < length; i++)
    {
        int symbol = text[i];
        if (symbol == 32)
        {
            number_of_words++;
        }
    }

    return number_of_words;
}

int count_sentences(string text)
{
    int length = strlen(text);
    int number_of_sentences = 0;

    for (int i = 0; i < length; i++)
    {
        int symbol = text[i];
        if (symbol == 33 || symbol == 46 || symbol == 63)
        {
            number_of_sentences++;
        }
    }

    return number_of_sentences;
}

float calculate_readability(float number_of_chars, float number_of_words, float number_of_sentences)
{
    float average_letters = number_of_chars / number_of_words * 100.00;
    float average_sentences = number_of_sentences / number_of_words * 100.00;

    // Coleman-Liau index formula
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
    return index;
}