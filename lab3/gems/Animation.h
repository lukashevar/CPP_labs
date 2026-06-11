#pragma once
#include <SFML/Graphics.hpp>
#include "GemColor.h"

enum class AnimationType {
    Swap,
    Destroy,
    Fall,
    RecolorBonus,
    BombBonus
};

class Animation {
public:
    Animation(
        AnimationType type,
        GemColor color,
        const sf::Vector2f& from,
        const sf::Vector2f& to,
        float duration
    );
    void update(float dt);
    bool isFinished() const;
    sf::Vector2f getCurrentPosition() const;
    GemColor getColor() const;
    float getScale() const;
    AnimationType getType() const;
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
    float getAlpha() const;
private:
    AnimationType m_type;
    GemColor m_color;
    sf::Vector2f m_from;
    sf::Vector2f m_to;
    float m_duration;
    float m_elapsed;
    int m_row = 0;
    int m_col = 0;
};
