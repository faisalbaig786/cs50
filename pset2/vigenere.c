#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Rejects incorrect number of args
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    // Stores key and gets length
    string k = argv[1];
    int klen = strlen(k);

    // Rejects non-alphabetic key
    for (int i = 0; i < klen; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }

    // Gets user plaintext input
    printf("plaintext: ");
    string s = get_string();
    printf("ciphertext: ");

    for (int i = 0, m = 0, n = strlen(s); i < n; i++)
    {

    // Gets key for specific letter
    int slen = tolower(k[m % klen]) - 'a';

        // Encrypts uppercase inputs
        if (isupper(s[i]))
        {
            printf("%c", 'A' + (s[i] - 'A' + slen) % 26);
            m++;
        }
        // Encrypts lowercase inputs
        else if (islower(s[i]))
        {
            printf("%c", 'a' + (s[i] - 'a' + slen) % 26);
            m++;
        }
        // Encrypts non-alphabetic inputs
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}