#ifndef BLACKMAMBA_GAME_HPP
#define BLACKMAMBA_GAME_HPP
#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
//#include <windows.h>

#include "StateManager.hpp"
#include "AssetManager.hpp"


namespace Engine
{
    enum AssetID
    {
        MAIN_FONT,
        BOLD_FONT,
        BACKGROUND,
        FOOD,
        POISON,
        HEART,
        UP_MOUTH,
        DOWN_MOUTH,
        LEFT_MOUTH,
        RIGHT_MOUTH
    };

    struct Context
    {
        std::unique_ptr<Engine::AssetManager> assets;
        std::unique_ptr<Engine::StateManager> states;
        std::unique_ptr<sf::RenderWindow> window;

        Context()
        {
            assets = std::make_unique<Engine::AssetManager>();
            states = std::make_unique<Engine::StateManager>();
            window = std::make_unique<sf::RenderWindow>();
        }
    };

    struct MultipleGameInitException : public std::exception {
        const char * what () const throw () {
            return "MultipleGameInit Exception";
        }
    };

    class Game
    {
        // we will implement Game class as singleton class.
        static Game *instance;
    private:
        std::shared_ptr<Context> context;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);
        Game(); // constructor is private as per singleton class implementation.
    public:
        static Game* getInstance() {
            try {
                if (!instance) {
                    instance = new Game;
                    return instance;
                } else {
                    // throw an exception since somewhere is trying to call an instance...
                    // ...when an instance already exists.
                    throw MultipleGameInitException();
                }
            } catch(MultipleGameInitException& e) {
                std::cerr << "MultipleGameInit exception caught!" << std::endl;
                std::cerr << e.what() << std::endl;
//                MessageBox(NULL, "Calling Multiple Game Instances! Ending game!",
//                           "Exception has occurred!", MB_ICONERROR); // windows only.
                std::terminate(); // aborts program.
            }
        }
        void Run();
    };
}


#endif //BLACKMAMBA_GAME_HPP
