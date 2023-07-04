#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int found, i;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *rFile = fopen(argv[1], "r"); //opens given file for reading
    if (rFile == NULL)
    {
        printf("Forensic image cannot be read\n");
        return 1;
    }
    BYTE *buffer = malloc(sizeof(BYTE) * 512); //allocates memory for buffer
    char output[8];
    FILE *img = NULL;
    while (fread(buffer, sizeof(BYTE) * 512, 1, rFile) == 1) //read 512 Bytes at a time
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            found = 1; //indicates whether there is a JPEG file in recovery or not
            sprintf(output, "%03i.jpg", i);
            img = fopen(output, "w"); //prepares file for writing
            fwrite(buffer, sizeof(BYTE) * 512, 1, img); //write
            i++; //numbers the found JPEGs
        }
        else
        {
            if (found == 1)
            {
                fwrite(buffer, sizeof(BYTE) * 512, 1, img); //write
            }
            else
            {
                found = 0;
            }
        }
    }
    free(buffer); // frees previously allocated memory
}