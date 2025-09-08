#include "solver.hpp"
Solver::Solver(Board &board, int xo) : board(board) , who_are_we_helping(xo) {}


bool* Solver::avaliableMoves()
{
    bool* moves = new bool[9];
    for (int i = 0; i < 9; i++)
    {
        moves[i] = (board.getSquare(i+1) == 0);
    }

    return moves;
}

int Solver::winNextMove(int xo)
{
    int position = 0;
    bool* moves = avaliableMoves();
    for (int i = 0; i < 9; i++)
    {
        if (moves[i] && board.checkWinAtPosition(i+1, xo))
        {
            position = i + 1;
            break;
        }
    }
    delete[] moves;
    return position;
}


int Solver::blockWinningMove(int xo)
{
    // it will return the positon of the place the over player will need to place in order to win
    return winNextMove(-xo);
}

int Solver::mandatoryMoves(int xo)
{
    int move = winNextMove(xo);
    if (move != 0)
        return move;
    move = blockWinningMove(xo);
    if (move != 0)
        return move;
    return 0;
}

int Solver::evaluate()
{
    int score = board.won();
    if(score != 0)
        return score * 20;
    return 0;
}

MinimaxResult Solver::minimax(bool is_maximizing, int depth)
{
    int eval = evaluate();
    if (eval == 20)
        return {(float)eval - 2 * depth, 0};
    else if (eval == -20)
        return {(float)eval + 2 * depth, 0};

    if (board.tie())
    {
        return {0, 0};
    }
        
    
    // mabye do some of the mandatory moves
    int xo;
    is_maximizing ? xo = 1 : xo = -1;

    bool *moves = avaliableMoves();
    MinimaxResult best = {0,0};

    if (is_maximizing)
        best.eval = INT_MIN;
    else
        best.eval = INT_MAX;

    for (int i = 0; i < 9; i++)
    {
        if (!moves[i])
            continue;

        board.setSquare(i+1, xo);
        MinimaxResult result = minimax(!is_maximizing, depth + 1);
        if (is_maximizing)
        {
            if (result.eval > best.eval)
            {
                best.eval = result.eval;
                best.best_move = i+1;
            }
                
        }
        else
        {
            if (result.eval < best.eval)
            {
                best.eval = result.eval;
                best.best_move = i+1;
            }
        }

        board.setSquare(i+1, 0, true);
    }

    delete[] moves;
    return best;
}

int Solver::solve()
{
    MinimaxResult result = minimax(who_are_we_helping == 1);
    return result.best_move;
}