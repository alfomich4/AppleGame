#include "Player.h"
#include "Constants.h"
#include "Game.h"
#include <SFML/Graphics.hpp>


namespace ApplesGames
{


    void InitPlayer(Player& player, const Game& game)
    {
        player.playerPosition = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.playerSpeed = INITIAL_SPEED;
        player.playerDirection = PlayerDirection::Right;

        player.playerSprite.setTexture(game.playerTexture);
        player.playerSprite.setOrigin(PLAYER_TEXTURE_SIZE / 2.f, PLAYER_TEXTURE_SIZE / 2.f);
        player.playerSprite.setPosition(player.playerPosition.x, player.playerPosition.y);
        setSpriteSize(player.playerSprite, PLAYER_TEXTURE_SIZE, PLAYER_SIZE);
        player.baseScale = player.playerSprite.getScale();
    }

    void RotateAccordingToDirection(Player& player)
    {
        switch (player.playerDirection)
        {
        case PlayerDirection::Right:
            player.playerSprite.setRotation(0.f);
            player.playerSprite.setScale(player.baseScale.x, player.baseScale.y);
            break;
        case PlayerDirection::Up:
            player.playerSprite.setRotation(270.f);
            player.playerSprite.setScale(player.baseScale.x, player.baseScale.y);
            break;
        case PlayerDirection::Down:
            player.playerSprite.setRotation(90.f);
            player.playerSprite.setScale(player.baseScale.x, player.baseScale.y);
            break;
        case PlayerDirection::Left:
            player.playerSprite.setRotation(0.f);
            player.playerSprite.setScale(-player.baseScale.x, player.baseScale.y);     // Зеркалим по горизонтали
            break;
        }
    }

    void HandleInput(Game& game, Player& player)
    {
        if (!game.isGameFinished)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player.playerDirection = PlayerDirection::Right;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player.playerDirection = PlayerDirection::Up;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player.playerDirection = PlayerDirection::Left;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player.playerDirection = PlayerDirection::Down;
        }
    }
}