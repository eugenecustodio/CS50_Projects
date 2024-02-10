#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    // Prompt user for pyramid's height and validate input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Build and print the pyramids
    for (int row = 0; row < height; row++)
    {
        // Print spaces for left pyramid
        for (int space = height - row - 1; space > 0; space--)
        {
            printf(" ");
        }

        // Print left pyramid
        for (int hash = 0; hash <= row; hash++)
        {
            printf("#");
        }

        // Print gap between pyramids
        printf("  ");

        // Print right pyramid
        for (int hash = 0; hash <= row; hash++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
