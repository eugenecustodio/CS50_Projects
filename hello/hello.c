#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user for their name
    string name = get_string("What's your name? ");

    // Print personalized greeting
    printf("Hello, %s!\n", name);
}
