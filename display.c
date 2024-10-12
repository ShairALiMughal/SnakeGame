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
    
    /* Print top border */
    for (j = 0; j < game->cols + 2; j++) {
        putchar('*');
    }
    putchar('\n');

    for (i = 0; i < game->rows; i++) {
        putchar('*'); /* Left border */
        for (j = 0; j < game->cols; j++) {
            if (IS_VISIBLE(game, i, j)) {
                if (game->map[i][j] == EMPTY) {
                    putchar(VISIBLE_EMPTY);
                } else {
                    putchar(game->map[i][j]);
                }
            } else {
                putchar(' ');
            }
        }
        putchar('*'); /* Right border */
        putchar('\n');
    }

    /* Print bottom border */
    for (j = 0; j < game->cols + 2; j++) {
        putchar('*');
    }
    putchar('\n');

    /* Print instructions */
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("Press u to undo\n");
}