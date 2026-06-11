#include "Cell.h"
#include "GemFactory.h"

Gem* Cell::getGem() const {
	return m_gem.get();
}

void Cell::setGem(std::unique_ptr<Gem> gem) {
	m_gem = std::move(gem);
}

bool Cell::isEmpty() const {
	return m_gem == nullptr;
}

bool Cell::isMarkedForDestroy() const {
	return m_markedForDestroy;
}

void Cell::markForDestroy() {
	m_markedForDestroy = true;
}

void Cell::dismarkForDestroy() {
	m_markedForDestroy = false;
}

std::unique_ptr<Gem> Cell::takeGem() {
	return std::move(m_gem);
}
