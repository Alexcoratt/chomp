#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#define PLAYER_COUNT 2

struct CoordPair {
	size_t row;
	size_t col;
};

void fprintBoard(FILE *, const struct Board *);
void gameLoop(struct GameState *);
struct CoordPair fscanCoordPair(FILE *);

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <height> <width>\n", argv[0]);
		return 1;
	}

	size_t height = strtoul(argv[1], NULL, 0);
	size_t width = strtoul(argv[2], NULL, 0);

	if (height == 0 || width == 0) {
		fputs("Neither height nor width can be 0", stderr);
		return 2;
	}

	struct GameState gs;
	initGameState(&gs, PLAYER_COUNT, height, width);

	gameLoop(&gs);
	printf("player %lu won!\n", gs.currentPlayerNum);

	termGameState(&gs);

	return 1;
}	

void gameLoop(struct GameState *gs) {
	while (!gs->isFinished) {
		puts("board:");
		fprintBoard(stdout, &gs->board);
		printf("est: %d\n", estimate(gs));

		bool isMoveValid = true;

		do {
			printf("player %lu: ", gs->currentPlayerNum);
			struct CoordPair coords = fscanCoordPair(stdin);

			isMoveValid = gameMove(gs, coords.row, coords.col);
			if (!isMoveValid)
				puts("invalid move");

		} while (!isMoveValid);
	}
}

void fprintBoard(FILE *out, const struct Board *board) {
	for (size_t i = 0; i < board->height; ++i) {
		char line[board->width + 2];
		for (size_t j = 0; j < board->width; ++j)
			line[j] = getBoardCellState(board, i, j) ? '@' : '.';
		line[board->width] = '\n';
		line[board->width + 1] = '\0';
		fputs(line, out);
	}
}

struct CoordPair fscanCoordPair(FILE *input) {
	struct CoordPair res;
	fscanf(input, "%lu", &res.row);
	fscanf(input, "%lu", &res.col);

	return res;
}