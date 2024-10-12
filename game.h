#ifndef GAME_H
#define GAME_H

#include <stdio.h>

/* Game object definitions */
#define EMPTY ' '
#define WALL 'O'
#define LANTERN '@'
#define PLAYER 'P'
#define SNAKE '~'
#define TREASURE '$'
#define VISIBLE_EMPTY ' '

/* Game state structure */
typedef struct {
    char** map;
    int rows;
    int cols;
    int player_row;
    int player_col;
    int snake_row;
    int snake_col;
    int lantern_row;
    int lantern_col;
    int treasure_row;
    int treasure_col;
    int vision_range;
    int has_lantern;
} GameState;

typedef struct UndoNode {
    GameState* state;
    struct UndoNode* prev;
} UndoNode;

typedef struct {
    GameState* current;
    UndoNode* head;
} GameManager;

/* Function prototypes */
GameManager* init_game(const char* filename);
void update_game(GameManager* manager, char move);
int is_game_over(GameManager* manager);
void free_game(GameManager* manager);
void undo_move(GameManager* manager);

#endif /* GAME_H */