#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Tell us your name please: ");
    printf("hello, %s\n", name);
}
