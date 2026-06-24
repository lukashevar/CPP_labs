#pragma once
#include <SFML/Graphics.hpp>
#include "managers/StateManager.h"

class Game {
public:
    Game();
    void run();
private:
    void proccessEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    sf::Clock clock;
    StateManager stateManager;
};
