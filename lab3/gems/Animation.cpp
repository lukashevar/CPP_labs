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


float Animation::getScale() const
{
	float t = m_elapsed / m_duration;

	switch (m_type)
	{
	case AnimationType::Destroy:
		return 1.f - t;

	case AnimationType::BombBonus:
		return 1.f + t * 2.f;

	case AnimationType::RecolorBonus:
		return 1.f + sin(t * 10.f) * 0.2f;

	default:
		return 1.f;
	}
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

float Animation::getAlpha() const {
	float t = m_elapsed / m_duration;

	switch (m_type) {
	case AnimationType::BombBonus:
		return 255.f * (1.f - t);

	case AnimationType::Destroy:
		return 255.f * (1.f - t);

	default:
		return 255.f;
	}
}
