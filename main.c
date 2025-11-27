#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAXLENGTH           30
#define MAX_DIE             6
#define N_PLAYER            3

#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2

char player_name[N_PLAYER][MAXLENGTH];
int player_position[N_PLAYER];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];

char player_statusString[3][MAXLENGTH] = {
    "LIVE",
    "DIE",
    "END"
};

int rolldie(void)
{
    return rand() % MAX_DIE + 1;
}

int gameEnd(void)
{
	int i;
	int flag_end = 1;
	
	for (i = 0; i < N_PLAYER; i++)
    {
        if(player_status[i] == PLAYERSTATUS_LIVE)
        	flag_end = 0;
    }
    
    return flag_end;
}

void initPlayer(void)
{
    int i;
    for (i = 0; i < N_PLAYER; i++)
    {
        player_position[i] = 0;
        player_coin[i] = 0;
        player_status[i] = PLAYERSTATUS_LIVE;

        printf("Player %d name: ", i);
        scanf("%s", player_name[i]);
    }
}

void printPlayerPosition(int player)
{
    int i;
    printf("Player %s position:\n", player_name[player]);
    
    for (i = 0; i < N_BOARD; i++)
    {
        printf("|");
        if (i == player_position[player])
            printf("%c", player_name[player][0]);
        else
        {
            if (board_getBoardStatus(i) == BOARDSTATUS_OK)
                printf(" ");
            else
                printf("X");
        }
    }
    printf("|\n");
}

void printPlayerStatus(void)
{
    int i;
    printf("\n------ PLAYER STATUS ------\n");
    for (i = 0; i < N_PLAYER; i++)
    {
        printf("%s : pos %d, coin %d, status %s\n",
            player_name[i],
            player_position[i],
            player_coin[i],
            player_statusString[player_status[i]]);
    }
    printf("-------------------------------\n\n");
}

void checkDie(void)
{
    int i;
    for (i = 0; i < N_PLAYER; i++)
    {
        if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
        {
            if (player_status[i] == PLAYERSTATUS_LIVE)
            {
                player_status[i] = PLAYERSTATUS_DIE;
                printf("So Sad! %s died at position %i\n", player_name[i], player_position[i]);
            }
        }
    }
}


int main(void)
{
	int cnt;
    int turn = 0;
    int dum;
    int coinResult;
    int die_result;

    srand((unsigned)time(NULL));

    // Opening
    printf("============================================\n");
    printf("********************************************\n");
    printf("             SHARK GAME START               \n");
    printf("********************************************\n");
    printf("============================================\n\n");

    // Step 1. Initialization
    board_initBoard();
    initPlayer();

    // Step 2. Game Loop
    do{
    	if(player_status[turn] != PLAYERSTATUS_LIVE)
    	{
    		turn = turn + 1%N_PLAYER;
    		continue;
		}
    	
    	//2-1. status printing
        board_printBoardStatus();
        
        //Player status
        printPlayerStatus();
        
		//2-2. roll die
        printf("%s's turn! Press ENTER to roll a die...\n", player_name[turn]);
        scanf("%d", &dum);
        fflush(stdin);
        getchar();
		die_result = rolldie();

		//2-3. moving
        player_position[turn] += die_result;
        if (player_position[turn] >= N_BOARD - 1)
        {
            player_position[turn] = N_BOARD - 1;
            player_status[turn] = PLAYERSTATUS_END;
        }
        
        printf("Die result: %i, %s moved to %i\n", die_result, player_name[turn], player_position[turn]);

        // get coin
        player_coin[turn] += board_getBoardCoin(player_position[turn]);
        printf("Coin gained: %d (total %d)\n",
            board_getBoardCoin(player_position[turn]),
            player_coin[turn]);

        // 2-4.change turn
        turn = (turn + 1) % N_PLAYER;

        // Shark move
        if (turn == 0)
        {
            int shark_pos = board_stepShark();
            printf("Shark moved to: %i\n", shark_pos);
            
            checkDie();
        }
        
    } while (gameEnd() == 0);
    //step3. game end (winner printing)
    
    //ending 
	printf("\n\n\n\n\n\n\n");
	printf("============================================\n");
	printf("********************************************\n");
	printf(" SHARK GAME END \n");
	printf("********************************************\n");
	printf("============================================\n\n");
	system("PAUSE");
	
    return 0;
}

