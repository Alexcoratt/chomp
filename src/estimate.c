#include "game.h"

size_t getRowCount(const struct Board *, size_t col);
size_t getColCount(const struct Board *, size_t row);

#define FIRST_PLAYER 0

#define UNKNOWN_EST 0
#define LOSE_EST -1
#define WIN_EST 1

int estimate(const struct GameState *gs) {
    const size_t ROW_COUNT = getRowCount(&gs->board, 0);
    const size_t COL_COUNT = getColCount(&gs->board, 0);
    const bool IS_FIRST_PLAYER = gs->currentPlayerNum == FIRST_PLAYER;

    if (getBoardCellState(&gs->board, 1, 1))
        return UNKNOWN_EST;   

    /*
    IS_FIRST_PLAYER r==c    RES
    0               0       LOSE
    0               1       WIN
    1               0       WIN
    1               1       LOSE
    */    
    return IS_FIRST_PLAYER != (ROW_COUNT == COL_COUNT) ? WIN_EST : LOSE_EST;
}

size_t getRowCount(const struct Board *board, size_t col) {
    size_t res = 0;
    for (; getBoardCellState(board, res, col) && res < board->height; ++res);
    return res;
}

size_t getColCount(const struct Board *board, size_t row) {
    size_t res = 0;
    for (; getBoardCellState(board, row, res) && res < board->width; ++res);
    return res;
}
