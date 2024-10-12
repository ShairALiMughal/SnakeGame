#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <stdlib.h>
#include "game.h"

#ifdef DARK
#define IS_VISIBLE(game, row, col) \
    (abs((row) - game->player_row) + abs((col) - game->player_col) <= game->vision_range)
#else
#define IS_VISIBLE(game, row, col) 1
#endif

#endif /* GAME_UTILS_H */