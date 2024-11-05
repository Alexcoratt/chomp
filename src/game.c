#include <stdlib.h>
#include <string.h>

#include "game.h"

void initGameState(struct GameState *gs, size_t playerCount, size_t boardHeight, size_t boardWidth) {
	gs->playerCount = playerCount;
	gs->currentPlayerNum = 0;
	
	initBoard(&gs->board, boardHeight, boardWidth);
	gs->isFinished = isFinalBoardState(&gs->board);
}

void initBoard(struct Board *board, size_t height, size_t width) {
	board->height = height;
	board->width = width;  
	
	size_t byteSize = height * width * sizeof(bool);
	board->cells = (bool *)memset(malloc(byteSize), true, byteSize);
}

void termGameState(struct GameState *gs) {
	termBoard(&gs->board);
}

void termBoard(struct Board *board) {
	free(board->cells);
}

bool gameMove(struct GameState *gs, size_t row, size_t col) {
	if (!doMoveOnBoard(&gs->board, row, col))
		return false;
	
	setNextPlayerNum(gs);
	gs->isFinished = isFinalBoardState(&gs->board);
	return true;
}

bool doMoveOnBoard(struct Board *board, size_t row, size_t col) {
	if (!getBoardCellState(board, row, col))
		return false;

	for (size_t i = row; i < board->height; ++i)
		for (size_t j = col; j < board->width; ++j)
			setBoardCellState(board, i, j, false);	

	return true;
}

bool getBoardCellState(const struct Board *board, size_t row, size_t col) {
	if (row >= board->height || col >= board->width)
		return false;

	return board->cells[row * board->width + col];
}

void setBoardCellState(struct Board *board, size_t row, size_t col, bool state) {
	if (row < board->height && col < board->width)
		board->cells[row * board->width + col] = state;
}

void setNextPlayerNum(struct GameState *gs) {
	gs->currentPlayerNum = (gs->currentPlayerNum + 1) % gs->playerCount;
}

bool isFinalBoardState(const struct Board *board) {
	for (size_t i = 0; i < board->height; ++i)
		for (size_t j = 0; j < board->width; ++j)
			if (getBoardCellState(board, i, j))
				return false;
	return true;
}
