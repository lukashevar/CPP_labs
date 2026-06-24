#include "entities/Paddle.h"
#include "Config.h"

Paddle::Paddle() {
	shape.setSize(sf::Vector2f(120.f, 20.f));
	shape.setFillColor(sf::Color::White);

	speed = 500.f;
	velocity = { 0.f, 0.f };

	shape.setPosition(300.f, 550.f);
}


void Paddle::update(float dt)
{
	handleInput(dt);

	shape.move(velocity * dt);

	if (shape.getPosition().x < 0.f)
	{
		shape.setPosition(0.f, shape.getPosition().y);
	}

	if (shape.getPosition().x + shape.getSize().x > 800.f)
	{
		shape.setPosition(
			800.f - shape.getSize().x,
			shape.getPosition().y
		);
	}

	if (widthBonusActive)
	{
		widthBonusTimer -= dt;

		if (widthBonusTimer <= 0.f)
		{
			widthBonusActive = false;
			setWidth(baseWidth);
		}
	}
}

void Paddle::handleInput(float dt) {
	velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = speed;
	}
}


void Paddle::render(sf::RenderWindow& window) {
	window.draw(shape);
}


void Paddle::setPosition(float x, float y) {
	shape.setPosition(x, y);
}


sf::Vector2f Paddle::getPosition() const {
	return shape.getPosition();
}


sf::FloatRect Paddle::getBounds() const {
	return shape.getGlobalBounds();
}

void Paddle::reset() {
	shape.setPosition(Config::PaddleStartX, Config::PaddleStartY);
}

float Paddle::getWidth() const
{
	return shape.getSize().x;
}

void Paddle::setWidth(float width)
{
	float centerX =
		shape.getPosition().x +
		shape.getSize().x / 2.f;

	shape.setSize({
		width,
		shape.getSize().y
		});

	shape.setPosition(
		centerX - width / 2.f,
		shape.getPosition().y
	);
}

void Paddle::activateWidthBonus(float duration)
{
	setWidth(baseWidth * 1.5f);

	widthBonusActive = true;
	widthBonusTimer = duration;
}
