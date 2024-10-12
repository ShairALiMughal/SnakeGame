#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "display.h"
#include "terminal.h"
#include "random.h"
#include "newSleep.h"
int main(int argc, char *argv[])
{
    GameManager* manager;
    char move;
    int game_status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    manager = init_game(argv[1]);
    if (manager == NULL) {
        return 1;
    }

    initRandom();

    while (1) {
        display_map(manager->current);

        disableBuffer();
        scanf(" %c", &move);
        enableBuffer();

        if (move == 'q') {
            break; /* Quit the game */
        }
        else if (move == 'u') {
            undo_move(manager);
        }
        else {
            update_game(manager, move);
        }

        game_status = is_game_over(manager);
        if (game_status != 0) {
            display_map(manager->current);
            if (game_status == 1) {
                printf("You win!\n");
            } else {
                printf("You lose!\n");
            }
            break;
        }
    }

    free_game(manager);
    return 0;
}