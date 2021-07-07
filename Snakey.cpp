//#include <iostream>
//#include <Windows.h>

#include "gameMain.h"

// needed to read input
//#include "gameMain.h"

#define DEFAULT_WIDTH 75
#define DEFAULT_HEIGHT 25
#define DEFAULT_REFRESH_RATE 50

//struct pmain {
//private:
//    int x, y;
//    int** positions;
//    int tailCount;
//
//    int* genCoords(const int& x, const int& y) const{
//        int xallowed[] = { x - 1, x, x + 1 };
//        int yallowed[] = { y - 1, y, y + 1 };
//        int pickX = x;
//        int pickY = y;
//        //while (true) {
//            srand(time(0));//used for randomizing values
//            pickX = xallowed[rand() % 2];
//            if (pickX != x) {
//                pickY = y;
//                //break;
//            }
//            else {
//                while (pickY == y) {
//                    pickY = yallowed[rand() % 2]; //may pick a slot thats occupied
//                }
//                //break;
//            }
//        //}
//        return new int[] {pickX, pickY};
//    }
//
//public:
//    pmain(const int& xG, const int& yG) : x(xG), y(yG), tailCount(DEFAULT_TAIL) {
//        positions = new int* [tailCount];
//        int cx = x;
//        int cy = y;
//        for (int i = 0; i < tailCount; i++) {
//            positions[i] = new int[2];
//            int* vals = genCoords(cx,cy);
//            positions[i][0] = vals[0];
//            positions[i][1] = vals[1];
//            cx = vals[0];
//            cy = vals[1];
//        }
//    };
//
//    void setPosition(int& xG, int& yG) {
//        x = xG;
//        y = yG;
//    }
//    int* getPoisition() const {
//        return new int[] {x, y};
//    }
//    int getTailCount() const {
//        return tailCount;
//    }
//    int** getTailPositions() const {
//        return positions;
//    }
//};

//struct gameMain {
//private:
//    pmain snake;
//    char** data;
//    bool active = false;
//    const int width;
//    const int height;
//    int snackX;
//    int snackY;
//    int refreshRate;
//
//    void logicGame() {
//        //logic goes here
//        randomizeSnack();
//    }
//    void randomizeSnack() {
//        srand(time(0));//used for randomizing values
//        snackX = (rand() + 1) % (width - 1);
//        snackY = (rand() + 1) % (height - 1);
//    }
//public:
//    gameMain(const int& widthG, const int& heightG, const int& xP, const int& yP, const int& refRate) :
//        width(widthG), height(heightG), snake(xP, yP), refreshRate(refRate), active(true) //mainhead allocated on stack
//    {
//
//        data = new char* [height]; //allocated on heap
//        for (int i = 0; i < height; i++) {
//            data[i] = new char[width];
//        }
//
//        for (int i = 0; i < height; i++) {
//            for (int k = 0; k < width; k++) {
//
//                if (i == snake.getPoisition()[1] && k == snake.getPoisition()[0]) {
//                    data[i][k] = '0';
//                }
//                else if (k == 0 || k == width - 1) {
//                    data[i][k] = '|';
//                }
//                else if (i == 0 || i == height - 1) {
//                    data[i][k] = '-';
//                }
//                else {
//                    data[i][k] = ' ';
//                }
//            }
//        }
//        int** positions = snake.getTailPositions();
//
//        for (int i = 0; i < snake.getTailCount(); i++) {
//            data[positions[i][1]][positions[i][0]] = 'o';
//        }
//
//        randomizeSnack();
//        data[snackY][snackX] = 'X';
//    }
//
//    void drawGame() const{
//        system("CLS");
//        for (int i = 0; i < height; i++) {
//            for (int k = 0; k < width; k++) {
//                std::cout << data[i][k];
//                if (k == width - 1) {
//                    std::cout << "\n";
//                }
//            }
//        }
//    }
//
//    bool getStatus() const{
//        return active;
//    }
//
//    void readGameInput() const{
//        if (GetKeyState('W') && 0x8000) {
//
//        }
//    }
//    
//    friend int main();
//};

int main()
{
    system("title Snakey");
    
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int refreshRate = DEFAULT_REFRESH_RATE;

    std::cout << "=========MAIN COMMANDS=========\n'1' = Exit\n'2' = Start game\n'3' = Settings\n===============================\n\n";
    while (true) {
        std::cout << "game>";
        std::string command;
        std::cin >> command;
        int cmd = std::atoi(command.c_str());

        if (cmd == 1) {
            break;
        }
        else if (cmd == 2) {
            system("CLS");
            std::cout << "Initializing data...";
            gameMain game(width, height, width/2, height/2, refreshRate);
            std::cout << "OK!\n\n";
            while (game.getStatus() == true) { //change true to gameStatus
                game.drawGame();
                game.readGameInput();

                Sleep(game.refreshRate);
            }
        }
        else if (cmd == 3) {
            std::cout << "\n=========SETTINGS=========\n'1' = Exit settings\n'2' = Change dimensions\n'3' = Change refresh rate\n" << "==========================\n\n";
            bool leave = false;
            while (true) { // game settings
                std::cout << "game>settings>";
                std::string command2;
                std::cin >> command2;
                int cmd2 = std::atoi(command2.c_str());

                switch (cmd2) 
                {
                case 1:
                    leave = true;
                    break;
                case 2: 
                    std::cout << "\nCurrent dimensions: [" << width << "],[" << height << "]\n";
                    std::cout << "FORMAT: [WIDTH],[HEIGHT]\n\n>";
                    {
                        std::string command3;
                        std::cin >> command3;
                        int comma = command3.find(',');

                        std::string splits[] = { command3.substr(0,comma), command3.substr(comma + 1,command3.length() - comma + 1) };
                        width = std::atoi(splits[0].c_str());
                        height = std::atoi(splits[1].c_str()); //implment error checks
                        std::cout << "New dimensions: [" << width << "],[" << height << "]\n\n";
                    }
                    break;
                case 3:
                    std::cout << "\nCurrent refresh rate: [" << refreshRate << "] ms\n";
                    std::cout << "FORMAT: [REFRESH RATE]\n\n>";

                    {
                        int command3;
                        std::cin >> command3; //IMPLMENT ERROR CHECKS

                        refreshRate = command3;
                        std::cout << "New refresh rate: [" << refreshRate << "] ms\n\n";
                    }

                    break;
                default:
                    std::cout << "\nERROR!\n\n";
                }

                if (leave == true) {
                    break;
                }
            } 
        }
        else {
            std::cout << "\nERROR!\n\n";
        }
    }
}
