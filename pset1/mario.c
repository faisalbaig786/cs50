#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
    printf("Height: ");
    h = get_int();
    }
    while (h < 0 || h > 23);
    
    for (int i = 0; i < h; i++)
    {   
        for (int j = h; j > i + 1; j--)
        {
        printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
        printf("#");
        }
        printf("  ");
         for (int k = 0; k <= i; k++)
        {
        printf("#");
        }
        printf("\n");
    }
}