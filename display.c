#include "game_utils.h"
#include <stdio.h>
#include "game.h"
#include <stdlib.h>
#include "display.h"

void clear_screen(void)
{
    /* Use the method that doesn't cause blinking */
    system("clear");
    system("tput cup 0 0");
}

void display_map(GameState* game)
{
    int i, j;

    clear_screen();

    for (i = 0; i < game->rows; i++)
    {
        for (j = 0; j < game->cols; j++)
        {
            if (IS_VISIBLE(game, i, j))
            {
                if (game->map[i][j] == EMPTY)
                    putchar(VISIBLE_EMPTY);
                else
                    putchar(game->map[i][j]);
            }
            else
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}