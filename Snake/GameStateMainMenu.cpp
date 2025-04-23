#include "Controller.h"
#include "GameStateMainMenu.h"
#include "Math.h"
#include "Settings.h"
#include <cassert>
#include <SFML/Graphics.hpp>

namespace GameStateMainMenuData
{
    void GameStateMainMenuData::InitGameStateMainMenu()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        menu.rootItem.hintText.setString("Apples Game");
        menu.rootItem.hintText.setFont(font);
        menu.rootItem.hintText.setCharacterSize(48);
        menu.rootItem.hintText.setFillColor(sf::Color::Red);
        menu.rootItem.childrenOrientation = Math::Orientation::Vertical;
        menu.rootItem.childrenAlignment = Math::Alignment::Middle;
        menu.rootItem.childrenSpacing = 10.f;
        menu.rootItem.children.push_back(&startGameItem);
        menu.rootItem.children.push_back(&optionsItem);
        menu.rootItem.children.push_back(&exitGameItem);

        startGameItem.text.setString("Start Game");
        startGameItem.text.setFont(font);
        startGameItem.text.setCharacterSize(24);

        optionsItem.text.setString("Options");
        optionsItem.text.setFont(font);
        optionsItem.text.setCharacterSize(24);
        optionsItem.hintText.setString("Options");
        optionsItem.hintText.setFont(font);
        optionsItem.hintText.setCharacterSize(48);
        optionsItem.hintText.setFillColor(sf::Color::Red);
        optionsItem.childrenOrientation = Math::Orientation::Vertical;
        optionsItem.childrenAlignment = Math::Alignment::Middle;
        optionsItem.childrenSpacing = 10.f;
        optionsItem.children.push_back(&optionsInfiniteApplesItem);
        optionsItem.children.push_back(&optionsWithAccelerationItem);

        optionsInfiniteApplesItem.text.setString("Infinite Apples: On/Off");
        optionsInfiniteApplesItem.text.setFont(font);
        optionsInfiniteApplesItem.text.setCharacterSize(24);

        optionsWithAccelerationItem.text.setString("With Acceleration: On/Off");
        optionsWithAccelerationItem.text.setFont(font);
        optionsWithAccelerationItem.text.setCharacterSize(24);

        exitGameItem.text.setString("Exit Game");
        exitGameItem.text.setFont(font);
        exitGameItem.text.setCharacterSize(24);
        exitGameItem.hintText.setString("Are you sure?");
        exitGameItem.hintText.setFont(font);
        exitGameItem.hintText.setCharacterSize(48);
        exitGameItem.hintText.setFillColor(sf::Color::Red);
        exitGameItem.childrenOrientation = Math::Orientation::Horizontal;
        exitGameItem.childrenAlignment = Math::Alignment::Middle;
        exitGameItem.childrenSpacing = 10.f;
        exitGameItem.children.push_back(&yesItem);
        exitGameItem.children.push_back(&noItem);

        yesItem.text.setString("Yes");
        yesItem.text.setFont(font);
        yesItem.text.setCharacterSize(24);

        noItem.text.setString("No");
        noItem.text.setFont(font);
        noItem.text.setCharacterSize(24);

        InitMenuItem(menu.rootItem);
        SelectMenuItem(menu, &startGameItem);
    }

    void GameStateMainMenuData::ShutdownGameStateMainMenu()
    {
        // No need to do anything here
    }

    void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data,Core_Controller::Controller& controller, const sf::Event& event)
    {
        if (!data.menu.selectedItem)
        {
            return;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                CollapseSelectedItem(data.menu);
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                if (data.menu.selectedItem == &data.startGameItem)
                {
                    controller.SwitchGameState(GameState::GameStateType::Playing);
                }
                else if (data.menu.selectedItem == &data.optionsItem)
                {
                    ExpandSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.optionsInfiniteApplesItem)
                {
                    //game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::InfiniteApples);
                }
                else if (data.menu.selectedItem == &data.optionsWithAccelerationItem)
                {
                    //game.options = (GameOptions)((std::uint8_t)game.options ^ (std::uint8_t)GameOptions::WithAcceleration);
                }
                else if (data.menu.selectedItem == &data.exitGameItem)
                {
                    ExpandSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.yesItem)
                {
                    controller.SwitchGameState(GameState::GameStateType::None);
                }
                else if (data.menu.selectedItem == &data.noItem)
                {
                    CollapseSelectedItem(data.menu);
                }
                else
                {
                    ExpandSelectedItem(data.menu);
                }
            }

            Math::Orientation orientation = data.menu.selectedItem->parent->childrenOrientation;
            if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
            {
                SelectPreviousMenuItem(data.menu);
            }
            else if (orientation == Math::Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
                orientation == Math::Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
            {
                SelectNextMenuItem(data.menu);
            }
        }
    }

    void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta)
    {
        // Добавить опции!!
        //bool isInfiniteApples = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples) != (std::uint8_t)GameOptions::Empty;
        //optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));

        //bool isWithAcceleration = ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration) != (std::uint8_t)GameOptions::Empty;
        //optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
    }

    void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

        sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
        hintText->setOrigin(Math::GetItemOrigin(*hintText, { 0.5f, 0.f }));
        hintText->setPosition(viewSize.x / 2.f, 150.f);
        window.draw(*hintText);

        DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
    }
}