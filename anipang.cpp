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
	// ������ ���忡�� 3�� �̻� ���ӵ� ���� ������ ������ �Ѵ�
}


void gameInit(Board *board)
{
    srand((unsigned)time(0));
    mkBoard(board, XSIZE, YSIZE, NUM_ITEM);
}

void pattern1(Board* board) {
    //����
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
    //����
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
    //����
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
// curr: ���콺�� Ŭ���� Ÿ�� ��ġ�� �˷��ش�.
// move: ���콺�� ������ ������ �˷��ش�. (0, 1), (0, -1), (1, 0), (-1, 0) ���� �ϳ��̴�.
void mouseMotion(Board* board, int tile[2], int move[2])
{
    int x, y;
    // ���콺�� �̿��Ͽ� Ÿ���� �������� �� �ش� ������ �����ؾ� �Ѵ�
    printf("(%d, %d) move by (%d, %d)\n", tile[0], tile[1], move[0], move[1]); // ����� �ڵ�. ������ �˴ϴ�.
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


// ���带 ��ȭ��Ű�� ȭ�鿡 �ݿ��ϴ� ���� �ڵ�
void testRemove(Board *board)
{
    int i, k, n = 3;

    for (k = 0; k < n; k++)
        board->tiles[5 - k][5] = 0;  // Ÿ�� ���� 0�� ��� ���� �׸��� ��µȴ�
    display();  // ȭ�鿡 ��ȭ�� ���带 �׸���
    Sleep(300); // �ʹ� ������ ������ �Ⱥ��̹Ƿ� ������ �ð����� ��ٸ���
    for (i = 0; i < n; i++) {
        for (k = 5; k > 0; k--) {
            board->tiles[k][5] = board->tiles[k - 1][5];
        }
        board->tiles[0][5] = rand() % board->nitems + 1;
        display();  // ȭ�鿡 ��ȭ�� ���带 �׸���. �� �Լ��� ȣ������ ������ 
		            // ������ ��ȭ�Ǿ ȭ�鿡 ��Ÿ���� �ʴ´�.
        Sleep(100); // �ʹ� ������ ������ �Ⱥ��̹Ƿ� ������ �ð����� ��ٸ���
    }
}



int main(int argc, char** argv)
{
    Board board;

    gameInit(&board);
    gameStart(&board);

    return 0;
}
