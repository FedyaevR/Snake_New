#include "GameStateGameOver.h"
#include "Settings.h"
#include <cassert>
#include "Math.h"

namespace GameStateGameOverData
{
    void GameStateGameOverData::InitGameStateGameOver()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        timeSinceGameOver = 0.f;

        gameOverText.setFont(font);
        gameOverText.setCharacterSize(48);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setString("GAME OVER");
        gameOverText.setOrigin(Math::GetItemOrigin(gameOverText, { 0.5f, 0.5f }));

        hintText.setFont(font);
        hintText.setCharacterSize(24);
        hintText.setFillColor(sf::Color::White);
        hintText.setString("Press Space to restart");
        hintText.setOrigin(Math::GetItemOrigin(hintText, { 0.5f, 1.f }));

        recordsTableText.setFont(font);
        recordsTableText.setCharacterSize(24);
        recordsTableText.setFillColor(sf::Color::Green);
        recordsTableText.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
        recordsTableText.setOrigin(Math::GetItemOrigin(recordsTableText, { 0.5f, 0.f }));
    }

    void GameStateGameOverData::ShutdownGameStateGameOver()
    {
    }

    void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Core_Game::Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                game.RestartGame();
                game.SwitchGameState(GameState::GameStateType::Playing);
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                game.SwitchGameState(GameState::GameStateType::MainMenu);
            }
        }
    }

    // ѕозже передать саму таблицу рекордов
    void UpdateGameStateGameOver(GameStateGameOverData& data, float timeDelta)
    {
        data.timeSinceGameOver += timeDelta;

        sf::Color gameOverTextColor = (int)data.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
        data.gameOverText.setFillColor(gameOverTextColor);

        data.recordsTableText.setString("Records:");

        // а тут таблица будет использоватьс€ как раз
     /*   for (const RecordsTableItem& item : recordsTable)
        {
            recordsTableText.setString(recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
        }*/

        data.recordsTableText.setOrigin(Math::GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
    }

    void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = window.getView().getSize();

        data.gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
        window.draw(data.gameOverText);

        data.recordsTableText.setPosition(viewSize.x / 2.f, 30.f);
        window.draw(data.recordsTableText);

        data.hintText.setPosition(viewSize.x / 2.f, viewSize.y - 10.f);
        window.draw(data.hintText);
    }
}