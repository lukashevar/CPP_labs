#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Animation.h"

class AnimationManager {
public:
	void add(const Animation& animation);

	void update(float dt);

	void clear();

	bool isPlaying() const;

	const std::vector<Animation>& getAnimations() const;

private:
	std::vector<Animation> m_animations;
};
