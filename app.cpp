#include "game.hpp"

int main()
{
    Game game = Game();
    while (!game.round())
    {
        system("cls");
    }

    return 0;
}