#include "../../include/Game.hpp"
#include "../../include/Settings.hpp"
#include "../../include/Menu.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

using namespace Engine;

Game::Game() : context(std::make_shared<Context>())
{
    // Setup window and show first screen to display
    context->window->create(sf::VideoMode(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT), "Black Mamba", sf::Style::Close);
    context->states->addState(std::make_unique<Menu>(context));
}

/**
 * Start timer and run game loop
 */
void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (context->window->isOpen())
    {
        timeSinceLastFrame += clock.restart();
        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            context->states->processStateChange();
            context->states->GetCurrent()->processInput();
            context->states->GetCurrent()->update(TIME_PER_FRAME);
            context->states->GetCurrent()->draw();
        }
    }
}

int main()
{
    Game game;
    game.Run();

    return 0;
}