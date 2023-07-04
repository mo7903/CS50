#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i = 0;
    int sum = 0;
    int j = 0;

    long n = get_long("Number: ");
    long temp = n;
    long tempo = temp;

    do
    {
        temp = temp / 10;
        i = temp % 10;
        i = i * 2;
        temp = temp / 10;
        if (i >= 10) {
            j = i % 10;
            i = i / 10;
            sum = sum + i + j;
        } else {
            sum = sum + i;
        }

    }
    while (temp > 1);

    do
    {
        i = tempo % 10;
        tempo = tempo / 100;
        sum = sum + i;
    }
    while(tempo > 1);

if (sum % 10 == 0) {
    if (n / 1000000000000000 > 1 && n / 1000000000000000 == 4) {
        printf ("VISA\n");
    } else if (n / 1000000000000000 > 1 && n / 1000000000000000 == 5) {
        if (n / 100000000000000 < 56 ) {
        printf("MASTERCARD\n");
        } else {
            printf("INVALID\n");
        }
    } else if (n / 100000000000000 > 1) {
        if (n / 10000000000000 == 34 || n / 10000000000000 == 37) {
        printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }
    } else if (n / 1000000000000 > 1 && n / 1000000000000 == 4) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }

} else {
    printf("INVALID\n");
}
}