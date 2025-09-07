#include "board.hpp"

Board::Board() : how_many_turns(0)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
}

Board::Board(const Board &board)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->board[i][j] = board.board[i][j];
}

char Board::getXO(int xo)
{
    if (xo == 1)
        return 'x';
    if (xo == -1)
        return 'o';
    return ' ';
}

bool Board::setSquare(int num_of_square, int xo, bool brute_force)
{
    if (((xo != 1 && xo != -1) && getSquare(num_of_square) != 0))
        if (!brute_force)
            return false;
    board[getRowByNumOfSquare(num_of_square)][getColumnByNumOfSquare(num_of_square)] = xo;
    return true;
}

int Board::getSquare(int num_of_square)
{
    return board[getRowByNumOfSquare(num_of_square)][getColumnByNumOfSquare(num_of_square)];
}

int Board::getSquare(int row, int column)
{
    return board[row][column];
}

bool Board::checkWinAtPosition(int num_of_square, int xo)
{
    int row = getRowByNumOfSquare(num_of_square);
    int column = getColumnByNumOfSquare(num_of_square);
    // horizontal
    if (xo == getSquare(row, (column + 1)%3) && xo == getSquare(row, (column + 2)%3))
        return true;
    // vertical
    if (xo == getSquare((row + 1)%3, column) && xo == getSquare((row + 2)%3, column))
        return true;
    
    //diagoal
    // I found out that all the squares that are on the diagonals are odd
    if (num_of_square % 2 == 1)
    {
        // 1,5,9
        if (num_of_square % 4 == 1)    
            if (xo == getSquare((row + 1)%3, (column + 1)%3) && xo == getSquare((row + 2)%3, (column + 2)%3))
                return true;
        
        // 3,5,7
        if (num_of_square == 3 || num_of_square == 5 ||num_of_square == 7)    
            if (xo == getSquare((row + 1)%3, (column + 2)%3) && xo == getSquare((row + 2)%3, (column + 4)%3))
                return true;
    }
    return false;
}

void Board::printBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << "  " << getXO(board[i][j]);
            if (j!=2)
                std::cout << "  |";
        }
        
        if (i!=2)
            std::cout << "\n" << "----------------";
        std::cout  << "\n"; 
    }
}

int Board::won()
{
    // horizontal
    for (int i = 1; i <= 7; i+=3)
        if (getSquare(i) != 0 && getSquare(i) == getSquare(i + 1) && getSquare(i) == getSquare(i + 2))
            return getSquare(i);
    // vertical
    for (int i = 1; i <= 3; i++)
        if (getSquare(i) != 0 && getSquare(i) == getSquare(i + 3) && getSquare(i) == getSquare((i + 6)))
            return getSquare(i);
    // diagonal
    if (getSquare(5) != 0 && getSquare(1) == getSquare(5) && getSquare(1) == getSquare(9))
        return getSquare(5);

    // diagonal
    if (getSquare(5) != 0 && getSquare(3) == getSquare(5) && getSquare(3) == getSquare(7))
        return getSquare(5);
    return 0;
}

// for the tie we can have two options
// 1. fill the entire 9 squares (the function is faster but will continue the game even if there is no possible win)
// 2. no possible win (the function will be slower but will pause the game if there is no posible win)
// this will be option 1
bool Board::tie()
{
    int counter = 0;

    for (int i = 1; i <= 9; i++)
        if (getSquare(i) != 0)
            counter++;

    return counter == 9;
}