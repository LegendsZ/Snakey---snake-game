#pragma once
#include <iostream>

#define DEFAULT_TAIL 3

struct pmain {
private:
    int x, y;
    int tailCount;
    int** positions;

    int* genCoords(const int& x, const int& y) const {
        int xallowed[] = { x - 1, x, x + 1 };
        int yallowed[] = { y - 1, y, y + 1 };
        int pickX = x;
        int pickY = y;
        //while (true) {
        srand(time(0));//used for randomizing values
        pickX = xallowed[rand() % 2];
        if (pickX != x) {
            pickY = y;
            //break;
        }
        else {
            while (pickY == y) {
                pickY = yallowed[rand() % 2]; //may pick a slot thats occupied
            }
            //break;
        }
        //}
        return new int[] {pickX, pickY};
    }
public:
    
    pmain(const int& xG, const int& yG) : x(xG), y(yG), tailCount(DEFAULT_TAIL) {
        positions = new int* [tailCount];
        int cx = x;
        int cy = y;
        for (int i = 0; i < tailCount; i++) {
            positions[i] = new int[2];
            int* vals = genCoords(cx, cy);
            positions[i][0] = vals[0];
            positions[i][1] = vals[1];
            cx = vals[0];
            cy = vals[1];
        }
    };

    void setPosition(const int& xG, const int& yG) {
        x = xG;
        y = yG;
    }
    void setTailPositions(const int&& positionsGiven) {

        

    }

    void removeTailPosition(const int& index, char** data) {
        int xLast = positions[tailCount-1][0];
        int yLast = positions[tailCount-1][1];
        tailCount--;

        int** tempPositions = new int* [tailCount];
        int count = 0;
        for (int i = 0; i < tailCount + 1; i++) {
            if (i != index) {
                tempPositions[count] = new int[2];
                tempPositions[count][0] = positions[i][0];
                tempPositions[count++][1] = positions[i][1];
            }
            //delete[] positions[i]; //should already be implied
        }
        positions = tempPositions;

        data[yLast][xLast] = ' ';
    }

    void addTailPosition(const int& xG, const int& yG, const int& index) {
        int xLast = positions[tailCount - 1][0];

        tailCount++;
        int** tempPositions = new int* [tailCount];

        int count = 0;
        for (int i = 0; i < tailCount; i++) {
            tempPositions[i] = new int[2];
            if (i != index) {
                tempPositions[i][0] = positions[count][0];
                tempPositions[i][1] = positions[count++][1];
            }
            else {
                tempPositions[i][0] = xG;
                tempPositions[i][1] = yG;
            }
            //delete[] positions[i]; //should already be implied
        }
        positions = tempPositions;
    }

    int* getPoisition() const {
        return new int[] {x, y};
    }
    int getTailCount() const {
        return tailCount;
    }
    int** getTailPositions() const {
        return positions;
    }
};