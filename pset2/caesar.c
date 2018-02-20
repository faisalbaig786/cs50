#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Checks if the right number of args given
    if (argc != 2)
    {
        printf("provide non-negative integer key\n");
        return 1;
    }
    else
    {
        // Converts arg to int
        int k = atoi(argv[1]);

        // Rejects negative integer
        if (k < 0)
        {
            printf("provide non-negative integer key\n");
            return 1;
        }

        // Gets user plaintext input
        printf("plaintext: ");
        string s = get_string();
        printf("ciphertext: ");

        // Encodes plaintext with key
        for (int i = 0, n = strlen(s); i < n; i++)
        {
            // Sorts uppercase
            if (isupper(s[i]))
            {
                printf("%c", (((s[i] + k) - 65) % 26) + 65);
            }
            // Sorts lowercase
            else if (islower(s[i]))
            {
                printf("%c", (((s[i] + k) - 97) % 26) + 97);
            }
            // Sorts non-alphabetic inputs
            else
            {
                printf("%c", s[i]);
            }
        }
    }
    printf("\n");
}