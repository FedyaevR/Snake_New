#include "GameStatePauseDialog.h"
#include "Settings.h"
#include "Math.h"
#include <cassert>

namespace GameStatePauseDialogData
{
    void GameStatePauseDialogData::InitGameStatePauseDialog()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        hintText.setString("Enter - Continue, Esc - Exit game");
        hintText.setFont(font);
        hintText.setCharacterSize(24);
        hintText.setFillColor(sf::Color::White);
        hintText.setOrigin(Math::GetItemOrigin(hintText, { 0.5f, 0.5f }));

        background.setFillColor(sf::Color(0, 0, 0, 128)); 
    }

    void GameStatePauseDialogData::ShutdownGameStatePauseDialog()
    {
    }

    void HandleGameStatePauseDialogWindowEvent(GameStatePauseDialogData& data, Core_Game::Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.PopGameState();
                game.wasPause = true;
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                game.SwitchGameState(GameState::GameStateType::MainMenu);
            }
        }

    }

    void UpdateGameStatePauseDialog(GameStatePauseDialogData& data, float timeDelta)
    {

    }

    void DrawGameStatePauseDialog(GameStatePauseDialogData& data, sf::RenderWindow& window)
    {
        sf::Vector2f windowSize = (sf::Vector2f)window.getSize();

        data.background.setSize(windowSize);
        window.draw(data.background);

        data.hintText.setPosition(windowSize / 2.f);
        window.draw(data.hintText);
    }
}