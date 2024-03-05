#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector> 
#include <fstream>
#include <sstream>
using namespace std;

string RESULTS_FILE_NAME = "wyniki.txt";
int MAX_RESULTS_IN_FILE = 10;

void HideCursor()
{
    ::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo(hConsoleOut, &hCCI);
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
class Player {
    int x;
    int y;
    int lastMoveTime;
    HANDLE h;

public:
    Player(int x, int y) {
        this->x = x;
        this->y = y;
        lastMoveTime = 0;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Move(char choice, int boardWidth, int boardHeight) {
        int newX = x;
        int newY = y;

        switch (choice) {
        case 'w':
            newY--;
            break;
        case 's':
            newY++;
            break;
        case 'd':
            newX++;
            break;
        case 'a':
            newX--;
            break;
        }

        if (newX >= 1 && newX < boardWidth - 1 && newY >= 1 && newY < boardHeight - 1) {
            x = newX;
            y = newY;
        }
    }

    void DrawPlayer() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        int decimalCode = 220;
        char character = static_cast<char>(decimalCode);
        SetConsoleCursorPosition(h, coord);
        SetConsoleTextAttribute(h, 14);
        cout << character;
        SetConsoleTextAttribute(h, 7);
    }

    void ClearPreviousPosition() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(h, coord);
        cout << ' ';
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getLastMoveTime() {
        return lastMoveTime;
    }
};

class Board {
    int width;
    int height;
    HANDLE h;

public:
    Board(int width, int height) {
        this->width = width;
        this->height = height;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Draw() {
        COORD coord;
        int decimalCode = 219;
        char character = static_cast<char>(decimalCode);
        SetConsoleTextAttribute(h, 9);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                coord.X = i;
                coord.Y = j;
                SetConsoleCursorPosition(h, coord);
                if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                    cout << character;
                }
                else {
                    cout << ' ';
                }
            }
        }
        SetConsoleTextAttribute(h, 7);
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }
};

class Lava {
    int x;
    int y;
    HANDLE h;

public:
    Lava(int x, int y) {
        this->x = x;
        this->y = y;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        int decimalCode = 219;
        char character = static_cast<char>(decimalCode);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        ClearPreviousPosition();
        SetConsoleTextAttribute(h, 12);
        cout << character;
        SetConsoleTextAttribute(h, 7);
    }
    void ClearPreviousPosition() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(h, coord);
        cout << ' ';
    }


    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class Opponent {
    int x;
    int y;
    int direction;
    int lastMoveTime;
    HANDLE h;

public:
    Opponent(int x, int y) {
        this->x = x;
        this->y = y;
        direction = 1;
        lastMoveTime = 0;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        int decimalCode = 219;
        char character = static_cast<char>(decimalCode);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        SetConsoleTextAttribute(h, 13);
        cout << character;
        SetConsoleTextAttribute(h, 7);
    }
    void Draw1() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        int decimalCode = 219;
        char character = static_cast<char>(decimalCode);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        SetConsoleTextAttribute(h, 10);
        cout << character;
        SetConsoleTextAttribute(h, 7);
    }

    void ClearPreviousPosition() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(h, coord);
        cout << ' ';
    }

    void Move(int w) {
        int currentTime = GetTickCount();
        ClearPreviousPosition();
        x = x + direction;
        if (x == w - 3) {
            direction = -1;
        }
        if (x == 2) {
            direction = 1;
        }
        Draw();
        lastMoveTime = currentTime;
    }
    void MoveUD(int h) {
        ClearPreviousPosition();
        y = y + direction;
        if (y == h - 2) {
            direction = -1;
        }
        if (y == 1) {
            direction = 1;
        }
        Draw1();
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getLastMoveTime() {
        return lastMoveTime;
    }
};

class Coin {
    int x;
    int y;
    HANDLE h;

public:
    Coin(int x, int y) {
        this->x = x;
        this->y = y;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void Draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(h, coord);
        SetConsoleTextAttribute(h, 10);
        cout << "$";
        SetConsoleTextAttribute(h, 7);
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};


void DrawMenu() {

    cout << R"(
$$$$$$$\                       $$\     $$\                                           
$$  __$$\                      $$ |    $$ |                                          
$$ |  $$ | $$$$$$\   $$$$$$\ $$$$$$\   $$$$$$$\         $$$$$$\  $$\   $$\ $$$$$$$\  
$$ |  $$ |$$  __$$\  \____$$\\_$$  _|  $$  __$$\       $$  __$$\ $$ |  $$ |$$  __$$\ 
$$ |  $$ |$$$$$$$$ | $$$$$$$ | $$ |    $$ |  $$ |      $$ |  \__|$$ |  $$ |$$ |  $$ |
$$ |  $$ |$$   ____|$$  __$$ | $$ |$$\ $$ |  $$ |      $$ |      $$ |  $$ |$$ |  $$ |
$$$$$$$  |\$$$$$$$\ \$$$$$$$ | \$$$$  |$$ |  $$ |      $$ |      \$$$$$$  |$$ |  $$ |
\_______/  \_______| \_______|  \____/ \__|  \__|      \__|       \______/ \__|  \__|                                                                                                                                                                  
)";
    cout << endl;
    cout << "1. Start the game" << endl;
    cout << "2. Ranking" << endl;
    cout << "3. End the game" << endl;
}

int touchLava(int x, int y) {
    if ((x == 10 && y == 10) || (x == 15 && y == 10) || (x == 20 && y == 10) || (x == 25 && y == 10) || (x == 30 && y == 10) || (x == 35 && y == 10) || (x == 40 && y == 10) || (x == 45 && y == 10) || (x == 50 && y == 10) || (x == 55 && y == 10)) {
        COORD coord;
        coord.X = 0;
        coord.Y = 23;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        system("cls");
        cout << "It was lava, you died!";
        cout << endl;
        return 1;
    }
    return 0;
}

void showScore(int coinCounter) {
    COORD coord;
    coord.X = 63;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Score: " << coinCounter;
}

vector<string> readResults() {
    ifstream infile(RESULTS_FILE_NAME);
    string line;
    vector<string> dane;
    while (getline(infile, line))
    {
        istringstream iss(line);
        dane.push_back(line);
    }
    infile.close();
    return dane;
}

void printResultsFromFile() {
    vector<string> wyniki = readResults();
    cout << "List of best players: " << endl << endl;
    int i = 1;
    for (std::vector<string>::iterator it = wyniki.begin(); it != wyniki.end(); ++it) {
        cout << i++ << ". " << *it << endl;
    }
    cout << endl;
    cout << "Press any button to back";
}

int getPlayerScoreFromFileLine(string line) {
    string wynik_g(line.substr(line.rfind(" ") + 1));
    int wynik_gracza = stoi(wynik_g);
    return wynik_gracza;
}

string podajNazweGracza() {
    string nazwagracza;
    cout << "Press player name: ";
    getline(cin, nazwagracza);
    return nazwagracza;
}

void saveScore(int wynikGry) {
    vector<string> wyniki = readResults();
    if (wyniki.empty()) {

        ofstream myfile;
        myfile.open(RESULTS_FILE_NAME);
        string nazwagracza = podajNazweGracza();
        myfile << nazwagracza;
        myfile << " ";
        myfile << wynikGry;
        myfile << endl;
        return;
    }

    string ostatnigracz = wyniki.back();
    int worstScoreInResultList = getPlayerScoreFromFileLine(ostatnigracz);
    if (worstScoreInResultList >= wynikGry && wyniki.size() >= MAX_RESULTS_IN_FILE) { //bierzemy 10 ostatnich wynikow graczy
        return;
    }

    string nazwagracza = podajNazweGracza();
    ofstream myfile;
    myfile.open(RESULTS_FILE_NAME);
    bool czyDodanoNowyWynikDoPliku = false;
    int ktoryGraczNaLiscie = 0;
    for (std::vector<string>::iterator it = wyniki.begin(); it != wyniki.end(); ++it) {
        if (ktoryGraczNaLiscie >= MAX_RESULTS_IN_FILE) {
            break;
        }
        int wynik_gracza = getPlayerScoreFromFileLine(*it);
        if (wynik_gracza <= wynikGry && czyDodanoNowyWynikDoPliku == false) {
            czyDodanoNowyWynikDoPliku = true;
            myfile << nazwagracza;
            myfile << " ";
            myfile << wynikGry;
            myfile << endl;
            ktoryGraczNaLiscie++;
        }
        if (ktoryGraczNaLiscie >= MAX_RESULTS_IN_FILE) {
            break;
        }
        myfile << *it;
        myfile << endl;
        ktoryGraczNaLiscie++;
    }
    myfile.close();
}
class Alien {
    int x;
    int y;
    int moveDelay;
    int lastMove;
    HANDLE h;

public:
    Alien(int x, int y, int moveDelay = 200) {
        this->x = x;
        this->y = y;
        this->moveDelay = moveDelay;
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        lastMove = 0;
    }

    void Draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        int decimalCode = 219;
        char character = static_cast<char>(decimalCode);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        SetConsoleTextAttribute(h, 11); // You can set a different color for the alien.
        cout << character;
        SetConsoleTextAttribute(h, 7);
    }

    void MoveTowardsPlayer(int playerX, int playerY) {
        int currentTime = GetTickCount();
        if (currentTime - lastMove >= moveDelay) {
            ClearPreviousPosition();
            if (x < playerX) {
                x++;
            }
            else if (x > playerX) {
                x--;
            }
            if (y < playerY) {
                y++;
            }
            else if (y > playerY) {
                y--;
            }
            Draw();
            lastMove = currentTime;
        }
    }

    void ClearPreviousPosition() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(h, coord);
        cout << ' ';
    }
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
    int get() {
        return moveDelay;
    }
};



int main() {
    bool startGame = false;
    vector<Lava> lavas;
    int coinCounter = 0;
    bool inMenu = true;
    char choice = ' ';
    Board board(60, 20);
    Player player(5, 10);
    vector<Coin> coins;
    Alien alien(30, 15, 400);
    Opponent opponent(6, 2);
    Opponent opponent1(8, 3);
    Opponent opponent2(10, 4);
    Opponent opponent3(12, 5);
    Opponent opponent4(6, 17);
    Opponent opponent5(8, 16);
    Opponent opponent6(10, 15);
    Opponent opponent7(12, 14);
    Opponent opponent8(2, 2);
    Opponent opponent9(57, 2);
    Lava lava(10, 10);
    Lava lava1(15, 10);
    Lava lava2(20, 10);
    Lava lava3(25, 10);
    Lava lava4(30, 10);
    Lava lava5(35, 10);
    Lava lava6(40, 10);
    Lava lava7(45, 10);
    Lava lava8(50, 10);
    Lava lava9(55, 10);
    HideCursor();
    int lastPlayerMoveTime = 0;
    int playerMoveDelay = 10;
    lavas.push_back(lava);
    lavas.push_back(lava1);
    lavas.push_back(lava2);
    lavas.push_back(lava3);
    lavas.push_back(lava4);
    lavas.push_back(lava5);
    lavas.push_back(lava6);
    lavas.push_back(lava7);
    lavas.push_back(lava8);
    lavas.push_back(lava9);
    while (true) {
        if (inMenu) {
            DrawMenu();
            inMenu = false;
        }
        if (_kbhit()) {
            choice = _getch();
            switch (choice) {
            case '1':
                system("cls");
                board.Draw();
                for (Lava& lava : lavas) {
                    lava.Draw();
                }
                player.DrawPlayer();
                startGame = true;
                break;
            case '2':
                startGame = false;
                system("cls");
                printResultsFromFile();
                _getch();
                system("cls");
                DrawMenu();
                break;
            case '3':
                COORD coord;
                coord.X = 0;
                coord.Y = 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
                system("cls");
                cout << "Game ended";
                cout << endl;
                return 0;
            default:
                if (startGame) {
                    int currentTime = GetTickCount();
                    if (currentTime - lastPlayerMoveTime >= playerMoveDelay) {
                        player.ClearPreviousPosition();
                        player.Move(choice, board.getWidth(), board.getHeight());
                        player.DrawPlayer();
                        int result = touchLava(player.getX(), player.getY());
                        if (result == 1) {
                            saveScore(coinCounter);
                            coinCounter = 0;
                            startGame = false;
                            inMenu = true;
                            return 0;
                        }

                        lastPlayerMoveTime = currentTime;
                    }
                }
            }
        }
        if (startGame) {
            alien.MoveTowardsPlayer(player.getX(), player.getY());

            if (player.getX() == alien.getX() && player.getY() == alien.getY()) {
                system("cls");
                cout << "You died";
                cout << endl;
                saveScore(coinCounter);
                coinCounter = 0;
                startGame = false;
                inMenu = true;
                return 0;
            }

            for (Lava& lava : lavas) {
                if (abs(alien.getX() - lava.getX()) <= 2 && abs(alien.getY() - lava.getY()) <= 2) {
                   if (!(alien.getX() == lava.getX() && alien.getY() == lava.getY())) {
                        for (Lava& lava : lavas) {
                            lava.Draw();
                        }
                    }
                }


            }

        }
        if (coins.empty() && startGame) {
            srand(static_cast<unsigned>(time(0)));
            int numCoins = 6;

            for (int i = 0; i < numCoins; i++) {
                int x = 1 + rand() % (board.getWidth() - 2);
                if (x == 10 || x == 15 || x == 20 || x == 25 || x == 30 || x == 35 || x == 40 || x == 45 || x == 50 || x == 55) {
                    x = 1 + rand() % (board.getWidth() - 2);
                }
                int y = 1 + rand() % (board.getHeight() - 2);
                if (y == 10) {
                    y = 1 + rand() % (board.getHeight() - 2);
                }
                coins.push_back(Coin(x, y));
            }
        }
        for (size_t i = 0; i < coins.size(); i++) {
            if (startGame) {
                coins[i].Draw();
            }
            if (player.getX() == coins[i].getX() && player.getY() == coins[i].getY()) {
                coinCounter++;
                showScore(coinCounter);
                coins.erase(coins.begin() + i);
            }
        }

        int currentTime = GetTickCount();
        if (startGame && currentTime - opponent.getLastMoveTime() >= (playerMoveDelay + 40)) {
            opponent.Move(board.getWidth());
            opponent1.Move(board.getWidth());
            opponent2.Move(board.getWidth());
            opponent3.Move(board.getWidth());
            opponent4.Move(board.getWidth());
            opponent5.Move(board.getWidth());
            opponent6.Move(board.getWidth());
            opponent7.Move(board.getWidth());
            opponent8.MoveUD(board.getHeight());
            opponent9.MoveUD(board.getHeight());
            if (player.getX() == opponent.getX() && player.getY() == opponent.getY() || player.getX() == opponent1.getX() && player.getY() == opponent1.getY() || player.getX() == opponent2.getX() && player.getY() == opponent2.getY() || player.getX() == opponent3.getX() && player.getY() == opponent3.getY()) {
                system("cls");
                cout << "You died";
                cout << endl;
                saveScore(coinCounter);
                coinCounter = 0;
                startGame = false;
                inMenu = true;
                return 0;
            }
            else if (player.getX() == opponent4.getX() && player.getY() == opponent4.getY() || player.getX() == opponent5.getX() && player.getY() == opponent5.getY() || player.getX() == opponent6.getX() && player.getY() == opponent6.getY() || player.getX() == opponent7.getX() && player.getY() == opponent7.getY()) {
                system("cls");
                cout << "You died";
                cout << endl;
                saveScore(coinCounter);
                coinCounter = 0;
                startGame = false;
                inMenu = true;
                return 0;
            }
            else if (player.getX() == opponent8.getX() && player.getY() == opponent8.getY() || player.getX() == opponent9.getX() && player.getY() == opponent9.getY()) {
                system("cls");
                cout << "You die";
                cout << endl;
                saveScore(coinCounter);
                coinCounter = 0;
                startGame = false;
                inMenu = true;
               
            }
        }
    }
}
