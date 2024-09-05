#pragma once
#include <stdint.h>

// BitBoard numbers
#define BOARD_TOP_LEFT 41
#define ROW_SIZE 7
#define COL_SIZE 6
#define COL_MAX_INDEX 5
#define BOARD_COL 0x20408102040

#define CLEAR_SCREEN "\x1b[2J\x1b[H"

typedef uint64_t BitBoard;

typedef struct {
    BitBoard players[2];
    uint8_t turn;
} Game;

int8_t placePiece(Game *game, uint8_t chosenColumn);
int8_t printBoard(Game game);
int8_t checkWin(BitBoard player, uint8_t piece);
int8_t displayGame(Game game);

extern uint64_t winLookupTable[];
extern uint32_t gridLookupTable[];