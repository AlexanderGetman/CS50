#include <cs50.h>
#include <stdio.h>

int get_height(string prompt);
void build_pyramid(int size);

int main(void)
{
    int h = get_height("Height: ");
    build_pyramid(h);
}

void build_pyramid(int size)
{
    for (int lines = 1; lines <= size; lines++)
    {
        for (int spaces = size - lines; spaces > 0; spaces--)
        {
            printf(" ");
        }

        for (int hashes_front = 0; hashes_front < lines; hashes_front++)
        {
            printf("#");
        }

        printf("  ");

        for (int hashes_back = 0; hashes_back < lines; hashes_back++)
        {
            printf("#");
        }

        printf("\n");
    }
}

int get_height(string prompt)
{
    int height;
    do
    {
        height = get_int("%s", prompt);
    }
    while (height > 8 || height <= 0);
    return height;
}
