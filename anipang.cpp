/*
* AniPang:
* This is a basic graphical interface of AniPang game.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "anipang.h"
#include "draw.h"


void mkBoard(Board *board, int xsize, int ysize, int nitems)
{
	int i, j;

	board->xsize = xsize;
	board->ysize = ysize;
	board->nitems = nitems;
	board->timeout = 60;  // in seconds
	board->time = board->timeout;
	board->score = 0;
    for (i = 0; i < ysize; i++) {
        for (j = 0; j < xsize; j++)
        {
            board->tiles[i][j] = rand() % nitems + 1;
            if (board->tiles[i][j] == board->tiles[i][j - 1] && board->tiles[i][j - 2] == board->tiles[i][j])
                while (board->tiles[i][j - 2] == board->tiles[i][j - 1] && board->tiles[i][j - 2] == board->tiles[i][j])
                    board->tiles[i][j] = rand() % nitems + 1;

            if (board->tiles[i][j] == board->tiles[i - 1][j] && board->tiles[i - 2][j] == board->tiles[i][j])
                while (board->tiles[i - 2][j] == board->tiles[i - 1][j] && board->tiles[i - 2][j] == board->tiles[i][j])
                    board->tiles[i][j] = rand() % nitems + 1;
        }
    }
	// 생성된 보드에서 3개 이상 연속된 값이 없도록 만들어야 한다
}


void gameInit(Board *board)
{
    srand((unsigned)time(0));
    mkBoard(board, XSIZE, YSIZE, NUM_ITEM);
}

void pattern1(Board* board) {
    //가로
    for (int i = 0; i < YSIZE; i++) {
        for (int j = 0; j < XSIZE; j++) {
            if (board->tiles[i][j] == board->tiles[i][j - 1] && board->tiles[i][j] == board->tiles[i][j - 2]) {
                board->tiles[i][j] = 0;
                board->tiles[i][j - 1] = 0;
                board->tiles[i][j - 2] = 0;
                display();
                Sleep(300);

                for (i; i > 0; i--) {
                    board->tiles[i][j] = board->tiles[i - 1][j];
                    board->tiles[i][j - 1] = board->tiles[i - 1][j - 1];
                    board->tiles[i][j - 2] = board->tiles[i - 1][j - 2];
                }
                board->tiles[0][j] = rand() % board->nitems + 1;
                board->tiles[0][j - 1] = rand() % board->nitems + 1;
                board->tiles[0][j - 2] = rand() % board->nitems + 1;

                display();
                Sleep(100);

            }
        }
    }
    //세로
    for (int j = 0; j < XSIZE; j++) {
        for (int i = 0; i < YSIZE; i++) {
            if (board->tiles[i][j] == board->tiles[i - 1][j] && board->tiles[i][j] == board->tiles[i - 2][j]) {
                board->tiles[i][j] = 0;
                board->tiles[i - 1][j] = 0;
                board->tiles[i - 2][j] = 0;
                display();
                Sleep(300);
                for (int k = 0; k < 3; k++){
                    int n = i;
                    for (; n > 0; n--) {
                        board->tiles[n][j] = board->tiles[n - 1][j];
                    }
                    board->tiles[0][j] = rand() % board->nitems + 1;
                    display();
                    Sleep(100);
                }
            }
        }
    }
}

void pattern2(Board *board) {
    for (int i = 0; i < YSIZE; i++) {
        for (int j = 0; j < XSIZE; j++) {
            if (board->tiles[i][j] == board->tiles[i][j - 1] && board->tiles[i][j] == board->tiles[i][j - 2] && board->tiles[i][j]== board->tiles[i][j - 3]) {
                for (int x = 0; x < 7; x++) {
                    board->tiles[i][x] = 0;
                }
                display();
                Sleep(300);

                for (int x = 0; x < 7; x++) {
                    board->tiles[i][x] = board->tiles[i - 1][x];
                }
                for (int x = 0; x < 7; x++) {
                    board->tiles[0][x] = rand() % board->nitems + 1;
                }
                display();
                Sleep(100);

            }
        }
    }
    //세로
    for (int j = 0; j < XSIZE; j++) {
        for (int i = 0; i < YSIZE; i++) {
            if (board->tiles[i][j] == board->tiles[i - 1][j] && board->tiles[i][j] == board->tiles[i - 2][j] && board->tiles[i][j] == board->tiles[i - 3][j]) {
                for (int k = 0; k < 7; k++) board->tiles[k][j] = 0;
                display();
                Sleep(300);
                for (int k = 0; k < 7; k++) {
                    board->tiles[k][j] = 0;
                    for (int n = 6; n > 0; n--) {
                        board->tiles[n][j] = board->tiles[n - 1][j];
                    }
                    board->tiles[0][j] = rand() % board->nitems + 1;
                    display();
                    Sleep(100);
                }
            }
        }
    }
}

void pattern3(Board* board) {
    }
// curr: 마우스가 클릭된 타일 위치를 알려준다.
// move: 마우스가 움직인 방향을 알려준다. (0, 1), (0, -1), (1, 0), (-1, 0) 중의 하나이다.
void mouseMotion(Board* board, int tile[2], int move[2])
{
    int x, y;
    // 마우스를 이용하여 타일을 움직였을 때 해당 내용을 구현해야 한다
    printf("(%d, %d) move by (%d, %d)\n", tile[0], tile[1], move[0], move[1]); // 디버깅 코드. 지워도 됩니다.
    y = tile[0] + move[0];
    x = tile[1] + move[1];
    int temp;
    temp = board->tiles[tile[1]][tile[0]];
    board->tiles[tile[1]][tile[0]] = board->tiles[x][y];
    board->tiles[x][y] = temp;

    pattern3(board);
    pattern2(board);
    pattern1(board);

}


// 보드를 변화시키고 화면에 반영하는 예제 코드
void testRemove(Board *board)
{
    int i, k, n = 3;

    for (k = 0; k < n; k++)
        board->tiles[5 - k][5] = 0;  // 타일 값이 0일 경우 폭발 그림이 출력된다
    display();  // 화면에 변화된 보드를 그린다
    Sleep(300); // 너무 빠르면 과정이 안보이므로 적당한 시간동안 기다린다
    for (i = 0; i < n; i++) {
        for (k = 5; k > 0; k--) {
            board->tiles[k][5] = board->tiles[k - 1][5];
        }
        board->tiles[0][5] = rand() % board->nitems + 1;
        display();  // 화면에 변화된 보드를 그린다. 이 함수를 호출하지 않으면 
		            // 내용이 변화되어도 화면에 나타나지 않는다.
        Sleep(100); // 너무 빠르면 과정이 안보이므로 적당한 시간동안 기다린다
    }
}



int main(int argc, char** argv)
{
    Board board;

    gameInit(&board);
    gameStart(&board);

    return 0;
}
