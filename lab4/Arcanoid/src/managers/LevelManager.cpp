#include "managers/LevelManager.h"

#include "blocks/Block.h"
#include "blocks/HpBlock.h"
#include "blocks/UnbreakableBlock.h"
#include "Config.h"



LevelManager::LevelManager()
    : currentLevel(0)
{
    levels = std::vector<LevelData>
    {
        LevelData{
            {
                "1111111111",
                "1111111111",
                "1111111111",
                "1111111111"
            }
        },

        LevelData{
            {
                "2222222222",
                "1111111111",
                "2222222222",
                "1111111111"
            }
        },

        LevelData{
            {
                "3333333333",
                "1111111111",
                "2222222222",
                "2222222222",
                "2222222222"
            }
        }
    };

    loadLevel(0);
}

void LevelManager::loadLevel(size_t index)
{
    if (index >= levels.size())
        return;

    currentLevel = index;

    createBlocks(levels[index]);
}

void LevelManager::createBlocks(const LevelData& level)
{
    blocks.clear();


    const sf::Vector2f blockSize(Config::blockWidth, Config::blockHeight);

    for (size_t row = 0; row < level.layout.size(); ++row)
    {
        for (size_t col = 0; col < level.layout[row].size(); ++col)
        {
            char type = level.layout[row][col];

            float x = 60.f + col * (Config::blockWidth + Config::spacingX);
            float y = 50.f + row * (Config::blockHeight + Config::spacingY);

            switch (type)
            {
            case '1':
                blocks.push_back(
                    std::make_unique<Block>(
                        sf::Vector2f(x, y),
                        blockSize,
                        sf::Color::Blue
                    )
                );
                break;

            case '2':
                blocks.push_back(
                    std::make_unique<HpBlock>(
                        sf::Vector2f(x, y), 
                        blockSize
                    )
                );
                break;

            case '3':
                blocks.push_back(
                    std::make_unique<UnbreakableBlock>(
                        sf::Vector2f(x, y),
                        blockSize
                    )
                );
                break;

            default:
                break;
            }
        }
    }
}

bool LevelManager::isLevelCompleted() const
{
    for (const auto& block : blocks)
    {
        if (!block->isDestroyed())
        {
            return false;
        }
    }

    return true;
}

size_t LevelManager::getCurrentLevel() const
{
    return currentLevel;
}

std::vector<std::unique_ptr<Block>>& LevelManager::getBlocks()
{
    return blocks;
}

const std::vector<std::unique_ptr<Block>>& LevelManager::getBlocks() const
{
    return blocks;
}