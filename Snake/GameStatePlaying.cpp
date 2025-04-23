#include "GameStatePlaying.h"
#include "Settings.h"
#include "Math.h"
#include <cassert>


namespace GameStatePlayingData
{
    void GameStatePlayingData::InitGameStatePlaying()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::Yellow);
        inputHintText.setFont(font);
        inputHintText.setCharacterSize(24);
        inputHintText.setFillColor(sf::Color::White);
        inputHintText.setString("Use arrow keys to move, ESC to exit");
        inputHintText.setOrigin(Math::GetItemOrigin(inputHintText, { 1.f, 0.f }));
    }

    void GameStatePlayingData::ShutdownGameStatePlaying()
    {
    }

    void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Core_Controller::Controller& controller, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                controller.PushGameState(GameState::GameStateType::ExitDialog, false);
            }
        }
    }

    void UpdateGameStatePlaying(GameStatePlayingData& data, float timeDelta)
    {
        // ћожно будет сюда перенести управление состо€нием игры как раз, но позже
    }

    void DrawGameStatePlaying(GameStatePlayingData& data, sf::RenderWindow& window)
    {
        data.scoreText.setPosition(10.f, 10.f);
        window.draw(data.scoreText);

        sf::Vector2f viewSize = window.getView().getSize();
        data.inputHintText.setPosition(viewSize.x - 10.f, 10.f);
        window.draw(data.inputHintText);
    }
}