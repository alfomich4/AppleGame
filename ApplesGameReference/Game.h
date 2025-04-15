#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"

namespace ApplesGames
{
    struct Player;
    struct Apple;
    struct Rock;

    struct Game
    {
        int numEatenApples = 0;
        bool isGameFinished = false;
        bool isGameStarted = false; // Флаг начала игры
        bool needReinitApples = true;
        float gameFinishTime = 0.f;
        unsigned int gameMode = MODE_DEFAULT;

        sf::RectangleShape background;
        sf::Text scoreText;
        sf::Text inputHintText;
        sf::Text gameOverText;
        sf::Text modeSelectText;

        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::SoundBuffer eatBuffer;
        sf::SoundBuffer deathBuffer;
        sf::Sound eatSound;
        sf::Sound deathSound;
    };

    void InitGame(Player& player, Apple& apples, Rock& rocks, Game& game, const sf::Font& font);
    void UpdateGame(Game& game, Player& player, Apple& apples, Rock& rocks, float deltaTime);
    void RenderGame(sf::RenderWindow& window, Game& game, Player& player, Apple& apples, Rock& rocks);
    void HandleModeSelection(Game& game, sf::Event event);
    void ShowModeSelectionScreen(sf::RenderWindow& window, Game& game);
}