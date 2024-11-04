#ifndef GAME_H
#define GAME_H

#include <stddef.h>
#include <stdbool.h>

struct Board {
	size_t height;
	size_t width;

	bool *cells;
};

void initBoard(struct Board *, size_t height, size_t width);
void termBoard(struct Board *);

// returns true if a move is valid
bool doMoveOnBoard(struct Board *, size_t row, size_t col);

bool getBoardCellState(const struct Board *, size_t row, size_t col);
void setBoardCellState(struct Board *, size_t row, size_t col, bool state);

bool isFinalBoardState(const struct Board *);

struct GameState {
	size_t playerCount;
	size_t currentPlayerNum;

	struct Board board;
	bool isFinished;
};

void initGameState(struct GameState *, size_t playerCount, size_t boardHeight, size_t boardWidth);
void termGameState(struct GameState *);

// returns true if a move is valid
bool gameMove(struct GameState *, size_t row, size_t col); 

void setNextPlayerNum(struct GameState *);

#endif
