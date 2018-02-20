#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Defines integer for jpeg size
int BUFFER_SIZE = 512;

int main(void)
{
    // Creates buffer
    unsigned char buffer[BUFFER_SIZE];

    // Creates jpeg filename array
    char filename[8];

    // Creates filename counter
    int up = 0;

    // Creates pointer to outfile
    FILE *img = NULL;

    // Opens input file
    FILE *inptr = fopen("card.raw", "r");

    // Ensures proper use
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", "card.raw");
        return 1;
    }

    // Reads card.raw for 512 bytes
    while (fread(buffer, 1, BUFFER_SIZE, inptr) == BUFFER_SIZE)
    {
        // Checks for jpeg header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] || buffer[3] == 0xe1))
            {
                // Closes previous jpeg file
                if (img != NULL)
                {
                    fclose(img);
                }

                // Names image
                sprintf(filename, "%03d.jpg", up);

                // Creates new jpeg file
                img = fopen(filename, "w");

                // Increases jpeg number counter
                up++;

                // Checks if image is NULL
                if (img == NULL)
                {
                    fclose(inptr);
                    printf("Error: Could not create image.\n");
                    return 1;
                }
            }
            // Checks if jpeg is open/not NULL
            if (img != NULL)
            {
                // Ensures proper writing
                if (fwrite(buffer, 1, BUFFER_SIZE, img) != BUFFER_SIZE)
                {
                    fclose(img);
                    fclose(inptr);
                    printf("Error writing file.\n");
                    return 1;
                }
            }
    }

    // Closes previous jpeg file
    if (img != NULL)
    {
        fclose(img);
    }

    // Checks for errors in reading
    if (ferror(inptr))
    {
        fclose(inptr);
        printf("Error reading raw file.\n");
        return 1;
    }

    // Closes input file
    fclose(inptr);
    return 0;

}