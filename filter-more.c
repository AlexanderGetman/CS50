#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        int half_width = width / 2;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < half_width; j++)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp;
            }
        }
    }

    if (width % 2 != 0)
    {
        int half_width = (width - 1) / 2;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < half_width; j++)
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average_r = 0;
            float average_g = 0;
            float average_b = 0;
            float counter = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + y < 0 || i + y > width - 1)
                    {
                        continue;
                    }

                    if (j + x < 0 || j + x > width - 1)
                    {
                        continue;
                    }

                    average_r += image[i + y][j + x].rgbtRed;
                    average_g += image[i + y][j + x].rgbtGreen;
                    average_b += image[i + y][j + x].rgbtBlue;
                    counter++;
                }
            }
            temp[i][j].rgbtRed = round(average_r / counter);
            temp[i][j].rgbtGreen = round(average_g / counter);
            temp[i][j].rgbtBlue = round(average_b / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxr = 0, gxg = 0, gxb = 0;
            int gyr = 0, gyg = 0, gyb = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + y < 0 || i + y > width - 1)
                    {
                        continue;
                    }

                    if (j + x < 0 || j + x > width - 1)
                    {
                        continue;
                    }

                    gxr += image[i + y][j + x].rgbtRed * gx[y + 1][x + 1];
                    gxg += image[i + y][j + x].rgbtGreen * gx[y + 1][x + 1];
                    gxb += image[i + y][j + x].rgbtBlue * gx[y + 1][x + 1];

                    gyr += image[i + y][j + x].rgbtRed * gy[y + 1][x + 1];
                    gyg += image[i + y][j + x].rgbtGreen * gy[y + 1][x + 1];
                    gyb += image[i + y][j + x].rgbtBlue * gy[y + 1][x + 1];
                }
            }

            temp[i][j].rgbtRed = fmin(round(sqrt(gxr * gxr + gyr *gyr)), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt(gxg * gxg + gyg *gyg)), 255);;
            temp[i][j].rgbtBlue = fmin(round(sqrt(gxb * gxb + gyb *gyb)), 255);;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
