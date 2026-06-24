#include "states/LevelSelectState.h"
#include "states/PlayingState.h"

LevelSelectState::LevelSelectState(StateManager& stateManager, sf::RenderWindow& window)
	: stateManager(stateManager), window(window)
{
	if (!font.loadFromFile("assets/arialmt.ttf"))
		throw std::runtime_error("Failed to load font");

	titleText.setFont(font);
	titleText.setString("SELECT LEVEL");
	titleText.setCharacterSize(64);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(200.f, 100.f);

	std::vector<std::string> items = { "Level 1", "Level 2", "Level 3" };
	for (size_t i = 0; i < items.size(); ++i) {
		sf::Text text;
		text.setFont(font);
		text.setString(items[i]);
		text.setCharacterSize(36);
		text.setPosition(300.f, 250.f + i * 60.f);
		menuItems.push_back(text);
	}

	updateSelection();
}

void LevelSelectState::handleInput(const sf::Event& event) {
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
		stateManager.change(std::make_unique<PlayingState>(stateManager, window, selectedItem));
	}
	if (event.key.code == sf::Keyboard::Escape) {
		stateManager.pop();
	}
}

void LevelSelectState::update(float dt) {}

void LevelSelectState::render(sf::RenderWindow& window)
{
	window.draw(titleText);
	for (auto& item : menuItems)
		window.draw(item);
}

void LevelSelectState::updateSelection()
{
	std::vector<std::string> names = { "Level 1", "Level 2", "Level 3" };
	for (size_t i = 0; i < menuItems.size(); i++) {
		if (i == selectedItem) {
			menuItems[i].setFillColor(sf::Color::Yellow);
			menuItems[i].setString("> " + names[i]);
		}
		else {
			menuItems[i].setFillColor(sf::Color::White);
			menuItems[i].setString(names[i]);
		}
	}
}
