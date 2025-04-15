#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>
namespace ApplesGames
{
    Vector2D GetRandomPositionInScreen()
    {
        Vector2D result;
        result.x = rand() / (float)RAND_MAX * SCREEN_WIDTH;
        result.y = rand() / (float)RAND_MAX * SCREEN_HEIGHT;
        return result;
    }

    bool IsCirclesCollide(Vector2D pos1, float radius1, Vector2D pos2, float radius2)
    {
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = radius1 + radius2;
        return distanceSquared <= (radiusSum * radiusSum);
    }

    void setSpriteSize(sf::Sprite& sprite, float textureSize, float desiredSize)
    {
        float scale = desiredSize / textureSize;
        sprite.setScale(scale, scale);
    }


}