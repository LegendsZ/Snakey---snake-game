#pragma once
#include "pmain.h"
#include <Windows.h> // needed to read input

struct gameMain {
private:
    pmain snake; //should be remade so that snake head is included in snake (idk why it's not atm)
    char** data;
    bool active;
    const int width;
    const int height;
    int snackX;
    int snackY;
    int refreshRate;

    void logicGame() {
        //logic goes here
        randomizeSnack(); //if new snack is needed
    }
    void randomizeSnack() {
        srand(time(0));//used for randomizing values
        snackX = (rand() % (width - 2)) + 1;
        snackY = (rand() % (height - 2)) + 1;
    }

    void moveSnake(int xChange, int yChange) {
        const int* tempHeadPos = snake.getPoisition();
        int iX = tempHeadPos[0];
        int iY = tempHeadPos[1];

        snake.setPosition(tempHeadPos[0] + xChange, tempHeadPos[1] + yChange);

        data[tempHeadPos[1] + yChange][tempHeadPos[0] + xChange] = '0';


        int tailCount = snake.getTailCount();
        snake.removeTailPosition(tailCount - 1, data);
        snake.addTailPosition(tempHeadPos[0], tempHeadPos[1], 0);
        data[iY][iX] = 'o';

        //for (int i = snake.getTailCount() - 1; i >= 0; i--) {
        //    int tempX = tempTailPos[i][0]; //switch if need be
        //    int tempY = tempTailPos[i][1];    
        //}

    }
public:
    gameMain(const int& widthG, const int& heightG, const int& xP, const int& yP, const int& refRate) :
        width(widthG), height(heightG), snake(xP, yP), refreshRate(refRate), active(true) //mainhead allocated on stack
    {

        data = new char* [height]; //allocated on heap
        for (int i = 0; i < height; i++) {
            data[i] = new char[width];
        }

        for (int i = 0; i < height; i++) {
            for (int k = 0; k < width; k++) {

                if (i == snake.getPoisition()[1] && k == snake.getPoisition()[0]) {
                    data[i][k] = '0';
                }
                else if (k == 0 || k == width - 1) {
                    data[i][k] = '|';
                }
                else if (i == 0 || i == height - 1) {
                    data[i][k] = '-';
                }
                else {
                    data[i][k] = ' ';
                }
            }
        }
        int** positions = snake.getTailPositions();

        for (int i = 0; i < snake.getTailCount(); i++) {
            data[positions[i][1]][positions[i][0]] = 'o';
        }

        randomizeSnack();
        data[snackY][snackX] = 'X';
    }

    void drawGame() const {
        system("CLS");
        for (int i = 0; i < height; i++) {
            for (int k = 0; k < width; k++) {
                std::cout << data[i][k];
                if (k == width - 1) {
                    std::cout << "\n";
                }
            }
        }
    }

    bool getStatus() const {
        return active;
    }

    void readGameInput() {
        if (GetKeyState('W') && 0x8000) {
            moveSnake(0, -1);
            drawGame();
            //system("pause");
        }
        else if (GetKeyState('A') && 0x8000) {
            moveSnake(-1, 0);
            drawGame();
            //system("pause");
        }
        else if (GetKeyState('S') && 0x8000) {
            moveSnake(0, 1);
            drawGame();
            //system("pause");
        }
        else if (GetKeyState('D') && 0x8000) {
            moveSnake(1, 0);
            drawGame();
            //system("pause");
        }
    }

    friend int main();
};