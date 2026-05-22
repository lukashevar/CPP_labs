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

    
    m_board.swapCells(r1, c1, row, col);

    
    if (MatchFinder::findMatches(m_board))
    {
        
        BoardProcessor::process(m_board);
    }
    else
    {
        
        m_board.swapCells(r1, c1, row, col);
    }

    m_selectedCell.reset();
}

void Game::render()
{
    m_window.clear();
    BoardRenderer::draw(m_window, m_board);
    m_window.display();
}