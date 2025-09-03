#include "board.hpp"

Board::Board()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
}

char Board::getXO(int xo)
{
    if (xo == 1)
        return 'x';
    if (xo == -1)
        return 'o';
    return ' ';
}

bool Board::setSquare(int num_of_square , int xo)
{
    if ((xo != 1 && xo != -1) || getSquare(num_of_square) != 0)
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