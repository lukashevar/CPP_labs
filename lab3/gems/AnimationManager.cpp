#include "AnimationManager.h"

#include <algorithm>

void AnimationManager::add(const Animation& animation) {
	m_animations.push_back(animation);
}


void AnimationManager::update(float dt) {
	for (Animation& animation : m_animations) {
		animation.update(dt);
	}

	m_animations.erase(
		std::remove_if(m_animations.begin(), m_animations.end(),
			[](const Animation& animation) {
				return animation.isFinished();
			}
		),
		m_animations.end()
	);
}


void AnimationManager::clear() {
	m_animations.clear();
}


bool AnimationManager::isPlaying() const {
	return !m_animations.empty();
}


const std::vector<Animation>& AnimationManager::getAnimations() const {
	return m_animations;
}
