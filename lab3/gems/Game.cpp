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

    
    BoardProcessor::process(m_board, m_animationManager);

    m_font.loadFromFile("assets/arialmt.ttf");

    m_scoreText.setFont(m_font);

    m_scoreText.setCharacterSize(32);

    m_scoreText.setFillColor(sf::Color::White);

    m_scoreText.setPosition(10.f, 10.f);
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
            AnimationType::Swap,
            color1,
            BoardRenderer::celltoPixel(r1, c1),
            BoardRenderer::celltoPixel(row, col),
            Constants::SWAP_ANIMATION_DURATION
        )
    );

    m_animationManager.add(
        Animation(
            AnimationType::Swap,
            color2,
            BoardRenderer::celltoPixel(row, col),
            BoardRenderer::celltoPixel(r1, c1),
            Constants::SWAP_ANIMATION_DURATION
        )
    );

    m_state = GameState::Swapping;

    
    m_moveRow1 = r1;
    m_moveCol1 = c1;
    m_moveRow2 = row;
    m_moveCol2 = col;

    m_selectedCell.reset();
}

void Game::render()
{
    m_window.clear();

    
    BoardRenderer::draw(m_window, m_board, m_animationManager);

    
    for (const Animation& animation : m_animationManager.getAnimations())
    {
        BoardRenderer::drawGem(
            m_window,
            animation.getColor(),
            animation.getCurrentPosition(),
            animation.getScale(),
            animation.getAlpha()
        );
    }

    
    m_scoreText.setString(
        "Score: " + std::to_string(m_scoreManager.getScore())
    );

    m_window.draw(m_scoreText);

    m_window.display();
}


void Game::update()
{
    float dt = m_clock.restart().asSeconds();

    m_animationManager.update(dt);

    
    if (m_animationManager.isPlaying())
        return;

    switch (m_state)
    {
    case GameState::Swapping:
    {
        if (MatchFinder::findMatches(m_board))
        {
            startDestroyAnimations();

            m_state = GameState::Destroying;
        }
        else
        {
            
            m_board.swapCells(
                m_moveRow1,
                m_moveCol1,
                m_moveRow2,
                m_moveCol2
            );

            m_state = GameState::Idle;
        }

        break;
    }

    case GameState::Destroying:
    {
        int gained =
            BoardProcessor::destroyMarkedCells(
                m_board,
                m_animationManager
            );

        m_scoreManager.addPoints(gained);

        startFallAnimations();

        m_state = GameState::Falling;

        break;
    }

    case GameState::Falling:
    {
        BoardProcessor::collapseColumns(m_board);

        BoardProcessor::fillEmptyCells(m_board);

        if (MatchFinder::findMatches(m_board))
        {
            startDestroyAnimations();

            m_state = GameState::Destroying;
        }
        else
        {
            m_state = GameState::Idle;
        }

        break;
    }

    case GameState::Idle:
    default:
        break;
    }
}

void Game::startDestroyAnimations()
{
    for (int row = 0; row < m_board.getRows(); ++row)
    {
        for (int col = 0; col < m_board.getCols(); ++col)
        {
            Cell& cell = m_board.getCell(row, col);

            if (cell.markedForDestroy)
            {
                m_animationManager.add(
                    Animation(
                        AnimationType::Destroy,
                        cell.color,
                        BoardRenderer::celltoPixel(row, col),
                        BoardRenderer::celltoPixel(row, col),
                        Constants::DESTROY_ANIMATION_DURATION
                    )
                );
            }
        }
    }
}


void Game::startFallAnimations()
{
    auto moves = BoardProcessor::collectFallMoves(m_board);

    for (const FallMove& move : moves)
    {
        Animation anim(
            AnimationType::Fall,
            move.color,
            BoardRenderer::celltoPixel(
                move.fromRow,
                move.fromCol
            ),
            BoardRenderer::celltoPixel(
                move.toRow,
                move.toCol
            ),
            Constants::FALL_ANIMATION_DURATION
        );

        anim.setRow(move.fromRow);
        anim.setCol(move.fromCol);

        m_animationManager.add(anim);
    }
}


void Game::startBombAnimation(int row, int col)
{
    Animation anim(
        AnimationType::BombBonus,
        GemColor::Yellow,
        BoardRenderer::celltoPixel(row, col),
        BoardRenderer::celltoPixel(row, col),
        0.5f
    );

    anim.setRow(row);
    anim.setCol(col);

    m_animationManager.add(anim);
}


void Game::startRecolorAnimation(
    int row,
    int col,
    GemColor color
)
{
    Animation anim(
        AnimationType::RecolorBonus,
        color,
        BoardRenderer::celltoPixel(row, col),
        BoardRenderer::celltoPixel(row, col),
        0.6f
    );

    anim.setRow(row);
    anim.setCol(col);

    m_animationManager.add(anim);
}
