#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
namespace ApplesGames
{
    struct Game;
    struct Rock
    {
        Vector2D rocksPositions[NUM_ROCKS];
        sf::Sprite rocksSprite[NUM_ROCKS];
    };

    void InitRocks(Rock& rocks, const Game& game);
}

