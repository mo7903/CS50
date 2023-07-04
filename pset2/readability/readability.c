#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    float lets = 0;
    float words = 0;
    float sets = 0;
    double x = 0;
    double s = 0;
    double l = 0;
    char temp;

    string text = get_string("Text: "); //asks the user for text and stores it in a string
    do //counts the sentences and stores the count
    {
        for (int k = 0, n = strlen(text); k <= n; k++) //helps examine each charachter
        {
            temp = text[k];
            if (temp == '.' || temp == '!' || temp == '?')
            {
                sets ++;
            }
            else
            {
            }
        }

    }
    while (temp != '\0');
    do //counts the letters and stores the count
    {
        for (int j = 0, o = strlen(text); j <= o; j++) //helps examine each charachter
        {
            temp = text[j];
            if (isalpha(temp) != 0)
            {
                lets ++;
            }
            else
            {
            }
        }

    }
    while (temp != '\0');
    do //counts the words and stores the count
    {
        for (int v = 0, u = strlen(text); v <= u; v++) //helps examine each charachter
        {
            temp = text[v];
            if (isspace(temp) != 0)
            {
                words ++;
            }
            else
            {
            }
        }

    }
    while (temp != '\0');
    words++;
    l = lets * 100 / words;
    s = sets * 100 / words;
    x = 0.0588 * l - 0.296 * s - 15.8; //calculates the Coleman-Liau index to determine which grade the text falls into
    if (x < 1) // prints back to the user the grade of the text
    {
        printf("Before Grade 1\n");
    }
    else if (x > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)round(x));
    }
}