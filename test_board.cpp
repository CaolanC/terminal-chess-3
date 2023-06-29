#include <iostream>

using namespace std;

class Board {
    public:
    int board[8][8] = {};

    void createBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                board[i][j] = 1;
            };
        };
    };

    void printBoard()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << board[i][j];
            };
        };        
    };

};

int main() {

    Board board;
    board.createBoard();
    board.printBoard();

    return 0;

}