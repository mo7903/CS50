#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float temp = 0;
    for (int i = 0; i < height; i++) // loops over every pixel
    {
        for (int j = 0; j < width; j++)
        {
            temp = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.00; //calculates avg of RGB
            temp = round(temp);
            image[i][j].rgbtRed = temp; //stores the rounded number into each RGB to get grayscale version
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtBlue = temp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = (0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue); //implements sepia equation to RGB numbers of pixels
            sepiaGreen = (0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue);
            sepiaBlue = (0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue);
            if(sepiaRed < 255) //checks whether the color exceeded max of 255
            {
                image[i][j].rgbtRed = round(sepiaRed);
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if(sepiaGreen < 255)
            {
                image[i][j].rgbtGreen = round(sepiaGreen);
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if(sepiaBlue < 255)
            {
                image[i][j].rgbtBlue = round(sepiaBlue);
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp = image[0][0]; //temp to store opposite
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++) //loops over the image and swaps the right-side pixels with the left-side pixels
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //create temporary image to blur without pixel aberration
    int totRed, totGreen, totBlue;
    float n = 0.00;
    for (int i = 0; i < height; i++) //loops over the entire pixel map of the image
    {
        for (int j = 0; j < width; j++)
        {
            totRed = totGreen = totBlue = 0; //resets n-counter and total color counts
            n = 0.00;
            for (int k = -1; k < 2; k++) //loops over the 3*3 matrix of the pixel
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > (height - 1) || j + l < 0 || j + l > (width - 1)) //checks for present pixels and skips over the wrong pixels
                    {
                        continue;
                    }

                    totRed += image[i + k][j + l].rgbtRed; //adds pixel color to total
                    totGreen += image[i + k][j + l].rgbtGreen;
                    totBlue += image[i + k][j + l].rgbtBlue;

                    n++;
                }

                temp[i][j].rgbtRed = round(totRed / n); //gets avg
                temp[i][j].rgbtGreen = round(totGreen / n);
                temp[i][j].rgbtBlue = round(totBlue / n);
            }
        }
    }
    for (int m = 0; m < height; m++) //copies temp image into original
    {
        for (int o = 0; o < width; o++)
        {
            image[m][o].rgbtRed = temp[m][o].rgbtRed;
            image[m][o].rgbtGreen = temp[m][o].rgbtGreen;
            image[m][o].rgbtBlue = temp[m][o].rgbtBlue;
        }
    }
    return;
}