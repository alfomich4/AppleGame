#include <SFML/Graphics.hpp>
#include <ctime>
#include "Constants.h"
#include "Game.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Record.h"

using namespace ApplesGames;

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game!");
    srand(static_cast<unsigned int>(time(NULL)));

    sf::Font font;
    if (!font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"))
        return EXIT_FAILURE;

    Game game;
    Player player;
    Apple apples;
    Rock rocks;

    InitGame(player, apples, rocks, game, font);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(16));
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                InitGame(player, apples, rocks, game, font);
            }

            HandleModeSelection(game, event);
        }
        
        
            HandleInput(game, player);
            RotateAccordingToDirection(player);
       

        UpdateGame(game, player, apples, rocks, deltaTime);
        RenderGame(window, game, player, apples, rocks);
    }

    return 0;
}