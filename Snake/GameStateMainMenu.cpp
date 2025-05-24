#include "GameStateMainMenu.h"
#include "Math.h"
#include "Settings.h"
#include <cassert>
#include <SFML/Graphics.hpp>

namespace GameStateMainMenuData
{
    void GameStateMainMenuData::InitGameStateMainMenu()
    {
        if(font.loadFromFile(Settings::DEFAULT_FONT_PATH))
        {
            std::cout << "Loaded Default font path is failed" << std::endl;

            throw std::invalid_argument("Default font path could not be loaded");
        }

        menu.rootItem.hintText.setString("Snake Game");
        menu.rootItem.hintText.setFont(font);
        menu.rootItem.hintText.setCharacterSize(48);
        menu.rootItem.hintText.setFillColor(sf::Color::Red);
        menu.rootItem.childrenOrientation = Math::Orientation::Vertical;
        menu.rootItem.childrenAlignment = Math::Alignment::Middle;
        menu.rootItem.childrenSpacing = 10.f;
        menu.rootItem.children.push_back(&startGameItem);
        menu.rootItem.children.push_back(&recordsTable);
        menu.rootItem.children.push_back(&difficultyLevel);
        menu.rootItem.children.push_back(&settings);
        menu.rootItem.children.push_back(&exitGameItem);

        startGameItem.text.setString("Start Game");
        startGameItem.text.setFont(font);
        startGameItem.text.setCharacterSize(24);

        settings.text.setString("Settings");
        settings.text.setFont(font);
        settings.text.setCharacterSize(24);
        settings.hintText.setString("Settings");
        settings.hintText.setFont(font);
        settings.hintText.setCharacterSize(48);
        settings.hintText.setFillColor(sf::Color::Red);
        settings.childrenOrientation = Math::Orientation::Vertical;
        settings.childrenAlignment = Math::Alignment::Middle;
        settings.childrenSpacing = 10.f;

        settings.children.push_back(&settingsMusic);
        settings.children.push_back(&settingsSound);

        settingsMusic.text.setString("Music");
        settingsMusic.text.setFont(font);
        settingsMusic.text.setCharacterSize(24);
        
        settingsMusic.switchText.setFont(font);
        settingsMusic.switchText.setCharacterSize(24);
        settingsMusic.switchText.setFillColor(sf::Color::White);

        settingsSound.text.setString("Sound");
        settingsSound.text.setFont(font);
        settingsSound.text.setCharacterSize(24);

        settingsSound.switchText.setFont(font);
        settingsSound.switchText.setCharacterSize(24);
        settingsSound.switchText.setFillColor(sf::Color::White);


        difficultyLevel.text.setString("Difficulty level");
        difficultyLevel.text.setFont(font);
        difficultyLevel.text.setCharacterSize(24);
        difficultyLevel.hintText.setString("Difficulty level");
        difficultyLevel.hintText.setFont(font);
        difficultyLevel.hintText.setCharacterSize(48);
        difficultyLevel.hintText.setFillColor(sf::Color::Red);

        difficultyLevel.childrenOrientation = Math::Orientation::Vertical;
        difficultyLevel.childrenAlignment = Math::Alignment::Middle;
        difficultyLevel.childrenSpacing = 10.f;

        difficultyLevel.children.push_back(&difficultyEasyLevel);
        difficultyLevel.children.push_back(&difficultyHarderThanEasyLevel);
        difficultyLevel.children.push_back(&difficultyMediumLevel);
        difficultyLevel.children.push_back(&difficultyEasierThanHardLevel);
        difficultyLevel.children.push_back(&difficultyHardLevel);

        difficultyEasyLevel.text.setString("Easy level");
        difficultyEasyLevel.text.setFont(font);
        difficultyEasyLevel.text.setCharacterSize(24);

        difficultyHarderThanEasyLevel.text.setString("Harder than easy level");
        difficultyHarderThanEasyLevel.text.setFont(font);
        difficultyHarderThanEasyLevel.text.setCharacterSize(24);

        difficultyMediumLevel.text.setString("Medium level");
        difficultyMediumLevel.text.setFont(font);
        difficultyMediumLevel.text.setCharacterSize(24);

        difficultyEasierThanHardLevel.text.setString("Easier than hard level");
        difficultyEasierThanHardLevel.text.setFont(font);
        difficultyEasierThanHardLevel.text.setCharacterSize(24);

        difficultyHardLevel.text.setString("Hard level");
        difficultyHardLevel.text.setFont(font);
        difficultyHardLevel.text.setCharacterSize(24);

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

        recordsTable.text.setString("Records table");
        recordsTable.text.setFont(font);
        recordsTable.text.setCharacterSize(24);
        recordsTable.hintText.setString("Records table");
        recordsTable.hintText.setFont(font);
        recordsTable.hintText.setCharacterSize(48);
        recordsTable.hintText.setFillColor(sf::Color::Red);

        InitMenuItem(menu.rootItem);
        SelectMenuItem(menu, &startGameItem);
    }

    void GameStateMainMenuData::ShutdownGameStateMainMenu()
    {
    }

    void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Core_Game::Game& game, const sf::Event& event)
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
                    game.SwitchGameState(GameState::GameStateType::Playing);
                }
                else if (data.menu.selectedItem == &data.settings)
                {
                    data.settingsMusic.switchText.setString(game.GetSettingInString("music"));
                    data.settingsSound.switchText.setString(game.GetSettingInString("sound"));

                    ExpandSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.difficultyEasyLevel)
                {
                    game.options = GameState::GameOptions::Easy;

                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.difficultyHarderThanEasyLevel)
                {
                    game.options = GameState::GameOptions::HarderThanEasy;

                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.difficultyMediumLevel)
                {
                    game.options = GameState::GameOptions::Medium;

                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.difficultyEasierThanHardLevel)
                {
                    game.options = GameState::GameOptions::EasierThanHard;

                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.difficultyHardLevel)
                {
                    game.options = GameState::GameOptions::Hard;

                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.exitGameItem)
                {
                    ExpandSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.yesItem)
                {
                    game.SwitchGameState(GameState::GameStateType::None);
                }
                else if (data.menu.selectedItem == &data.noItem)
                {
                    CollapseSelectedItem(data.menu);
                }
                else if (data.menu.selectedItem == &data.settingsMusic)
                {
                    game.music = !game.music;

                    if (game.music)
                    {
                        game.backgroundMusic.play();
                    }
                    else 
                    {
                        game.backgroundMusic.stop();
                    }

                    SelectSwitchSetting(*data.menu.selectedItem, game);
                }
                else if (data.menu.selectedItem == &data.settingsSound)
                {
                    game.sound = !game.sound;

                    SelectSwitchSetting(*data.menu.selectedItem, game);
                }
                else if (data.menu.selectedItem == &data.recordsTable)
                {
                    if (data.isRecordTablePrepared == false)
                    {
                        auto& selectedItem = data.menu.selectedItem;
                        selectedItem->childrenOrientation = Math::Orientation::Vertical;
                        selectedItem->childrenAlignment = Math::Alignment::Middle;
                        selectedItem->childrenSpacing = 10.f;

                        for (size_t i = 0; i < game.recordsTable.size(); i++)
                        {
                            auto item = game.recordsTable[i];
                            auto menuItem = new Menu::MenuItem();
                            menuItem->text.setString(item.name + "\t\t" + std::to_string(item.score));
                            menuItem->text.setFont(data.font);
                            menuItem->text.setCharacterSize(24);
                            menuItem->parent = selectedItem;

                            data.playersForTable.push_back(*menuItem);

                            selectedItem->children.push_back(menuItem);
                        }

                        data.isRecordTablePrepared = true;
                    }

                    ExpandSelectedItem(data.menu);
                }
                else
                {
                    ExpandSelectedItem(data.menu);
                }
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

            game.SetSettingsWithDifficultyLevel();
        }
    }

    void UpdateGameStateMainMenu(GameStateMainMenuData& data, float timeDelta)
    {
    }

    void DrawGameStateMainMenu(GameStateMainMenuData& data, sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getSize();

        sf::Text* hintText = &GetCurrentMenuContext(data.menu)->hintText;
        hintText->setOrigin(Math::GetItemOrigin(*hintText, { 0.5f, 0.f }));
        hintText->setPosition(viewSize.x / 2.f, 150.f);
        window.draw(*hintText);

        auto currentMenu = data.menu.selectedItem;
        sf::Text* switchText = &currentMenu->switchText;
        switchText->setOrigin(Math::GetItemOrigin(*switchText, { 0.5f, 0.f }));
        switchText->setPosition(currentMenu->text.getPosition().x + 100.f, currentMenu->text.getPosition().y);
        window.draw(*switchText);

        DrawMenu(data.menu, window, viewSize / 2.f, { 0.5f, 0.f });
    }
}