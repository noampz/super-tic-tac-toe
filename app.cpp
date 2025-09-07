#include "./src/game.hpp"

int main()
{
    Game game = Game();
    int xo = 1;
    while (!game.round(xo))
    {
        xo *= -1;
        system("cls");
    }

    return 0;
}