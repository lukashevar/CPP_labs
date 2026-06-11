#include "core/Game.h"
#include "states/MainMenuState.h"
#include "Config.h"

Game::Game()
    : window(
        sf::VideoMode(Config::windowWidth, Config::windowHeight),
        "Arkanoid")
{
    window.setFramerateLimit(60);
    stateManager.push(std::make_unique<MainMenuState>(stateManager, window));
}

void Game::run()
{
    while (window.isOpen() && !stateManager.isEmpty()) {
        float dt = clock.restart().asSeconds();
        proccessEvents();
        update(dt);
        render();
    }
}

void Game::proccessEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (stateManager.current())
            stateManager.current()->handleInput(event);
    }
}

void Game::update(float dt)
{
    if (stateManager.current())
        stateManager.current()->update(dt);
}

void Game::render()
{
    window.clear(sf::Color::Black);
    if (stateManager.current())
        stateManager.current()->render(window);
    window.display();
}
