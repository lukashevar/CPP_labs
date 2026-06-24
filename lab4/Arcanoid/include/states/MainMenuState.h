#pragma once
#include "states/State.h"
#include "managers/StateManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, sf::RenderWindow& window);
    void handleInput(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
private:
    void updateSelection();
    StateManager& stateManager;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Text> menuItems;
    int selectedItem = 0;
};
