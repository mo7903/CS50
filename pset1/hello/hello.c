#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); //asks the user for his name
    printf("hello, %s!\n", name); //says hello to the user using the name from the above command
}