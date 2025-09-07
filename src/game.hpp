#pragma once
#include "board.hpp"

class Game
{
    private:
    Board board;
    // 1 = x , -1 = o
    int whose_turn;
    // 0 = tie, 1 = x won, -1 = o won
    int who_won;

    int last_turn;
    int getSquareNumFromUser();

    friend class solver;
    public:
    Game();
    int getWhoWon() const {return who_won;}


    //false if game ends
    bool round(int xo);

    void printWinningMessage();
};