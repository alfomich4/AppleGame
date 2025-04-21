#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"
namespace ApplesGames
{
    struct Game;
    enum class PlayerDirection
    {
        Right = 0,
        Up,
        Left,
        Down
    };

    struct Player
    {
        Vector2D playerPosition;
        float playerSpeed = INITIAL_SPEED;
        PlayerDirection playerDirection = PlayerDirection::Right;
        sf::Sprite playerSprite;
        sf::Vector2f baseScale;
    };
    
    
    
    void InitPlayer(Player& player, const Game& game);
    void HandleInput(Game& game, Player& player);
    void RotateAccordingToDirection(Player& player);


}