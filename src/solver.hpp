#pragma once
#include "./data_structure/treeNode.hpp"
#include "board.hpp"
#include "game.hpp"

// {eval, best_move}
struct MinimaxResult
{
    int eval;
    int best_move;
};

class Solver
{
    private:

    Board &board;

    
    int who_are_we_helping;

    // returns an array with a length of 9 that is true when the move is avalibale and false when it is not
    bool* avaliableMoves();

    // return 0 if there are no positions to win
    int winNextMove(int xo);

    //  I dont think this is needed but might as well have it for simplicity
    int blockWinningMove(int xo);

    //returns the move the person needs to
    int mandatoryMoves(int xo);

    int evaluate();
    //decided not to continue with the fork as it will not be efficient
    //int fork(Board &board, int xo);

    MinimaxResult minimax(bool is_maximizing, bool first = true, int depth = 0);

    public:
    
    Solver(Board &board, int xo);

    int solve();
};