#include "ScoreManager.h"

void ScoreManager::addPoints(int points) {
	m_score += points;

	if (m_score > m_highScore) {
		m_highScore = m_score;
	}
}

int ScoreManager::getScore() const {
	return m_score;
}

int ScoreManager::getHighScore() const {
	return m_highScore;
}

void ScoreManager::reset() {
	m_score = 0;
}