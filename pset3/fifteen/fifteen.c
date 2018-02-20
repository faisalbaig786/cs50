/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // Creates i and j for 2-D array checking, full for the greatest number in the game
    int i, j;
    int full = (d * d) - 1;

    // As long as the value is greater than 0
    while (full > 0)
    {
        // Loops for 2-D array checking
        for (i = 0; i < d; i++)
        {
            for (j = 0; j < d; j++)
            {
                // Condition if odd dimensions
                if ((d == 3) | (d == 5) | (d == 7) | (d == 9))
                {
                    // Sets current i, j value to full and decreases full by 1
                    board[i][j] = full;
                    full--;
                }
                // Condition if even dimensions
                else if ((d == 4) | (d == 6) | (d == 8))
                {
                    if (full >= 3)
                    {
                        board[i][j] = full;
                        full--;
                    }
                    // Swaps the 2 and 1 for even game
                    else if (full == 2)
                    {
                        board[i][j] = full - 1;
                        full--;
                    }
                    // Swaps the 1 and 2 for even game
                    else if (full == 1)
                    {
                        board[i][j] = full + 1;
                        full--;
                    }
                }
            }
        }
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Prints blank line
    printf("\n");
    {
        // Checking 2-D array
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                // If last/0th value, prints blank tile
                if (board[i][j] == 0)
                {
                    printf("  _");
                }
                // Prints the number tile in descending order
                else
                {
                    printf(" %2i", board[i][j]);
                }
            }
            // Prints 2 blank lines
            printf("\n\n");
        }
    }
    // Prints blank line between board and user input line
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // Two-variable nested loops for 2-D array checking
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // If i and j are at the blank tile's position
            if (board[i][j] == 0)
            {
                // If number tile is on top of blank
                if ((i - 1 >= 0) && (board[i - 1][j] == tile))
                {
                    // Sets s to blank's value, blank's position to number's value, number's position to s's value
                    // Runs for loops again to find blank
                    int s = board[i][j];
                    board[i][j] = board[i - 1][j];
                    board[i - 1][j] = s;
                    return true;
                }
                // If number tile is below blank
                else if ((i + 1 < d) && (board[i + 1][j] == tile))
                {
                    int s = board[i][j];
                    board[i][j] = board[i + 1][j];
                    board[i + 1][j] = s;
                    return true;
                }
                // If number tile is to the left of blank
                else if ((j - 1 >= 0) && (board[i][j - 1] == tile))
                {
                    int s = board[i][j];
                    board[i][j] = board[i][j - 1];
                    board[i][j - 1] = s;
                    return true;
                }
                // If number tile is to the right of blank
                else if ((j + 1 < d) && (board[i][j + 1] == tile))
                {
                    int s = board[i][j];
                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = s;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // Sets variable val to the last value printed (1)
    int val = ((d * d) + 1) - (d * d);

    // Nested for loops for 2-D array checking
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // As long as the final value hasn't been reached and the board is at the current value
            if (val < (d * d) - 1 && board[i][j] == val)
            {
                // Move to the following value (+1)
                val++;
            }
            // If the final value has been reached and the blank follows, win
            else if (val == (d * d) - 1 && board[d - 1][d - 1] == 0)
            {
                return true;
            }
            // If the blank appears too early, no win yet
            else if (board[i][j] == 0)
            {
                return false;
            }
            // If any tile is out of order, no win yet
            else
            {
                return false;
            }
        }
    }
    return false;
}
