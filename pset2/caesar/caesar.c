#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    string plaintext;
    int m = 0;
    char temp;
    int j;
    int key = 0;
    if (argc == 2)
    {
        for (int n = 0; n < strlen(argv[1]); n++)
        {
            if (isdigit(argv[1][n])) // checks whether key is digit
            {
                ;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                m ++; // keeps a numerical note that something is wrong so the process halts if the key is invalid
                n += strlen(argv[1]);
                void exit(int status);
                exit(1);
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        m ++; // keeps a numerical note that something is wrong so the process halts if the key is invalid
        void exit(int status);
        exit(1);
    }
    if (true)
    {
        key = atoi(argv[1]); // stores key into variable if valid
        plaintext = get_string("plaintext: "); // prompts user for plaintext
    }
    else
    {
        void exit(int status);
        exit(1);
    }
    if (plaintext != 0) // checks if there is plaintext to encrypt
    {
        printf("ciphertext: ");
        do
        {
            for (j = 0; j < strlen(plaintext); j++)
            {
                temp = plaintext[j];
                if (isalpha(temp)) //checks whether charachter is alphabetical
                {
                    if (isupper(temp)) // if so it checks whether it's uppercase
                    {
                        temp = (((temp - 64) + key) % 26) + 64; // if so it enters the equation of caesar's encryption
                        printf("%c", temp);
                    }
                    else
                    {
                        temp = (((temp - 96) + key) % 26) + 96;
                        printf("%c", temp);
                    }

                }
                else // prints non-alphabetical charachters with encryption
                {
                    printf("%c", temp);
                }
            }
        }
        while (plaintext[j] != '\0'); // stops the do while loop when the string ends with the \0 char
    }
    else
    {
        void exit(int status);
        exit(1);
    }
    printf("\n"); // prints a new line
}

