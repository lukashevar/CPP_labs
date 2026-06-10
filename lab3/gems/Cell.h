#pragma once
#include <memory>
#include "Gem.h"

class Cell {
public:
	Cell();

	Gem* getGem() const;
	void setGem(std::unique_ptr<Gem> gem);
	std::unique_ptr<Gem> takeGem();

	bool isEmpty() const;
	bool isMarkedForDestroy() const;
	void markForDestroy();
	void dismarkForDestroy();

private:
	bool m_markedForDestroy = false;
	std::unique_ptr<Gem> m_gem;
};
