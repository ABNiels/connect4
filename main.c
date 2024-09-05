#include <stdio.h>
#include <stdint.h>
#include "connect4.h"

int main() {
    Game game = {{0x0,0}, 0};
    
    int8_t piece, column;

    do {
        column = displayGame(game);
        if(column > 6 || column < 0) continue;

        piece = placePiece(&game, column);
        if (piece < 0) continue;

        game.turn ^= 1;
    } while (checkWin(game.players[game.turn ^ 1], piece) == 0);
    printf(CLEAR_SCREEN);
    printf("Game Over\n");
    printBoard(game);
    
    return 0;
}

int8_t placePiece(Game *game, uint8_t chosenColumn) {
    
    int8_t numToShift = BOARD_TOP_LEFT - chosenColumn - (ROW_SIZE * (COL_MAX_INDEX - __builtin_popcountll((game->players[0] | game->players[1]) & (BOARD_COL >> chosenColumn))));
    if (numToShift < 0) return -1;

    game->players[game->turn] |= (1ULL << numToShift);

    return numToShift;
}

int8_t checkWin(BitBoard player, uint8_t piece) {
    uint8_t shift;
    uint32_t temp, grid;

    if (__builtin_popcountll(player) < 4) return 0;

    temp = gridLookupTable[piece];
    while(temp != 0) {
        
        shift = __builtin_ctzll(temp);
        temp ^= (1 << shift);

        grid = player >> shift;
        grid = (grid & 0xF) | ((grid >> 3) & 0xF0) | ((grid >> 6) & 0xF00) | ((grid >> 9) & 0xF000);

        if (winLookupTable[grid >> 6] & (0x8000000000000000ULL >> (grid & 0x3F))) return 1;
    }

    return 0;
}


int8_t displayGame(Game game) {
    printf(CLEAR_SCREEN);
    printBoard(game);
    printf("\n");
    printf("Player %i (%c) enter a move: ", game.turn + 1, "BR"[game.turn]);
    int8_t input;
    scanf("%i", &input);
    return input;
}

int8_t printBoard(Game game) {
    int8_t i;
    for(i = BOARD_TOP_LEFT; i >= 0; i--) {
        switch (((game.players[0] >> i) & 0x1) | ((game.players[1] >> i) & 0x1) << 1)  {
            case 1:
                printf("B ");
                break;
            case 2:
                printf("R ");
                break;
            case 0:
                printf(". ");
                break;
            default:
                break;
        }
        if (i%7 == 0) printf("\n");
    }
    return 0;
}