#include "game.hpp"
#include "solver.hpp"

Game::Game() : whose_turn(1), board(Board()) {}

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
bool Game::round(int xo)
{
    board.printBoard();
    
    int answer;
    if (xo == 1)
    {
        Solver solver = Solver(board, 1);
        answer = solver.solve();
    }
    else
    {
        answer = getSquareNumFromUser();
        //Solver solverO = Solver(board, -1);
        //answer = solverO.solve();
    }
        
    board.setSquare(answer, xo);
    
    if (board.checkWinAtPosition(answer, xo))
    {
        who_won = xo;
        xo = 0;
        printWinningMessage();
        return true;
    }
    //check tie
    if (board.tie())
        return true;
    return false;
}

void Game::printWinningMessage()
{
    system("cls");
    std::cout << "Game Ended.\n";
    
    if (who_won == 1)
        std::cout << "X won.\n";
        
    if (who_won == -1)
        std::cout << "O won.\n";
    board.printBoard();
}