#pragma once

#include "blocks/Block.h"

#include <memory>
#include <string>
#include <vector>

struct LevelData
{
    std::vector<std::string> layout;
};

class LevelManager
{
public:
    LevelManager();

    void loadLevel(size_t index);

    bool isLevelCompleted() const;

    size_t getCurrentLevel() const;

    std::vector<std::unique_ptr<Block>>& getBlocks();
    const std::vector<std::unique_ptr<Block>>& getBlocks() const;

    size_t getLevelCount() const;

private:
    void createBlocks(const LevelData& level);

    size_t currentLevel = 0;

    std::vector<LevelData> levels;

    std::vector<std::unique_ptr<Block>> blocks;
};