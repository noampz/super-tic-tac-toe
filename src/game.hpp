#include "board.hpp"

class Game
{
    private:
    Board board;
    // 1 = x , -1 = o
    int whoseTurn;
    // 0 = tie, 1 = x won, -1 = o won
    int whoWon;

    int howManyTurns;

    int getSquareNumFromUser();
    bool checkWinAtPosition(int num_of_square, int xo);
    public:
    Game();
    int getWhoWon() const {return whoWon;}

    //false if game ends
    bool round();
    bool won();
    bool tie();

    void printWinningMessage();
};