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
#include <string>

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

    int origCollumn;
    int destCollumn;
    int origRow;
    int destRow;

    void moveData(int a1, int a2, int b1, int b2)
    {
        origCollumn = a1;
        destCollumn = b1;
        origRow = a2;
        destRow = b2;
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
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Piece piece;

                    if (i == 1)
                    {
                        piece.create_piece(1, false);
                    } else if (i == 0) {

                        if (j == 0 || j == 7) {
                            piece.create_piece(3, false);
                        } else if (j == 1 || j == 6) {
                            piece.create_piece(2, false);
                        } else if (j == 2 || j == 5) {
                            piece.create_piece(4, false);
                        } else if (j == 3) {
                            piece.create_piece(5, false);
                        } else if (j == 4) {
                            piece.create_piece(6, false);
                        };
                    } else if (i == 7) {

                        if (j == 0 || j == 7) {
                            piece.create_piece(3, true);
                        } else if (j == 1 || j == 6) {
                            piece.create_piece(2, true);
                        } else if (j == 2 || j == 5) {
                            piece.create_piece(4, true);
                        } else if (j == 3) {
                            piece.create_piece(5, true);
                        } else if (j == 4) {
                            piece.create_piece(6, true);
                        };
                    } else if (i == 6) {

                        piece.create_piece(1, true);
                    } else {

                        piece.create_piece(0, true);
                    };

                    board[i][j] = piece;
                    }
            };
            //reverse(begin(board), end(board));
        };

        bool isInBoard(int row, int collumn) {
            if ((row >= 0 && row < 8) && (collumn >= 0 && row < 8))
            {
                return true;
            }
            return false;
        };

        bool Empty(int collumn, int row){
            if (board[collumn][row].piece_name) {
                return false;
            };
            return true;
        };

        string bg_color;
        int row_count = 0;

        void printBoard() {

            string colorOne = "\033[46m";
            string colorTwo = "\033[45m";

            int colorTracker = 0;
            string color;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {

                    if (colorTracker % 2) {
                        color = colorOne;
                    } else {
                        color = colorTwo;
                    };

                    cout << color << board[i][j].unicode_char; // << board[i][j].white;
                    colorTracker++;
                };
                cout << "\033[40m\n";
                colorTracker++;
            };

        };

        void doMove(int origCollumn, int origRow, int destCollumn, int destRow)
        {
            Piece empty;
            empty.create_piece(0, true);
            board[destCollumn][destRow] = board[origCollumn][origRow];
            board[origCollumn][origRow] = empty;
            board[destCollumn][destRow].hasMoved = true;
        };

        vector<Move> legalMoves(bool white) {
            vector<Move> moves;

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {

                    vector<Move> pieceMoves;

                    if (white == true && !(Empty(i, j)))
                    {
                        Piece currentPiece = board[i][j];

                        int currentName = currentPiece.piece_name;
                        bool currentBool = currentPiece.white;

                        if (currentName == 1 && currentBool == white)
                        {
                            pieceMoves = pawn_movement(i, j, white);

                        } else if ((currentName == 2) && (currentBool == white))
                        {
                            pieceMoves = knight_movement(i, j, white);

                        } else if ((currentName == 3) && (currentBool == white))
                        {
                            pieceMoves = rook_movement(i, j, white);

                        } else if ((currentName == 4) && (currentBool == white))
                        {
                            pieceMoves = bishop_movement(i, j, white);

                        } else if ((currentName == 5) && (currentBool == white))
                        {
                            pieceMoves = rook_movement(i, j, white);

                            vector<Move> tempMoves = bishop_movement(i, j, white);

                            for (Move i: tempMoves) {
                                pieceMoves.push_back(i);
                            }
                        } else if ((currentName == 6) && (currentBool == white))
                        {
                            pieceMoves = king_movement(i, j, white);

                        };
                    };

                    if ((white == false) && !(Empty(i, j)))
                    {


                        Piece currentPiece = board[i][j];

                        if (currentPiece.piece_name == 1 && currentPiece.white == white)
                        {
                            pieceMoves = pawn_movement(i, j, white);
                        } else if ((currentPiece.piece_name == 2) && (currentPiece.white == white))
                        {
                            pieceMoves = knight_movement(i, j, white);
                        };
                    };
                    for (Move i : pieceMoves)
                    {
                        moves.push_back(i);
                    }
                };
            };

            cout << "Printing Moves:\n";
            for (Move i : moves)
            {
                cout << i.origCollumn << "," << i.origRow << " - " << i.destCollumn << "," << i.destRow << "\n";
            };
            return moves;            
        };

        vector<Move> king_movement(int collumn, int row, bool white)
        {
            vector<Move> kMoves;
            for (int i = collumn - 1; i <= collumn + 1; i++)
            {
                if (isInBoard(i, row + 1) && (Empty(i, row + 1) || board[i][row + 1].white != white)) {
                    Move kMove;
                    kMove.moveData(collumn, row, i, row + i);
                    kMoves.push_back(kMove);
                };
            };

            for (int i = collumn - 1; i <= collumn + 1; i++)
            {
                if (isInBoard(i, row - 1) && (Empty(i, row - 1) || board[i][row - 1].white != white)) {
                    Move kMove;
                    kMove.moveData(collumn, row, i, row - i);
                    kMoves.push_back(kMove);
                };
            };

            if (isInBoard(collumn - 1, row) && (Empty(collumn - 1, row) || board[collumn - 1][row].white != white)) {
                Move kMove;
                kMove.moveData(collumn, row, collumn - 1, row);
                kMoves.push_back(kMove);
                };

            if (isInBoard(collumn + 1, row) && (Empty(collumn + 1, row) || board[collumn + 1][row].white != white)) {
                Move kMove;
                kMove.moveData(collumn, row, collumn + 1, row);
                kMoves.push_back(kMove);
                };
            return kMoves;
        }

        vector<Move> pawn_movement(int collumn, int row, bool white)
        {
            vector<Move> pMoves;

            int dir;

            if (white)
            {
                dir = -1;
            } else {
                dir = 1;
            };
            if ((Empty(collumn + (1 * dir), row)))
            {
                Move move;
                move.moveData(collumn, row, collumn + (1 * dir), row);
                pMoves.push_back(move);
                if (Empty(collumn + (2 * dir), row) && !(board[collumn][row].hasMoved))
                {
                    Move move;
                    move.moveData(collumn, row, collumn + (2 * dir), row);
                    pMoves.push_back(move);
                };
            };

            return pMoves;

        };

        bool indexColor(int collumn, int row)
        {
            return board[collumn][row].white;
        };

        vector<Move> knight_movement(int collumn, int row, bool white)
        {

            vector<Move> nMoves;
            if (isInBoard(collumn + 2, row + 1) && (Empty(collumn + 2, row + 1) || indexColor(collumn + 2, row + 1) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn + 2, row + 1);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn + 2, row - 1) && (Empty(collumn + 2, row - 1) || indexColor(collumn + 2, row - 1) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn + 2, row - 1);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn + 1, row + 2) && (Empty(collumn + 1, row + 2) || indexColor(collumn + 1, row + 2) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn + 1, row + 2);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn + 1, row - 2) && (Empty(collumn + 1, row - 2) || indexColor(collumn + 1, row - 2) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn + 1, row - 2);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn - 2, row + 1) && (Empty(collumn - 2, row + 1) || indexColor(collumn - 2, row + 1) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn - 2, row + 1);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn - 2, row - 1) && (Empty(collumn - 2, row - 1) || indexColor(collumn - 2, row - 1) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn - 2, row - 1);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn -1, row + 2) && (Empty(collumn - 1, row + 2) || indexColor(collumn - 1, row + 2) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn - 1, row + 2);
                nMoves.push_back(kMove);
            };
            if (isInBoard(collumn - 1, row - 2) && (Empty(collumn - 1, row - 2) || indexColor(collumn - 1, row - 2) != white))
            {
                Move kMove;
                kMove.moveData(collumn, row, collumn - 1, row - 2);  
                nMoves.push_back(kMove);
            };

            return nMoves;
        };

        vector<Move> rook_movement(int collumn, int row, bool white)
        {
            vector<Move> rMoves;

            // Up movment

            for (int i = row + 1; i < 8; i++)
            {
                Piece currentPiece = board[collumn][i];
                if (Empty(collumn, i))
                {
                    Move rMove;
                    rMove.moveData(collumn, row, collumn, i);
                    rMoves.push_back(rMove);

                } else if (currentPiece.white != white)
                {
                    Move rMove;
                    rMove.moveData(collumn, row, collumn, i);
                    rMoves.push_back(rMove);                    
                    break;
                } else
                {
                    break;
                };
            };

            // Down movement

            for (int i = row - 1; i >= 0; i--)
            {
                Piece currentPiece = board[collumn][i];
                if (Empty(collumn, i))
                {
                    Move rMove;
                    rMove.moveData(collumn, row, collumn, i);
                    rMoves.push_back(rMove);

                } else if (currentPiece.white != white)
                {
                    Move rMove;
                    rMove.moveData(collumn, row, collumn, i);
                    rMoves.push_back(rMove);                    
                    break;
                } else
                {
                    break;
                };
            };

            // Right Movement
            for (int i = collumn + 1; i < 8; i++)
            {
                Piece currentPiece = board[i][row];
                if (Empty(i, row))
                {
                    Move rMove;
                    rMove.moveData(i, row, i, row);
                    rMoves.push_back(rMove);

                } else if (currentPiece.white != white)
                {
                    Move rMove;
                    rMove.moveData(i, row, i, row);
                    rMoves.push_back(rMove);                    
                    break;
                } else
                {
                    break;
                };
            };

            // Left Movement

            for (int i = collumn - 1; i >= 0; i--)
            {
                Piece currentPiece = board[i][row];
                if (Empty(i, row))
                {
                    Move rMove;
                    rMove.moveData(i, row, i, row);
                    rMoves.push_back(rMove);

                } else if (currentPiece.white != white)
                {
                    Move rMove;
                    rMove.moveData(i, row, i, row);
                    rMoves.push_back(rMove);                    
                    break;
                } else
                {
                    break;
                };
            };


            return rMoves;
        };

        vector<Move> bishop_movement(int collumn, int row, bool white)
        {
            vector<Move> bMoves;

            //Up right movement

            for (int i = 1; collumn - i >= 0 && row + i < 8; i++)
            {
                Piece currentPiece = board[collumn - i][row + i];
                if (Empty(collumn - i, row + i))
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn - i, row + i);
                    bMoves.push_back(bMove);

                } else if (currentPiece.white != white)
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn - i, row + i);
                    bMoves.push_back(bMove);                    
                    break;
                } else
                {
                    break;
                };                
            };

            //Down right movement

            for (int i = 1; collumn + i < 8 && row + i < 8; i++)
            {
                Piece currentPiece = board[collumn + i][row + i];
                if (Empty(collumn + i, row + i))
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn + i, row + i);
                    bMoves.push_back(bMove);

                } else if (currentPiece.white != white)
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn + i, row + i);
                    bMoves.push_back(bMove);                    
                    break;
                } else
                {
                    break;
                };                
            };

            //Up left movement

            for (int i = 1; collumn - i >= 0 && row - i < 8; i++)
            {
                Piece currentPiece = board[collumn - i][row - i];
                if (Empty(collumn - i, row + i))
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn - i, row - i);
                    bMoves.push_back(bMove);

                } else if (currentPiece.white != white)
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn - i, row - i);
                    bMoves.push_back(bMove);                    
                    break;
                } else
                {
                    break;
                };                
            };

            //Down left movement

            for (int i = 1; collumn + i < 8 && row - i >= 0; i++)
            {
                Piece currentPiece = board[collumn + i][row - i];
                if (Empty(collumn + i, row + i))
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn + i, row - i);
                    bMoves.push_back(bMove);

                } else if (currentPiece.white != white)
                {
                    Move bMove;
                    bMove.moveData(i, row, collumn + i, row - i);
                    bMoves.push_back(bMove);                    
                    break;
                } else
                {
                    break;
                };                
            };

        return bMoves;

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

tuple<int, int> convertCoordinate(string coord)
{
    int letter = (coord[0] - 97);
    int number = 7 - (coord[1] - 49);

    return make_tuple(number, letter);
}
tuple<int, int, int, int> convertCoordinates(string coords) {

    string coordOrig = coords.substr(0, 2);
    string coordDest = coords.substr(3, 5);
    
    int OriginA;
    int OriginB;

    int DestinationA;
    int DestinationB;

    tie(OriginA, OriginB) = convertCoordinate(coordOrig);
    tie(DestinationA, DestinationB) = convertCoordinate(coordDest);

    return make_tuple(OriginA, OriginB, DestinationA, DestinationB);  

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
    board.printBoard();

    string input;
    cin >> input;

    int originCoordinateA;
    int originCoordinateB;
    int DestinationCoordinateA;
    int DestinationCoordinateB;  

    tie(originCoordinateA, originCoordinateB, DestinationCoordinateA, DestinationCoordinateB) = convertCoordinates(input);

    board.doMove(originCoordinateA, originCoordinateB, DestinationCoordinateA, DestinationCoordinateB);
    board.printBoard();
    board.legalMoves(true);

    // string a = "a";
    // cout << int(a[0]);


    //int index = $d\n, hello['e']

    //This is a comment
}
