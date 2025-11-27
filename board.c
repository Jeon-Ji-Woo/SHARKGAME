#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD             20
#define BOARDSTATUS_OK      1
#define BOARDSTATUS_NOK     0
#define N_COINPOS           12 
#define MAX_COIN            4 
#define MAX_SHARKSTEP       6
#define SHARK_INITPOS      -4

static int board_status[N_BOARD];
static int board_coin[N_BOARD];
static int shark_position;

void board_initBoard(void)
{
    int i;

    shark_position = SHARK_INITPOS;

    // Initialize arrays
    for (i = 0; i < N_BOARD; i++)
    {
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = 0;
    }

    // Allocate coins
    for (i = 0; i < N_COINPOS; i++)
    {
        int allocated = 0;
        do
        {
            int coinpos = rand() % N_BOARD;

            if (board_coin[coinpos] == 0)
            {
                board_coin[coinpos] = rand() % MAX_COIN + 1;
                allocated = 1;
            }
        } while (allocated == 0);
    }
}

int board_getBoardStatus(int pos)
{
    if (pos < 0 || pos >= N_BOARD) return BOARDSTATUS_NOK;
    return board_status[pos];
}

int board_getBoardCoin(int pos)
{
    if (pos < 0 || pos >= N_BOARD) return 0;
    return board_coin[pos];
}

int board_stepShark(void)
{
    int step = rand() % MAX_SHARKSTEP + 1;
    int i;

    for (i = 0; i < step; i++)
    {
        int posIdx = shark_position + i + 1;

        if (posIdx >= 0 && posIdx < N_BOARD)
            board_status[posIdx] = BOARDSTATUS_NOK;
    }

    shark_position += step;

    return shark_position;
}

void board_printBoardStatus(void)
{
    int i;

    printf("--------------- BOARD STATUS ---------------\n");
    for (i = 0; i < N_BOARD; i++)
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)
            //printf("%c", player_name[0]);
            printf("X");
        else
            printf("O");
    }
    printf("|\n");
    printf("--------------------------------------------\n");
    
    printf("-----------------BOARD COIN-----------------\n");
    for (i=0;i<N_BOARD;i++)
    {
    	printf("|%i", board_coin[i]);
    	//printf("O");
	}
    printf("|\n");
    printf("--------------------------------------------\n");
}

