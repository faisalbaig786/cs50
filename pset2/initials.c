#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // gets user input
    string s = get_string();

    // makes sure user input is a string
    if (s != NULL)
    {
        // print the first initial
        printf("%c", toupper(s[0]));
    }

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // searches for space between strings
        if (s[i] == ' ')
        {
            // prints initial after space
            printf("%c", toupper(s[i + 1]));
        }
    }
    printf("\n");
}