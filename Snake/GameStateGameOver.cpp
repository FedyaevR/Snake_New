#include "GameStateGameOver.h"
#include "Settings.h"
#include <cassert>
#include "Math.h"

namespace GameStateGameOverData
{
    void GameStateGameOverData::InitGameStateGameOver()
    {
        if(font.loadFromFile(Settings::DEFAULT_FONT_PATH))
        {
            std::cout << "Loaded Default font path is failed" << std::endl;

            throw std::invalid_argument("Default font path could not be loaded");
        }

        timeSinceGameOver = 0.f;

        menu.rootItem.childrenOrientation = Math::Orientation::Vertical;
        menu.rootItem.childrenAlignment = Math::Alignment::Middle;
        menu.rootItem.childrenSpacing = 10.f;
        menu.rootItem.children.push_back(&restartGameItem);
        menu.rootItem.children.push_back(&inMainMenu);

        restartGameItem.text.setString("Restart Game");
        restartGameItem.text.setFont(font);
        restartGameItem.text.setCharacterSize(24);

        inMainMenu.text.setString("Exit in main menu");
        inMainMenu.text.setFont(font);
        inMainMenu.text.setCharacterSize(24);

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setOrigin(Math::GetItemOrigin(scoreText, { 0.5f, 1.f }));

        recordsTableText.setFont(font);
        recordsTableText.setCharacterSize(24);
        recordsTableText.setFillColor(sf::Color::Green);
        recordsTableText.setOrigin(Math::GetItemOrigin(recordsTableText, { 0.5f, 0.f }));

        InitMenuItem(menu.rootItem);
        SelectMenuItem(menu, &restartGameItem);
    }

    void GameStateGameOverData::ShutdownGameStateGameOver()
    {
    }

    void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Core_Game::Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                if (data.menu.selectedItem == &data.restartGameItem)
                {
                    game.SwitchGameState(GameState::GameStateType::Playing);
                }
                else if (data.menu.selectedItem == &data.inMainMenu)
                {
                    game.SwitchGameState(GameState::GameStateType::MainMenu);
                }

                game.RestartGame();
            }

            Math::Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
            if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
                orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::W ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::Left ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::A)
            {
                SelectPreviousMenuItem(data.menu);
            }
            else if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
                orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::S ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::Right ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::D)
            {
                SelectNextMenuItem(data.menu);
            }
        }
    }

    void UpdateGameStateGameOver(GameStateGameOverData& data, Core_Game::Game& game, float timeDelta)
    {
        data.timeSinceGameOver += timeDelta;
        data.scoreText.setString("Your score: " + std::to_string(game.score));

        data.recordsTableText.setString("Records:");
        for (const auto& item : game.recordsTable)
        {
            data.recordsTableText.setString(data.recordsTableText.getString() + "\n" + item.name + ": " + std::to_string(item.score));
        }

        data.recordsTableText.setOrigin(Math::GetItemOrigin(data.recordsTableText, { 0.5f, 0.f }));
    }

    void DrawGameStateGameOver(GameStateGameOverData& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = window.getView()
                                      .getSize();

        data.scoreText.setPosition(viewSize.x / 2.f, 30.f);
        window.draw(data.scoreText);

        data.recordsTableText.setPosition((viewSize.x / 2.f) + 90.f, data.scoreText.getPosition().y + 35.f);
        window.draw(data.recordsTableText);

        DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
    }
}