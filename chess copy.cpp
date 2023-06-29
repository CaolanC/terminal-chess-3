#include <iostream>
#include <cwchar>
#include <map>
#include <cstdlib>
#include <typeinfo>
#include <cstring>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <array>
#include <vector>
#include <cmath>

using namespace std;

map<char, int> alphabetMap = {
    {'a', 0}, //  + (letterNum - 1) * 8},
    {'b', 1},
    {'c', 2},
    {'d', 3},
    {'e', 4},
    {'f', 5},
    {'g', 6},
    {'h', 7}
};

map<char, int> updateAlphabetMap(map<char, int> alphabetMap, string letterNum)
{
    for(auto i = alphabetMap.begin(); i != alphabetMap.end(); ++i)
    {
        if(i -> first == letterNum[0])
        {
            alphabetMap[letterNum[0]] = alphabetMap[letterNum[0]] + ((int)letterNum[1] - '0' - 1) * 8;
        };
    };

    return alphabetMap;
};

class Move
{
    public:

    int orig;
    int dest;

    void moveData(int origin, int destination)
    {
        orig = origin;
        dest = destination;
    };
};

class Piece
{
    public:

    int piece_name;
    string unicode_char;
    bool white;
    bool hasMoved;
    
    //wchar_t unicode_char;

    void printPiece(){
        cout << piece_name;
    };

    void create_piece(int piece, bool color)
    {
        piece_name = piece;
        white = color;
        hasMoved = false;
        switch (piece_name) {

            case 0:

            unicode_char = "  ";
            //unicode_char = L'\u265c';
            break;

            case 1:
            //unicode_char = L'\u265c';
            unicode_char = "P ";
            
            break;

            case 2:

            unicode_char = "N ";
            //unicode_char = L'\u265c';
            break;

            case 3:

            unicode_char = "R ";

            break;

            case 4:

            unicode_char = "B ";
            //unicode_char = L'\u265c';
            break;

            case 5:

            unicode_char = "Q ";
            //unicode_char = L'\u265c';
             break;

            case 6:

            unicode_char = "K ";
            //unicode_char = L'\u265c';
        } 
    };
};

class Board
{
    public:

    Piece originOriginalPiece;
    Piece destinationOriginalPiece;
    int originOriginalIndex;
    int destinationOriginalIndex;

    Piece board[8][8];

        void createBoard() {
            for (int i = 0; i < 64; i++)
            {
                Piece piece;
                if (i >= 8 && i <= 15) {

                    piece.create_piece(1, false);
                    board[i] = piece;

                } else if (i >= 48 && i <= 55){

                    piece.create_piece(1, true);
                    board[i] = piece;

                } else if (i == 56 || i == 63) {

                    piece.create_piece(3, true);
                    board[i] = piece;

                } else if (i == 57 || i == 62) {

                    piece.create_piece(2, true);
                    board[i] = piece;

                } else if (i == 58 || i == 61) {

                    piece.create_piece(4, true);
                    board[i] = piece;

                } else if (i == 59) {

                    piece.create_piece(5, true);
                    board[i] = piece;

                } else if (i == 60) {

                    piece.create_piece(6, false);
                    board[i] = piece;

                } else if (i >= 8 && i <= 15){

                    piece.create_piece(2, false);
                    board[i] = piece;

                } else if (i == 0 || i == 7) {

                    piece.create_piece(3, false);
                    board[i] = piece;

                } else if (i == 1 || i == 6) {

                    piece.create_piece(2, false);
                    board[i] = piece;

                } else if (i == 2 || i == 5) {

                    piece.create_piece(4, false);
                    board[i] = piece;

                } else if (i == 3) {

                    piece.create_piece(5, false);
                    board[i] = piece;

                } else if (i == 4) {

                    piece.create_piece(6, false);
                    board[i] = piece;
                }
                
                else {
                    piece.create_piece(0, true);
                    board[i] = piece;
                };
            };
            //reverse(begin(board), end(board));
        };

        bool isInBoard(int index) {
            if (index >= 0  && index < 63) {
                return true;
            } else {
                return false;
            };
        };

        vector<Move> pawn_movement(int index, bool side)
        {
            int dir;

            vector<Move> pawn_moves;

            if (side) {
                dir = -1;

            } else {
                dir = 1;
            };

            int mvForI = index + (8 * dir);

            if (isInBoard(mvForI) && board[mvForI].piece_name == 0)
            {
                Move moveForI;
                moveForI.moveData(index, mvForI);
                pawn_moves.push_back(moveForI);
                int mvForII = index + (16 * dir);
                if (isInBoard(mvForII) && board[mvForII].piece_name == 0)
                {
                    Move moveForII;
                    moveForII.moveData(index, mvForII);
                    pawn_moves.push_back(moveForII);
                };

                int takeLeft = index + (7 * dir);
                int takeRight = index + (9 * dir);

                if (isInBoard(takeLeft) && (board[takeLeft].piece_name != 0 && board[takeLeft].white != side))
                {
                    Move mvL;
                    mvL.moveData(index, takeLeft);
                    pawn_moves.push_back(mvL);

                } else if (isInBoard(takeRight) && (board[takeRight].piece_name != 0 && board[takeRight].white != side))
                {
                    Move mvR;
                    mvR.moveData(index, takeRight);
                    pawn_moves.push_back(mvR);
                };

            };

        return pawn_moves;

        };

        vector<Move> knight_movement(int index, bool isWhite)
        {
        vector<Move> kMoves;
        vector<int> nOffsets = {17, 15, 6, 10, -6, -10, -15, -17};
        vector<int> verifiedOffsets;

        int indexHeight = floor(index / 8);
        int indexWidth = index % 8;

        for (int i : nOffsets)
        {
            int offsetHeight = floor(i / 8);
            int offsetWidth = i % 8;
            if ((offsetHeight - 2 == indexHeight || offsetHeight + 2 == indexHeight) && (offsetWidth == indexWidth + 1 || offsetWidth == indexWidth - 1))
            {
                verifiedOffsets.push_back(i);

            } else if ((offsetHeight - 1 == indexHeight || offsetHeight + 1 == indexHeight) && (offsetWidth == indexWidth + 2 || offsetWidth == indexWidth - 2)){

                verifiedOffsets.push_back(i);
            };
        };
        
        for (int i = 0; i < 8; i++)
        {
            int new_index = index + verifiedOffsets[i];
            if (isInBoard(new_index) && (board[new_index].piece_name == 0 || board[new_index].white != isWhite)) {
                Move newMove;
                newMove.moveData(index, new_index);
                kMoves.push_back(newMove);
            };
        };

        return kMoves;

        };

        vector<Move> rook_movement(int index, bool turn)
        {

            vector<Move> rMoves;

            // Up movement
            for (int i = index + 8; i < 64; i + 8)
            {
                int pieceName = board[i].piece_name;
                int color = board[i].white;

                if (!(pieceName))
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                } else if (pieceName && color != turn)
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                    break;
                } else {
                    break;
                };
            };

            // Down Movement

            for (int i = index - 8; i >= 0; i - 8)
            {
                int pieceName = board[i].piece_name;
                int color = board[i].white;

                if (!(pieceName))
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                } else if (pieceName && color != turn)
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                    break;
                } else {
                    break;
                };
            };

            // Right Movement

            for (int i = index + 1; (i % 8) && (i < 64); i + 1)
            {
                int pieceName = board[i].piece_name;
                int color = board[i].white;

                if (!(pieceName))
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                } else if (pieceName && color != turn)
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                    break;
                } else {
                    break;
                };
            
            };

            // Left Movement

            for (int i = index - 1; (i + 1) % 8 && (i >= 0); i - 1)
            {
                int pieceName = board[i].piece_name;
                int color = board[i].white;

                if (!(pieceName))
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                } else if (pieceName && color != turn)
                {
                    Move rMove;
                    rMove.moveData(index, i);
                    rMoves.push_back(rMove);
                    break;
                } else {
                    break;
                };
            };

            return rMoves;
        };

        vector<Move> bishop_movement(int index, bool turn)
        {
            vector<Move> bMoves;
            
            int numHeight = 8 - (index % 8);

            for (int i = 1; (i < numHeight) && i >= 0 && index + (i * 9) < 64; i++)
            {
                int calc = index + (i * 9);

                int pieceName = board[calc].piece_name;
                int color = board[calc].white;

                if (!(pieceName))
                {
                    Move bMove;
                    bMove.moveData(index, calc);
                    bMoves.push_back(bMove);
                } else if (pieceName && color != turn)
                {
                    Move bMove;
                    bMove.moveData(index, i);
                    bMoves.push_back(bMove);
                    break;
                } else {
                    break;
                };
            }

            // UP RIGHT

        return bMoves;

        };

        vector<Move> turnMoves(bool turn)
        {
            
            vector<Move> moves;

            for (int i = 0; i < 64; i++)
            {

                vector<Move> pcMoves = pieceMoves(i, turn);
                for (Move j : pcMoves)
                {
                    cout << j.orig << " " << j.dest << "\n";
                    moves.push_back(j);
                };
            };

            return moves;

        };

        vector<Move> pieceMoves(int index, bool turn)
        {
            int name = board[index].piece_name;
            bool pieceColor = board[index].white;

            vector<Move> pieceMoves;

            if (name && pieceColor == turn)
                {
                    // cout << index << " Index \n";
                    switch (name)
                    {
                        case 1:
                            pieceMoves = pawn_movement(index, turn);
                        break;

                        case 2:
                            pieceMoves = knight_movement(index, turn);
                        break;

                        case 3:
                            pieceMoves = rook_movement(index, turn);
                        break;
                    };


                };

            // for (Move i : pieceMoves)
            // {
            //     cout << i.dest << "\n";
            // }

            return pieceMoves;
        };

        void doMove(int orig, int dest)
        {
            Piece piece;
            piece.create_piece(0, true);

            originOriginalPiece = board[orig];
            destinationOriginalPiece = board[dest];
            originOriginalIndex = orig;
            destinationOriginalIndex = dest;

            board[dest] = board[orig];
            board[orig] = piece;
        };

        void undoMove()
        {
            board[originOriginalIndex] = originOriginalPiece;
            board[destinationOriginalIndex] = destinationOriginalPiece;
        }

        string bg_color;
        int row_count = 0;

        void printBoard() {
            for (int i = 7; i >= 0; i--)
            {
                string row = "";
                int j = i * 8;
                for (j; j < ((i) * 8) + 8; j++) {
                    if (row_count % 2) {
                        bg_color = "\033[42m";
                    } else {
                        bg_color = "\033[44m";
                    };
                    row += (bg_color + board[j].unicode_char);
                    row_count += 1;

            };
            row_count += 1;
            cout << (row + "\033[40m\n");
            }

        };

        void printBoardArray(int index)
        {
            board[index].printPiece();
        };

};

class LegalMove
{
    public:
    string origin;
    string destination;
    LegalMove(string Origin, string Destination)
    {
        origin = Origin;
        destination = Destination;
    };

    string thisDestination()
    {
        return destination;
    };

    string thisOrigin()
    {
        return origin;
    };
};

map<string, int> doMove(void *mv, map<string, int> board)
{   
    
    return board;
};

// map<string, int> map;

// e2 (in the python dictionary) -->  52 (in the array)

// int coordToInt(string coord, int *arr)
// {
//     for(int i = 0; i < 8; i++)
//     {
//         if(i == 8 - coord[1])
//         {
//             for(int j = 0; j < 8; j++)
//             {
//                 if(j == 4) printf("%d\n", arr[i][j]);
//             };
//         };
        
//     };
// };

Board convertCoord(Board board, string coord) {
    string coordOrig = coord.substr(0, 2);
    string coordDest = coord.substr(3, 5);
    map<char, int> orig = updateAlphabetMap(alphabetMap, coordOrig);
    int origIndex = orig[coordOrig[0]];
    map<char, int> dest = updateAlphabetMap(alphabetMap, coordDest);
    int destIndex = dest[coordDest[0]];

    board.doMove(origIndex, destIndex);

    return board;
};

// bool isInBoard(int index) {
//     if (index >= 0  && index < 63) {
//         return true;
//     } else {
//         return false;
//     };
// }

void test(char **arr)
{
    for(int i = 0; i < 8; i++)
    {
        if(i == 8-2)
        {
            for(int j = 0; j < 8; j++)
            {
                if(j == 4) printf("%d\n", arr[i][j]);
            };
        };
        
    };
};

void test()
{
    float a = floor(7 / 8);
    cout << a;
}

int main(){
    Board board;

    // test();

    board.createBoard();
    // board.printBoard();    // convertCoord(" ");

    // for (int i = 0; i < 1000000; i++)
    // {
    // board.turnMoves(false);
    // }

    // while (true) {
    //     string input;
    //     cin >> input;
    //     board = convertCoord(board, input);     
    //     board.printBoard();   
    // };

    return 0;

    //int index = $d\n, hello['e']
}
