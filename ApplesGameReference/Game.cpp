#include "Game.h"
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Math.h"
#include "Record.h"
#include <cassert>
#include <sstream>

namespace ApplesGames
{
    void InitGame(Player& player, Apple& apples, Rock& rocks, Game& game,const sf::Font& font)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "Rock.png"));

        assert(game.eatBuffer.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
        assert(game.deathBuffer.loadFromFile(RESOURCES_PATH + "Death.wav"));

        game.eatSound.setBuffer(game.eatBuffer);
        game.deathSound.setBuffer(game.deathBuffer);

        InitPlayer(player, game);
        InitApples(apples, game);
        InitRocks(rocks, game);

        game.needReinitApples = true;
        game.numEatenApples = 0;
        game.isGameFinished = false;
        game.isGameStarted = false; // Игра не начата, ждем выбора режима
        game.gameFinishTime = 0.f;

        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setFillColor(sf::Color::Black);

        game.scoreText.setFont(font);
        game.scoreText.setCharacterSize(20);
        game.scoreText.setFillColor(sf::Color::White);
        game.scoreText.setPosition(10, 10);

        game.inputHintText.setFont(font);
        game.inputHintText.setCharacterSize(20);
        game.inputHintText.setFillColor(sf::Color::Yellow);
        game.inputHintText.setPosition(200, 10);
        game.inputHintText.setString("Use arrow keys to move,press space to restart, ESC to exit");

        game.gameOverText.setFont(font);
        game.gameOverText.setCharacterSize(70);
        game.gameOverText.setFillColor(sf::Color::Cyan);
        game.gameOverText.setPosition(200, 200);

        game.leadertable.setFont(font);
        game.leadertable.setCharacterSize(24);
        game.leadertable.setFillColor(sf::Color::White);
        
        
       

       

    }

    void UpdateGame(Game& game, Player& player, Apple& apples, Rock& rocks, float deltaTime)
    {
        if (!game.isGameStarted) return; // Не обновляем игру, пока не выбран режим

        if (!game.isGameFinished)
        {
            if (game.needReinitApples)
            {
                InitApples(apples, game);
                game.needReinitApples = false;
            }
            // Движение игрока
            switch (player.playerDirection)
            {
            case PlayerDirection::Right: player.playerPosition.x += player.playerSpeed * deltaTime; break;
            case PlayerDirection::Up:    player.playerPosition.y -= player.playerSpeed * deltaTime; break;
            case PlayerDirection::Left:  player.playerPosition.x -= player.playerSpeed * deltaTime; break;
            case PlayerDirection::Down:  player.playerPosition.y += player.playerSpeed * deltaTime; break;
            }

            // Проверка границ экрана
            if (player.playerPosition.x - PLAYER_SIZE / 2 < 0 ||
                player.playerPosition.x + PLAYER_SIZE / 2 > SCREEN_WIDTH ||
                player.playerPosition.y - PLAYER_SIZE / 2 < 0 ||
                player.playerPosition.y + PLAYER_SIZE / 2 > SCREEN_HEIGHT)
            {
                game.isGameFinished = true;
                game.gameFinishTime = 0.f;
                game.deathSound.play();
            }
            int appleCount;
            if (game.gameMode & MODE_50_APPLES)
            {
                appleCount = NUM_APPLES_EXTENDED;
            }
            else
            {
                appleCount = NUM_APPLES;
            }
            // Обработка столкновений с яблоками
            for (int i = 0; i < appleCount; ++i)
            {
                if (!apples.isAppleEaten[i] &&IsCirclesCollide(player.playerPosition, PLAYER_SIZE / 2,apples.applesPositions[i], APPLE_SIZE / 2))
                {
                    game.numEatenApples++;
                    game.eatSound.play();

                    // Ускорение только если не установлен флаг NO_ACCELERATION
                    if (!(game.gameMode & MODE_NO_ACCELERATION))
                    {
                        player.playerSpeed += ACCELERATION;
                        if (player.playerSpeed > MAX_SPEED)
                            player.playerSpeed = MAX_SPEED;
                    }

                    // Для бесконечных яблок создаем новое
                    if (game.gameMode & MODE_INFINITE_APPLES)
                    {
                        apples.applesPositions[i] = GetRandomPositionInScreen();
                        apples.applesSprite[i].setPosition(apples.applesPositions[i].x,apples.applesPositions[i].y);
                    }
                    else
                    {
                        apples.isAppleEaten[i] = true;
                    }
                }
            }

            int targetApples;
            if (game.gameMode & MODE_50_APPLES)
            {
                targetApples = NUM_APPLES_EXTENDED;
            }
            else
            {
                targetApples = NUM_APPLES;
            }

            // Проверка условия победы (если не бесконечные яблоки)
            if (!(game.gameMode & MODE_INFINITE_APPLES) && game.numEatenApples >= targetApples)
            {
                game.isGameFinished = true;
                game.gameFinishTime = 0.f;
                
            }

            // Обработка столкновений с камнями
            for (int i = 0; i < NUM_ROCKS; ++i)
            {
                if (IsCirclesCollide(player.playerPosition, PLAYER_SIZE / 2,
                    rocks.rocksPositions[i], ROCK_SIZE / 2))
                {
                    game.isGameFinished = true;
                    game.gameFinishTime = 0.f;
                    game.deathSound.play();
                    break;
                }
            }
        }
        //else
        //{
        //    game.gameFinishTime += deltaTime;
        //    if (game.gameFinishTime > PAUSE_LENGTH)
        //    {
        //         /*При рестарте сбрасываем флаг начала игры*/
        //        game.isGameStarted = false;
        //        InitGame(player, apples, rocks, game, *game.scoreText.getFont());
        //    }
        //}

        if (game.isGameFinished && (game.gameMode & MODE_INFINITE_APPLES))
        
        {
            for (auto& rec :leaderboard)
            {
                if (rec.name == "Player" && game.numEatenApples > rec.score)
                {
                    rec.score = game.numEatenApples;
                }
            }
           SortLeaderboard(leaderboard);
        }
        
    }

    void RenderGame(sf::RenderWindow& window, Game& game, Player& player, Apple& apples, Rock& rocks)
    {
        window.clear();

        if (!game.isGameStarted)
        {
            ShowModeSelectionScreen(window, game);
            return;
        }

        if (game.isGameFinished && game.gameFinishTime <= PAUSE_LENGTH)
        {
            game.background.setFillColor(sf::Color::Red);
        }
        else
        {
            game.background.setFillColor(sf::Color::Black);
        }
        window.draw(game.background);

        if (game.isGameFinished && game.gameFinishTime <= PAUSE_LENGTH)
        {
            int targetApples;
            if (game.gameMode & MODE_50_APPLES)
            {
                targetApples = NUM_APPLES_EXTENDED;
            }
            else
            {
                targetApples = NUM_APPLES;
            }

            if ((!(game.gameMode & MODE_INFINITE_APPLES) && game.numEatenApples >= targetApples)) 
            {
                game.gameOverText.setString("YOU WIN!");
            }
            else
            {
                game.gameOverText.setString("GAME OVER");
            }
           

            window.draw(game.gameOverText);
            float y = 300;// позицию по вертикали
            int index = 1;// место игрока в списке
            if (game.isGameFinished && (game.gameMode & MODE_INFINITE_APPLES))
            {
                for (const auto& rec : leaderboard)
                {
                   
                    game.leadertable.setPosition(200, y);
                    game.leadertable.setString(std::to_string(index) + ". " + rec.name + " - " + std::to_string(rec.score));
                    window.draw(game.leadertable);

                    y += 30;
                    ++index;
                }
            }
        }

        player.playerSprite.setPosition(player.playerPosition.x, player.playerPosition.y);
        window.draw(player.playerSprite);

        // Определяем количество яблок для отрисовки
        int appleCount;
        if (game.gameMode & MODE_50_APPLES)
        {
            appleCount = NUM_APPLES_EXTENDED;
        }
        else
        {
            appleCount = NUM_APPLES;
        }

        for (int i = 0; i < appleCount; ++i)
        {
            if (!apples.isAppleEaten[i])
            {
                window.draw(apples.applesSprite[i]);
            }
        }

        for (int i = 0; i < NUM_ROCKS; ++i)
        {
            window.draw(rocks.rocksSprite[i]);
        }

        window.draw(game.inputHintText);

        std::stringstream scoreText;
        scoreText << "Apples eaten: " << game.numEatenApples;

        if (!(game.gameMode & MODE_INFINITE_APPLES))
        {
            if (game.gameMode & MODE_50_APPLES)
            {
                scoreText << " / " << NUM_APPLES_EXTENDED;
            }
            else
            {
                scoreText << " / " << NUM_APPLES;
            }
        }

        game.scoreText.setString(scoreText.str());
        window.draw(game.scoreText);

        window.display();
    }

    void HandleModeSelection(Game& game, sf::Event event)
    {
        if (event.type == sf::Event::KeyPressed && !game.isGameStarted)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Num1: // Стандартный режим (20 яблок с ускорением)
                game.gameMode = MODE_DEFAULT;
                game.isGameStarted = true;
                break;

            case sf::Keyboard::Num2: // Бесконечные яблоки с ускорением
                game.gameMode = MODE_INFINITE_APPLES;
                game.isGameStarted = true;
                break;

            case sf::Keyboard::Num3: // 20 яблок без ускорения
                game.gameMode = MODE_NO_ACCELERATION;
                game.isGameStarted = true;
                break;

            case sf::Keyboard::Num4: // Бесконечные яблоки без ускорения
                game.gameMode = MODE_INFINITE_APPLES | MODE_NO_ACCELERATION;
                game.isGameStarted = true;
                break;
            case sf::Keyboard::Num5:
                game.gameMode = MODE_50_APPLES; // Только 50 яблок
                game.isGameStarted = true;
                break;
            }
        }
    }

    void ShowModeSelectionScreen(sf::RenderWindow& window, Game& game)
    {
        sf::Text title;
        title.setFont(*game.scoreText.getFont());
        title.setString("Select Game Mode:");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::White);
        title.setPosition(250, 100);

        sf::Text mode1;
        mode1.setFont(*game.scoreText.getFont());
        mode1.setString("1 - Standard (20 apples with acceleration)");
        mode1.setCharacterSize(30);
        mode1.setFillColor(sf::Color::Green);
        mode1.setPosition(150, 200);

        sf::Text mode2;
        mode2.setFont(*game.scoreText.getFont());
        mode2.setString("2 - Infinite apples with acceleration");
        mode2.setCharacterSize(30);
        mode2.setFillColor(sf::Color::Green);
        mode2.setPosition(150, 250);

        sf::Text mode3;
        mode3.setFont(*game.scoreText.getFont());
        mode3.setString("3 - 20 apples without acceleration");
        mode3.setCharacterSize(30);
        mode3.setFillColor(sf::Color::Green);
        mode3.setPosition(150, 300);

        sf::Text mode4;
        mode4.setFont(*game.scoreText.getFont());
        mode4.setString("4 - Infinite apples without acceleration");
        mode4.setCharacterSize(30);
        mode4.setFillColor(sf::Color::Green);
        mode4.setPosition(150, 350);

        sf::Text mode5;
        mode5.setFont(*game.scoreText.getFont());
        mode5.setString("5 - 50 apples with acceleration");
        mode5.setCharacterSize(30);
        mode5.setFillColor(sf::Color::Green);
        mode5.setPosition(150, 400);

        window.clear();
        window.draw(title);
        window.draw(mode1);
        window.draw(mode2);
        window.draw(mode3);
        window.draw(mode4);
        window.draw(mode5);
        window.display();
    }
}