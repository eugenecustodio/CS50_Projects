#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of red, green, and blue values
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set red, green, and blue values to the average
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels from the left half with corresponding pixels from the right half
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image
    RGBTRIPLE(*temp)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate over the 3x3 grid centered at the current pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += temp[ni][nj].rgbtRed;
                        sumGreen += temp[ni][nj].rgbtGreen;
                        sumBlue += temp[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate average of red, green, and blue values
            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }

    free(temp);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*temp)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    if (temp == NULL)
    {
        return;
    }

    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    int Gx_red, Gx_green, Gx_blue, Gy_red, Gy_green, Gy_blue;
    int new_red, new_green, new_blue;

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Gx_red = Gx_green = Gx_blue = Gy_red = Gy_green = Gy_blue = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int ni = i + k;
                    int nj = j + l;

                    // Check if the neighboring pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        Gx_red += temp[ni][nj].rgbtRed * Gx[k + 1][l + 1];
                        Gx_green += temp[ni][nj].rgbtGreen * Gx[k + 1][l + 1];
                        Gx_blue += temp[ni][nj].rgbtBlue * Gx[k + 1][l + 1];

                        Gy_red += temp[ni][nj].rgbtRed * Gy[k + 1][l + 1];
                        Gy_green += temp[ni][nj].rgbtGreen * Gy[k + 1][l + 1];
                        Gy_blue += temp[ni][nj].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            new_red = round(sqrt((double)(Gx_red * Gx_red) + (double)(Gy_red * Gy_red)));
            new_green = round(sqrt((double)(Gx_green * Gx_green) + (double)(Gy_green * Gy_green)));
            new_blue = round(sqrt((double)(Gx_blue * Gx_blue) + (double)(Gy_blue * Gy_blue)));

            // Cap the values at 255 if they exceed the maximum
            image[i][j].rgbtRed = (new_red > 255) ? 255 : (unsigned char)new_red;
            image[i][j].rgbtGreen = (new_green > 255) ? 255 : (unsigned char)new_green;
            image[i][j].rgbtBlue = (new_blue > 255) ? 255 : (unsigned char)new_blue;
        }
    }

    free(temp);
}
