#include "Animation.h"

Animation::Animation(
	AnimationType type,
	GemColor color,
	const sf::Vector2f& from,
	const sf::Vector2f& to,
	float duration
)
	: m_type(type)
	, m_color(color)
	, m_from(from)
	, m_to(to)
	, m_duration(duration)
	, m_elapsed(0.f)
{}


void Animation::update(float dt) {
	m_elapsed += dt;

	if (m_elapsed > m_duration) {
		m_elapsed = m_duration;
	}
}


bool Animation::isFinished() const {
	return m_elapsed >= m_duration;
}


sf::Vector2f Animation::getCurrentPosition() const {
	float t = m_elapsed / m_duration;

	return m_from + (m_to - m_from) * t;
}


GemColor Animation::getColor() const {
	return m_color;
}


AnimationType Animation::getType() const {
	return m_type;
}


float Animation::getScale() const {
	if (m_type != AnimationType::Destroy)
		return 1.f;

	float t = m_elapsed / m_duration;
	
	return 1.f - t;
}

int Animation::getRow() const {
	return m_row;
}


int Animation::getCol() const {
	return m_col;
}

void Animation::setRow(int row) {
	m_row = row;
}

void Animation::setCol(int col) {
	m_col = col;
}