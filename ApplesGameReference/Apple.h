#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGames
{
    struct Game;
    struct Apple
    {
        std::vector<bool> isAppleEaten;
        std::vector<Vector2D> applesPositions;
        std::vector<sf::Sprite> applesSprite;

        Apple() 
        {
            resize(NUM_APPLES); // Инициализируем стандартным размером
        }

        void resize(size_t newSize) 
        {
            isAppleEaten.resize(newSize);
            applesPositions.resize(newSize);
            applesSprite.resize(newSize);
        }
    };
   

    void InitApples(Apple& apples, const Game& game);
}