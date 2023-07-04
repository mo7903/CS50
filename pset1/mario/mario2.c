#include <stdio.h>
#include <cs50.h>

int main(void)
{
int n;
int m;

    do
    {
    n = get_int("Size = ");

    }
    while (n < 1 || n > 8);


    for (int i = 0; i < n; i++)
    {
        m = n - 1;
        for (int j = 0; j < m; j++)
        {
            printf(" ");
        }
        for(int k = 0; k < m; k++)
        {
            printf("#");

        }
        printf("\n");
    }
}

