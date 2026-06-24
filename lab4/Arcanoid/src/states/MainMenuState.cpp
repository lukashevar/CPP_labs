#include "states/MainMenuState.h"
#include "states/LevelSelectState.h"
#include "states/PlayingState.h"
#include <stdexcept>

MainMenuState::MainMenuState(StateManager& stateManager, sf::RenderWindow& window)
    : stateManager(stateManager), window(window)
{
    if (!font.loadFromFile("assets/arialmt.ttf"))
        throw std::runtime_error("Failed to load font");

    titleText.setFont(font);
    titleText.setString("ARKANOID");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(250.f, 100.f);

    std::vector<std::string> items = { "Start Game", "Select Level" };
    for (size_t i = 0; i < items.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(36);
        text.setPosition(300.f, 250.f + i * 60.f);
        menuItems.push_back(text);
    }

    updateSelection();
}

void MainMenuState::handleInput(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
        return;

    if (event.key.code == sf::Keyboard::Up) {
        selectedItem = (selectedItem - 1 + menuItems.size()) % menuItems.size();
        updateSelection();
    }
    if (event.key.code == sf::Keyboard::Down) {
        selectedItem = (selectedItem + 1) % menuItems.size();
        updateSelection();
    }
    if (event.key.code == sf::Keyboard::Return) {
        if (selectedItem == 0)
            stateManager.change(std::make_unique<PlayingState>(stateManager, window, 0));
        else if (selectedItem == 1)
            stateManager.push(std::make_unique<LevelSelectState>(stateManager, window));
    }
}

void MainMenuState::update(float dt) {}

void MainMenuState::render(sf::RenderWindow& window)
{
    window.draw(titleText);
    for (auto& item : menuItems)
        window.draw(item);
}

void MainMenuState::updateSelection()
{
    for (size_t i = 0; i < menuItems.size(); i++) {
        if (i == selectedItem) {
            menuItems[i].setFillColor(sf::Color::Yellow);
            menuItems[i].setString("> " + std::string(i == 0 ? "Start Game" : "Select Level"));
        }
        else {
            menuItems[i].setFillColor(sf::Color::White);
            menuItems[i].setString(i == 0 ? "Start Game" : "Select Level");
        }
    }
}
