#include "Animation.h"

Animation::Animation(
	GemColor color,
	const sf::Vector2f& from,
	const sf::Vector2f& to,
	float duration
)
	: m_color(color)
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