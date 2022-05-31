#include "gameWindow.hpp"

int main()
{
    GameWindow window(800, 600, false);

    window.loop();

    return 0;
}