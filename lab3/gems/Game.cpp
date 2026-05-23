#include "Game.h"

#include "BoardProcessor.h"
#include "BoardRenderer.h"
#include "Constants.h"
#include "MatchFinder.h"

Game::Game()
    : m_window(
        sf::VideoMode(
            Constants::WINDOW_WIDTH,
            Constants::WINDOW_HEIGHT
        ),
        "GEMS"
    ),
    m_board(Constants::ROWS, Constants::COLS)
{
    m_window.setFramerateLimit(60);

    
    BoardProcessor::process(m_board);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            handleMouseClick(
                event.mouseButton.x,
                event.mouseButton.y
            );
        }
    }
}

void Game::handleMouseClick(int mouseX, int mouseY)
{
    if (m_animationManager.isPlaying())
        return;

    int row = 0;
    int col = 0;

    if (!BoardRenderer::pixelToCell(m_board, mouseX, mouseY, row, col))
        return;

    if (!m_selectedCell.has_value())
    {
        m_selectedCell = { row, col };
        return;
    }

    int r1 = m_selectedCell->first;
    int c1 = m_selectedCell->second;

    
    if (r1 == row && c1 == col)
    {
        m_selectedCell.reset();
        return;
    }

    
    if (!m_board.areAdjacent(r1, c1, row, col))
    {
        m_selectedCell = { row, col };
        return;
    }

    GemColor color1 = m_board.getCell(r1, c1).color;
    GemColor color2 = m_board.getCell(row, col).color;

    
    m_board.swapCells(r1, c1, row, col);

    m_animationManager.add(
        Animation(
            color1,
            BoardRenderer::celltoPixel(r1, c1),
            BoardRenderer::celltoPixel(row, col),
            Constants::SWAP_ANIMATION_DURATION
        )
    );

    m_animationManager.add(
        Animation(
            color2,
            BoardRenderer::celltoPixel(row, col),
            BoardRenderer::celltoPixel(r1, c1),
            Constants::SWAP_ANIMATION_DURATION
        )
    );

    m_pendingMove = true;
    
    m_moveRow1 = r1;
    m_moveCol1 = c1;
    m_moveRow2 = row;
    m_moveCol2 = col;

    m_selectedCell.reset();
}

void Game::render()
{
    m_window.clear();
    BoardRenderer::draw(m_window, m_board);

    for (const Animation& animation : m_animationManager.getAnimations()) {
        BoardRenderer::drawGem(
            m_window,
            animation.getColor(),
            animation.getCurrentPosition()
        );
    }

    m_window.display();
}


void Game::update() {
    float dt = m_clock.restart().asSeconds();

    m_animationManager.update(dt);

    if (m_pendingMove && !m_animationManager.isPlaying()) {
        m_pendingMove = false;

        if (MatchFinder::findMatches(m_board)) {
            BoardProcessor::process(m_board);
        }
        else {
            m_board.swapCells(
                m_moveRow1,
                m_moveCol1,
                m_moveRow2,
                m_moveCol2
            );
        }
    }
}