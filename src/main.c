#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#define PLAYER_COUNT 2

struct CoordPair {
	size_t row;
	size_t col;
};

enum GAME_LOOP_STATE {
	GL_SUCCESS = 0,
	GL_FILE_READING_ERROR
};

enum GAME_LOOP_STATE gameLoop(struct GameState *);
void fprintBoard(FILE *, const struct Board *);
bool fscanCoordPair(FILE *, struct CoordPair *);

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

	enum GAME_LOOP_STATE glstate = gameLoop(&gs);

	switch (glstate) {
		case GL_FILE_READING_ERROR:
			fputs("Unexpected EOF error\n", stderr);
			break;
		default:
			printf("player %lu won!\n", gs.currentPlayerNum);
	}

	termGameState(&gs);

	return glstate;
}	

enum GAME_LOOP_STATE gameLoop(struct GameState *gs) {
	while (!gs->isFinished) {
		puts("board:");
		fprintBoard(stdout, &gs->board);

		bool isMoveValid = true;

		do {
			printf("player %lu: ", gs->currentPlayerNum);

			struct CoordPair coords;
			if (!fscanCoordPair(stdin, &coords))
				return GL_FILE_READING_ERROR;

			isMoveValid = gameMove(gs, coords.row, coords.col);
			if (!isMoveValid)
				puts("invalid move");

		} while (!isMoveValid);
	}

	return GL_SUCCESS;
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

bool fscanCoordPair(FILE *input, struct CoordPair *coords) {
	return fscanf(input, "%lu%lu", &coords->row, &coords->col) != EOF;
}