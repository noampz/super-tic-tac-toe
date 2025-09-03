#include "game.hpp"

Game::Game() : whoseTurn(1), howManyTurns(0) , board(Board()) {}

bool Game::checkWinAtPosition(int num_of_square, int xo)
{
    int row = board.getRowByNumOfSquare(num_of_square);
    int column = board.getColumnByNumOfSquare(num_of_square);
    // horizontal
    if (xo == board.getSquare(row, (column + 1)%3) && xo == board.getSquare(row, (column + 2)%3))
        return true;
    // vertical
    if (xo == board.getSquare((row + 1)%3, column) && xo == board.getSquare((row + 2)%3, column))
        return true;
    
    //diagoal
    // I found out that all the squares that are on the diagonals are odd
    if (num_of_square % 2 == 1)
    {
        // 1,5,9
        if (num_of_square % 4 == 1)    
            if (xo == board.getSquare((row + 1)%3, (column + 1)%3) && xo == board.getSquare((row + 2)%3, (column + 2)%3))
                return true;
        
        // 3,5,7
        if (num_of_square == 3 || num_of_square == 5 ||num_of_square == 7)    
            if (xo == board.getSquare((row + 1)%3, (column + 2)%3) && xo == board.getSquare((row + 2)%3, (column + 4)%3))
                return true;
    }
    return false;
}

int Game::getSquareNumFromUser()
{
    int answer;
    std::cin >> answer;
    if (answer > 9 || answer < 1)
    {
        std::cout << "\nPlease input a num between 1 to 9: ";
        return getSquareNumFromUser();
    }
    if (board.getSquare(answer) != 0)
    {
        std::cout << "\nThis square is alredy taken pls write a diffrent square: ";
        return getSquareNumFromUser();
    }
    return answer;
}

//true if game ends
bool Game::round()
{
    board.printBoard();
    int answer = getSquareNumFromUser();
    board.setSquare(answer, whoseTurn);
    
    
    howManyTurns++;
    
    if (checkWinAtPosition(answer, whoseTurn))
    {
        whoWon = whoseTurn;
        whoseTurn = 0;
        printWinningMessage();
        return true;
    }
    //change the x to o or the o to x
    whoseTurn = -1 * whoseTurn;
    return false;
}

bool Game::won()
{
    // horizontal
    for (int i = 1; i <= 7; i+=3)
        if (board.getSquare(i) != 0 && board.getSquare(i) == board.getSquare(i + 1) && board.getSquare(i) == board.getSquare(i + 2))
            return true;
    // vertical
    for (int i = 1; i <= 3; i++)
        if (board.getSquare(i) != 0 && board.getSquare(i) == board.getSquare(i + 3) && board.getSquare(i) == board.getSquare((i + 6)))
            return true;
    // diagonal
    if (board.getSquare(5) != 0 && board.getSquare(1) == board.getSquare(5) && board.getSquare(1) == board.getSquare(9))
        return true;

    // diagonal
    if (board.getSquare(5) != 0 && board.getSquare(3) == board.getSquare(5) && board.getSquare(3) == board.getSquare(7))
        return true;
    return false;
}

// for the tie we can have two options
// 1. fill the entire 9 squares (the function is faster but will continue the game even if there is no possible win)
// 2. no possible win (the function will be slower but will pause the game if there is no posible win)
// this will be option 1
bool Game::tie()
{
    return howManyTurns >= 9;
}

void Game::printWinningMessage()
{
    system("cls");
    std::cout << "Game Ended.\n";
    
    if (whoWon == 1)
        std::cout << "X won.\n";
        
    if (whoWon == -1)
        std::cout << "O won.\n";
    board.printBoard();
}