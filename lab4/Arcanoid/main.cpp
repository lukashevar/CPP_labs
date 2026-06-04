#include "core/Game.h"
#include <ctime>
#include <windows.h>

#pragma warning(disable: 4996)




int main()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    srand(static_cast<unsigned>(time(nullptr)));

    Game game;
    game.run();

    return 0;
}
