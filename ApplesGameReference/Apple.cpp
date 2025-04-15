#include "Apple.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGames
{

    void InitApples(Apple& apples, const Game& game)
    {
        int appleCount;
        if (game.gameMode & MODE_50_APPLES)
        {
            appleCount = NUM_APPLES_EXTENDED;
        }
        else
        {
            appleCount = NUM_APPLES;
        }
        apples.resize(appleCount);
        for (int i = 0; i < appleCount; ++i)
        {
            apples.applesPositions[i] = GetRandomPositionInScreen();
            apples.isAppleEaten[i] = false;

            apples.applesSprite[i].setTexture(game.appleTexture);
            apples.applesSprite[i].setOrigin(APPLE_TEXTURE_SIZE / 2.f, APPLE_TEXTURE_SIZE / 2.f);
            apples.applesSprite[i].setPosition(apples.applesPositions[i].x, apples.applesPositions[i].y);
            setSpriteSize(apples.applesSprite[i], APPLE_TEXTURE_SIZE, APPLE_SIZE);
        }
    }
}
