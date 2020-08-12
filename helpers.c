#include "helpers.h"
#include <math.h>

/*
Hello ! This is the Filter script made for the Problem Set 4 of CS50's Introduction to Computer Science course.
The user should input the key in the command prompt after the ./filter -b, g, r or s (for blur, greyscale, reflect or sepia) images/file.bmp out.bmp (input and output).

The software works as follows :

1 . Get the users input and checks if it's valid
2 . Applies the correct filter to the bmp file
3 . Outputs a new bmp file with the applied filter

Feel free to send any suggestions at contact@arsadevs.com
*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int rgbAvg = round((image[a][b].rgbtGreen + image[a][b].rgbtRed + image[a][b].rgbtBlue) / 3.00);
            image[a][b].rgbtGreen = rgbAvg;
            image[a][b].rgbtRed = rgbAvg;
            image[a][b].rgbtBlue = rgbAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int sepiaR = round(0.393 * image[a][b].rgbtRed + 0.769 * image[a][b].rgbtGreen + 0.189 * image[a][b].rgbtBlue);
            int sepiaG = round(0.349 * image[a][b].rgbtRed + 0.686 * image[a][b].rgbtGreen + 0.168 * image[a][b].rgbtBlue);
            int sepiaB = round(0.272 * image[a][b].rgbtRed + 0.534 * image[a][b].rgbtGreen + 0.131 * image[a][b].rgbtBlue);
            if (sepiaR > 255)
            {
                sepiaR = 255;
            }
            if (sepiaG > 255)
            {
                sepiaG = 255;
            }
            if (sepiaB > 255)
            {
                sepiaB = 255;
            }
            image[a][b].rgbtRed = sepiaR;
            image[a][b].rgbtGreen = sepiaG;
            image[a][b].rgbtBlue = sepiaB;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width / 2; b++)
        {
            RGBTRIPLE *pix1 = &image[a][b];
            RGBTRIPLE *pix2 = &image[a][width - 1 - b];
            RGBTRIPLE tmp = *pix1;
            *pix1 = *pix2;
            *pix2 = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            float counter = 0;
            for (int c = -1; c < 2; c++)
            {
                for (int d = -1; d < 2; d++)
                {
                    if (a + c < 0 || a + c > height - 1 || b + d < 0 || b + d > width - 1)
                    {
                        continue;
                    }
                    sumR += image[a + c][b + d].rgbtRed;
                    sumG += image[a + c][b + d].rgbtGreen;
                    sumB += image[a + c][b + d].rgbtBlue;
                    counter++;
                }
            }
            tmp[a][b].rgbtRed = round(sumR / counter);
            tmp[a][b].rgbtGreen = round(sumG / counter);
            tmp[a][b].rgbtBlue = round(sumB / counter);
            if (tmp[a][b].rgbtRed > 255)
            {
                tmp[a][b].rgbtRed = 255;
            }
            if (tmp[a][b].rgbtGreen > 255)
            {
                tmp[a][b].rgbtGreen = 255;
            }
            if (tmp[a][b].rgbtBlue > 255)
            {
                tmp[a][b].rgbtBlue = 255;
            }
        }
    }
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = tmp[a][b].rgbtRed;
            image[a][b].rgbtGreen = tmp[a][b].rgbtGreen;
            image[a][b].rgbtBlue = tmp[a][b].rgbtBlue;
        }
    }
    return;
}
