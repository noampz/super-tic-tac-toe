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
        return score;
    return 0;
}

MinimaxResult Solver::minimax(bool is_maximizing, bool first, int depth)
{
    int score = evaluate();
    if (score != 0)
        return {(float)score, 0};
    if (board.tie())
        return {0, 0};

    int xo = is_maximizing ? 1 : -1;
    int move = winNextMove(xo);
    if (move != 0)
        return {1, move};

    MinimaxResult best = {0,0};
    bool *moves = new bool[9];

    int counter = 0;

    move = blockWinningMove(xo);
    if (move != 0)
    {
        for (int i = 0; i < 9; i++)
        {
            moves[i] = false;
        }
        moves[move-1] = true;
    }
    else
    {
        moves = avaliableMoves();
    }

    if (is_maximizing)
    {
        best.eval = INT_MIN;

        for (int i = 0; i < 9; i++)
        {
            if (!moves[i])
                continue;
            board.setSquare(i+1, 1, true);
            if (first)
            {
                MinimaxResult result = minimax(!is_maximizing, false, depth + 1);
                if (result.eval > best.eval)
                {
                    best.eval = result.eval;
                    best.best_move = i+1;
                }
            }
            else
            {
                counter++;
                best.eval -= minimax(!is_maximizing, false, depth + 1).eval;
            }
            board.setSquare(i+1, 0, true);
        }
    }
    else
    {
        best.eval = INT_MAX;

        for (int i = 0; i < 9; i++)
        {
            if (!moves[i])
                continue;
            board.setSquare(i+1, -1, true);
            if (first)
            {
                MinimaxResult result = minimax(!is_maximizing, false, depth + 1);
                if (result.eval < best.eval)
                {
                    best.eval = result.eval;
                    best.best_move = i+1;
                }
            }
            else
            {
                counter++;
                best.eval += minimax(!is_maximizing, false, depth + 1).eval;
            }
            board.setSquare(i+1, 0, true);
        }
    }
    counter == 0 ? counter = 1 : counter;
    best.eval /= counter;
    delete moves;
    return best;
}

int Solver::solve()
{
    return minimax(who_are_we_helping == 1, true, 0).best_move;
}