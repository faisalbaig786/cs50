#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensures proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // Remembers n resize factor
    int n = atoi(argv[1]);

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n should be between 1 and 100\n");
        return 2;
    }

    // Remembers filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // Opens input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // Opens output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // Reads infile's BITMAPFILEHEADER
    BITMAPFILEHEADER i_bf, o_bf;
    fread(&i_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Reads infile's BITMAPINFOHEADER
    BITMAPINFOHEADER i_bi, o_bi;
    fread(&i_bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Determines input file's padding
    int paddingi =  (4 - (i_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Sets output bf and bi to input
    o_bf = i_bf;
    o_bi = i_bi;

    // Ensures infile is (likely) a 24-bit uncompressed BMP 4.0
    if (i_bf.bfType != 0x4d42 || i_bf.bfOffBits != 54 || i_bi.biSize != 40 ||
        i_bi.biBitCount != 24 || i_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // Multiplies output bmp width and height by n
    o_bi.biWidth *= n;
    o_bi.biHeight *= n;

    // Determines padding for output scanlines
    int paddingo =  (4 - (o_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Edits biSizeImage and bfSize values for output
    o_bi.biSizeImage = ((sizeof(RGBTRIPLE) * o_bi.biWidth) + paddingo) * abs(o_bi.biHeight);
    o_bf.bfSize = o_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Writes outfile's BITMAPFILEHEADER
    fwrite(&o_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Writes outfile's BITMAPINFOHEADER
    fwrite(&o_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Iterates over infile's scanlines
    for (int i = 0, biHeight = abs(i_bi.biHeight); i < biHeight; i++)
    {
        // Iterates n times for each row
        for (int j = 0; j < n; j++)
        {
            // Iterates over pixels in scanline
            for (int k = 0; k < i_bi.biWidth; k++)
            {
                // Temporary storage in 'triple'
                RGBTRIPLE triple;

                // Reads RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // Writes RGB triple to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // Adds outfile padding
            for (int m = 0; m < paddingo; m++)
            {
                fputc(0x00, outptr);
            }
            // Repeats row writing for n times
            if (j < n - 1)
            {
                fseek(inptr, -i_bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
         // Skips over padding
        fseek(inptr, paddingi, SEEK_CUR);
    }

    // Closes infile
    fclose(inptr);

    // Closes outfile
    fclose(outptr);

    // Success
    return 0;
}