/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Setting variables for minimum, maximum, and middle values
    int min = 0;
    int max = n - 1;
    int mid = (min + max) / 2;

    // Setting the condition while the max value has not been gone past
    while (min <= max)
    {
        // Checks for value in the middle of the array
        if (values[mid] == value)
        {
            return true;
        }
        // Checks for value before the middle
        else if (value < values[mid])
        {
            max = mid - 1;
            mid = (min + max) / 2;
        }
        // Checks for value after middle
        else if (value > values[mid])
        {
            min = mid + 1;
            mid = (min + max) / 2;
        }
        // Terminates checking if value not find
        else
        {
            break;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Creates loop to check values
    for (int i = 0; i < n - 1; i++)
    {
        int check = 0;
        // Sets int s to i
        for (int s = i; s < n; s++)
        {
            // Checks if the next number after i is smaller
            if (values[s] < values[i])
            {
                // Sets the smaller s value to int temp, sets s to larger i value, sets i to smaller temp value
                // Sets check to 1 to continue checking the array
                int temp = values[s];
                values[s] = values[i];
                values[i] = temp;
                check = 1;
            }
        }
        if (check == 0)
            break;
    }
    // Prints the values in order once sorted
    for (int x = 0; x < n; x++)
        printf("%d\n", values[x]);
        return;
}
