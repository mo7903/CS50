#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    int m;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        m = n - i ;
        for (int k = 1; k < m; k++)
        {
            printf(" ");
        }
        printf("#");
        for (int j = 0; j < i; j++)
        {
         printf("#");
        }
        printf("\n");
    }
}