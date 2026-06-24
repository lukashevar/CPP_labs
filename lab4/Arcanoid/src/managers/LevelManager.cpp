#include "managers/LevelManager.h"

#include "blocks/SimpleBlock.h"
#include "blocks/HpBlock.h"
#include "blocks/UnbreakableBlock.h"
#include "blocks/SpeedBoostBlock.h"
#include "Config.h"



LevelManager::LevelManager()
    : currentLevel(0)
{
    levels = std::vector<LevelData>
    {
        LevelData{
            {
                "3333333333",
                "1111111111",
                "1111441111",
                "1111111111"
            }
        },

        LevelData{
            {
                "2222222222",
                "1111111111",
                "2222222222",
                "1114444111"
            }
        },

        LevelData{
            {
                "3333333333",
                "1114444111",
                "2222222222",
                "2224444222",
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
            {
                auto block = std::make_unique<SimpleBlock>(
                    sf::Vector2f(x, y),
                    blockSize
                );

                if (rand() % 5 == 0) 
                    block->setBonus(true);

                blocks.push_back(std::move(block));
                break;
            }

            case '2':
            {
                auto block = std::make_unique<HpBlock>(
                    sf::Vector2f(x, y),
                    blockSize
                );

                if (rand() % 5 == 0)
                    block->setBonus(true);

                blocks.push_back(std::move(block));
                break;
            }

            case '3':
            {
                auto block = std::make_unique<UnbreakableBlock>(
                    sf::Vector2f(x, y),
                    blockSize
                );

                if (rand() % 5 == 0) 
                    block->setBonus(true);

                blocks.push_back(std::move(block));
                break;
            }

            case '4':
            {
                auto block = std::make_unique<SpeedBoostBlock>(
                    sf::Vector2f(x, y),
                    blockSize
                );

                if (rand() % 5 == 0)
                    block->setBonus(true);

                blocks.push_back(std::move(block));
                break;
            }

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
        if (block->isBreakable() && !block->isDestroyed())
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

size_t LevelManager::getLevelCount() const {
    return levels.size();
}
