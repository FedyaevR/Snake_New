#include "GameStateExitDialog.h"
#include "Settings.h"
#include "Math.h"
#include <cassert>

namespace GameStateExitDialogData
{
    void GameStateExitDialogData::InitGameStateExitDialog()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        hintText.setString("Are you sure you want to stop this game? Enter - Yes, Esc - No");
        hintText.setFont(font);
        hintText.setCharacterSize(24);
        hintText.setFillColor(sf::Color::White);
        hintText.setOrigin(Math::GetItemOrigin(hintText, { 0.5f, 0.5f }));

        background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
    }

    void GameStateExitDialogData::ShutdownGameStateExitDialog()
    {
        // We dont need to free resources here, because they will be freed automatically
    }

    void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Core_Game::Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                game.PopGameState();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                game.SwitchGameState(GameState::GameStateType::MainMenu);
            }
        }
    }

    void UpdateGameStateExitDialog(GameStateExitDialogData& data, float timeDelta)
    {

    }

    void DrawGameStateExitDialog(GameStateExitDialogData& data, sf::RenderWindow& window)
    {
        sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

        data.background.setSize(windowSize);
        window.draw(data.background);

        data.hintText.setPosition(windowSize / 2.f);
        window.draw(data.hintText);
    }
}