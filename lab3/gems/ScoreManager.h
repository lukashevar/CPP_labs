#pragma once

class ScoreManager {
public:
	void addPoints(int points);

	int getScore() const;
	int getHighScore() const;

	void reset();

private:
	int m_score = 0;
	int m_highScore = 0;
};
