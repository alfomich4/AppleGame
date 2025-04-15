#include "Rock.h"
#include "Constants.h"
#include"Game.h"

namespace ApplesGames
{

    void InitRocks(Rock& rocks, const Game& game)
    {
        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            rocks.rocksPositions[i] = GetRandomPositionInScreen();

            rocks.rocksSprite[i].setTexture(game.rockTexture);
            rocks.rocksSprite[i].setOrigin(ROCK_TEXTURE_SIZE / 2.f, ROCK_TEXTURE_SIZE / 2.f);
            rocks.rocksSprite[i].setPosition(rocks.rocksPositions[i].x, rocks.rocksPositions[i].y);
            setSpriteSize(rocks.rocksSprite[i], ROCK_TEXTURE_SIZE, ROCK_SIZE);
        }
    }
}