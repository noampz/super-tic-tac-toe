#include <iostream>

class Board
{
    private:

    // 0 is nothing
    // 1 is x
    // -1 is o

    /*  [1,2,3]
        [4,5,6]
        [7,8,9]  */
    int board[3][3];
    
    //returns 'x' if xo is 1 or 'o' if xo is -1
    //and ' ' if xo 
    char getXO(int xo);
    public:
    Board();
    // x == 1
    // o == -1
    // returns true if succeded false if not
    bool setSquare(int num_of_squere , int xo);

    // x == 1
    // nothing == 0
    // o == -1
    int getSquare(int num_of_squere);
    int getSquare(int row, int column);
    // the first []
    // 0 indexed
    int getRowByNumOfSquare(int num_of_square) {return (num_of_square-1)/3;}
    // 0 indexed
    // the second []
    int getColumnByNumOfSquare(int num_of_square) {return (num_of_square-1)%3;}

    void printBoard();
};