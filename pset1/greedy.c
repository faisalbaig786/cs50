#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float owed=0;
    int change =0;
    int q =0;
    int d =0;
    int n =0;
    int p =0;
    
    printf("O hai! How much change is owed?\n");
    do
    {
        owed = get_float();
        if (owed < 0)
        printf("How much change is owed?\n");
    }
    while (owed < 0);
    
     change = (int)round(owed * 100);
    
    while (change >= 25)
    {
        q = q + 1;
        change = change - 25;
    }
    while (change >= 10)
    {
        d = d + 1;
        change = change - 10;
    }
    while (change >= 5)
    {
        n = n + 1;
        change = change - 5;
    }
    while (change >= 1)
    {
        p = p + 1;
        change = change - 1;
    }
    
    
    printf("%i\n", q + d + n + p);
}
