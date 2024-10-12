#include "game_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "random.h"
#include "display.h"

#ifdef DARK
#define IS_VISIBLE(game, row, col) \
    (abs((row) - game->player_row) + abs((col) - game->player_col) <= game->vision_range)
#else
#define IS_VISIBLE(game, row, col) 1
#endif

GameManager* init_game(const char* filename)
{
    FILE* file;
    GameManager* manager;
    GameState* game;
    int i, j, wall_count;

    manager = (GameManager*)malloc(sizeof(GameManager));
    if (manager == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    game = (GameState*)malloc(sizeof(GameState));
    if (game == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(manager);
        return NULL;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        free(game);
        free(manager);
        return NULL;
    }

    fscanf(file, "%d %d", &game->rows, &game->cols);
    fscanf(file, "%d", &wall_count);

    /* Allocate memory for the map */
    game->map = (char**)malloc(game->rows * sizeof(char*));
    for (i = 0; i < game->rows; i++) {
        game->map[i] = (char*)malloc(game->cols * sizeof(char));
    }

    /* Initialize the map */
    for (i = 0; i < game->rows; i++) {
        for (j = 0; j < game->cols; j++) {
            int obj;
            fscanf(file, "%d", &obj);
            switch(obj) {
                case 0: game->map[i][j] = EMPTY; break;
                case 1: game->map[i][j] = WALL; break;
                case 2: 
                    game->map[i][j] = LANTERN;
                    game->lantern_row = i;
                    game->lantern_col = j;
                    break;
                case 3: 
                    game->map[i][j] = PLAYER;
                    game->player_row = i;
                    game->player_col = j;
                    break;
                case 4: 
                    game->map[i][j] = SNAKE;
                    game->snake_row = i;
                    game->snake_col = j;
                    break;
                case 5: 
                    game->map[i][j] = TREASURE;
                    game->treasure_row = i;
                    game->treasure_col = j;
                    break;
            }
        }
    }

    fclose(file);

    game->vision_range = 3;
    game->has_lantern = 0;

    manager->current = game;
    manager->head = NULL;

    return manager;
}

void update_game(GameManager* manager, char move)
{
    GameState* game = manager->current;
    int new_row = game->player_row;
    int new_col = game->player_col;
    UndoNode* new_node;
    int i, direction, snake_new_row, snake_new_col;

    /* Save current state for undo */
    new_node = (UndoNode*)malloc(sizeof(UndoNode));
    new_node->state = (GameState*)malloc(sizeof(GameState));
    memcpy(new_node->state, game, sizeof(GameState));
    new_node->state->map = (char**)malloc(game->rows * sizeof(char*));
    for (i = 0; i < game->rows; i++) {
        new_node->state->map[i] = (char*)malloc(game->cols * sizeof(char));
        memcpy(new_node->state->map[i], game->map[i], game->cols * sizeof(char));
    }
    new_node->prev = manager->head;
    manager->head = new_node;


    /* Update player position based on move */
    switch(move) {
        case 'w': new_row--; break;
        case 's': new_row++; break;
        case 'a': new_col--; break;
        case 'd': new_col++; break;
        default: return; /* Invalid move */
    }

    /* Check if the move is valid */
    if (new_row >= 0 && new_row < game->rows && new_col >= 0 && new_col < game->cols 
        && game->map[new_row][new_col] != WALL) {
        
        /* Update player position */
        game->map[game->player_row][game->player_col] = EMPTY;
        game->player_row = new_row;
        game->player_col = new_col;

        /* Check for lantern */
        if (game->map[new_row][new_col] == LANTERN) {
            game->has_lantern = 1;
            game->vision_range = 6;
        }

        game->map[new_row][new_col] = PLAYER;

        /* Move snake */
        direction = randomUCP(0, 7);
        snake_new_row = game->snake_row;
        snake_new_col = game->snake_col;

        switch(direction) {
            case 0: snake_new_row--; break;
            case 1: snake_new_row--; snake_new_col++; break;
            case 2: snake_new_col++; break;
            case 3: snake_new_row++; snake_new_col++; break;
            case 4: snake_new_row++; break;
            case 5: snake_new_row++; snake_new_col--; break;
            case 6: snake_new_col--; break;
            case 7: snake_new_row--; snake_new_col--; break;
        }

        /* Check if snake move is valid */
        if (snake_new_row >= 0 && snake_new_row < game->rows && snake_new_col >= 0 && snake_new_col < game->cols 
            && game->map[snake_new_row][snake_new_col] != WALL
            && game->map[snake_new_row][snake_new_col] != TREASURE
            && game->map[snake_new_row][snake_new_col] != LANTERN) {
            
            game->map[game->snake_row][game->snake_col] = EMPTY;
            game->snake_row = snake_new_row;
            game->snake_col = snake_new_col;
            game->map[snake_new_row][snake_new_col] = SNAKE;
        }
    }
}

void undo_move(GameManager* manager)
{
    GameState* temp;
    UndoNode* temp_node;
    int i;

    if (manager->head == NULL) {
        return; /* Nothing to undo */
    }

    temp = manager->current;
    manager->current = manager->head->state;
    temp_node = manager->head;
    manager->head = manager->head->prev;

    /* Free the old current state */
    for (i = 0; i < temp->rows; i++) {
        free(temp->map[i]);
    }
    free(temp->map);
    free(temp);

    free(temp_node);
}

int is_game_over(GameManager* manager)
{
    GameState* game = manager->current;
    /* Check if player reached treasure */
    if (game->player_row == game->treasure_row && game->player_col == game->treasure_col) {
        return 1; /* Player wins */
    }

    /* Check if snake ate player */
    if (game->player_row == game->snake_row && game->player_col == game->snake_col) {
        return -1; /* Player loses */
    }

    return 0; /* Game continues */
}

void free_game(GameManager* manager)
{
    GameState* game = manager->current;
    int i;
    for (i = 0; i < game->rows; i++) {
        free(game->map[i]);
    }
    free(game->map);
    free(game);

    while (manager->head != NULL) {
        UndoNode* temp = manager->head;
        manager->head = manager->head->prev;
        for (i = 0; i < temp->state->rows; i++) {
            free(temp->state->map[i]);
        }
        free(temp->state->map);
        free(temp->state);
        free(temp);
    }

    free(manager);
}