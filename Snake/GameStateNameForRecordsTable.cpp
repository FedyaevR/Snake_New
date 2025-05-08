#include "GameStateNameForRecordsTable.h"
#include "Settings.h"
#include "Math.h"
#include <cassert>
#include <iostream>

namespace GameStateNameForRecordsTable
{
    void GameStateNameForRecordsTable::InitGameStateNameForRecords()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        menu.rootItem.hintText.setString("Input your name");
        menu.rootItem.hintText.setFont(font);
        menu.rootItem.hintText.setCharacterSize(34);
        menu.rootItem.hintText.setFillColor(sf::Color::White);
        menu.rootItem.childrenOrientation = Math::Orientation::Vertical;
        menu.rootItem.childrenAlignment = Math::Alignment::Middle;
        menu.rootItem.childrenSpacing = 10.f;
        menu.rootItem.children.push_back(&yesItem);
        menu.rootItem.children.push_back(&noItem);

        yesItem.text.setString("Yes");
        yesItem.text.setFont(font);
        yesItem.text.setCharacterSize(24);
        yesItem.hintText.setString("Input your name\nPress \"Enter\" to continue");
        yesItem.hintText.setFont(font);
        yesItem.hintText.setCharacterSize(34);
        yesItem.hintText.setFillColor(sf::Color::White);
        yesItem.childrenOrientation = Math::Orientation::Vertical;
        yesItem.childrenAlignment = Math::Alignment::Middle;
        yesItem.childrenSpacing = 10.f;
        yesItem.children.push_back(&inputItem);

        inputItem.text.setFont(font);
        inputItem.text.setCharacterSize(24);

        noItem.text.setString("No");
        noItem.text.setFont(font);
        noItem.text.setCharacterSize(24);

        inputNameText.setFont(font);
        inputNameText.setCharacterSize(24);

        InitMenuItem(menu.rootItem);
        SelectMenuItem(menu, &noItem);
    }

    void HandleGameStateNameForRecordWindowEvent(GameStateNameForRecordsTable& data, Core_Game::Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b') 
            { 
                if (!data.userName.empty())
                {
                    data.userName.pop_back();
                }
            }

            if (event.text.unicode >= 32 && event.text.unicode < 128) 
            {
                data.userName += static_cast<char>(event.text.unicode);
            }

            data.inputNameText.setString("Input here: " + data.userName);
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                if (data.menu.selectedItem == &data.noItem)
                {
                    game.SwitchGameState(GameState::GameStateType::GameOver);
                }
                else if (data.menu.selectedItem == &data.yesItem)
                {
                    ExpandSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.inputItem)
                {
                    game.userName = data.userName;

                    for (size_t i = 0; i < game.recordsTable.size(); i++)
                    {
                        if (game.recordsTable[i].isCurrentPlayer)
                        {
                            game.recordsTable[i].name = game.userName;
                            game.recordsTable[i].score = game.score;
                        }
                    }

                    game.SortRecordTable();
                    game.SwitchGameState(GameState::GameStateType::GameOver);
                }
            }

            Math::Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
            if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
                orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::W)
            {
                SelectPreviousMenuItem(data.menu);
            }
            else if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
                orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::S)
            {
                SelectNextMenuItem(data.menu);
            }
        }
    }

    void UpdateGameStateNameForRecord(GameStateNameForRecordsTable& data, float timeDelta, Core_Game::Game& game)
    {
    }

    void DrawGameStateNameForRecord(GameStateNameForRecordsTable& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

        sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
        hintText->setOrigin(Math::GetItemOrigin(*hintText, { 0.5f, 0.f }));
        hintText->setPosition(viewSize.x / 2.f, 150.f);
        window.draw(*hintText);

        data.inputNameText.setPosition((viewSize.x / 2.f) - 110.f, viewSize.y / 2.f);
        window.draw(data.inputNameText);

        DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
    }
}
