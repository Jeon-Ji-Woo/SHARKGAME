#ifndef BOARD_H
#define BOARD_H

//전역 상수 추가
#define N_BOARD             20
#define BOARDSTATUS_OK      1
#define BOARDSTATUS_NOK     0
#define N_COINPOS           12 
#define MAX_COIN            4 
#define MAX_SHARKSTEP       6
#define SHARK_INITPOS      -4

//함수 선언
void board_printBoardStatus(void);
int board_getBoardCoin(int pos);
int board_getBoardStatus(int pos);
void board_initBoard(void);
int board_stepShark(void);

#endif

