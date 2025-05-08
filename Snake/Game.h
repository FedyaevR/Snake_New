#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "GameState.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <SFML/Audio.hpp>

namespace Core_Game
{
    struct RecordsTableItem
    {
        std::string name;
        int score = 0;
        bool isCurrentPlayer = false;
    };

    struct Game
    {
        std::vector<GameState::GameState> gameStateStack;
        GameState::GameStateChangeType gameStateChangeType = GameState::GameStateChangeType::None;
        GameState::GameStateType pendingGameStateType = GameState::GameStateType::None;
        bool pendingGameStateIsExclusivelyVisible = false;

        GameState::GameOptions options = GameState::GameOptions::Default;

        float deltaTime;

        Snake::Snake snake;
        Apple::Apple apple;
        Settings::Settings settings;

        bool wasPause = false;
        bool isStart = false;

        int scoreForApple = Settings::SCORE_FOR_APPLE;

        int score = 0;

        bool music = true;
        bool sound = true;

        std::string userName;

        std::vector<RecordsTableItem> recordsTable;

        sf::SoundBuffer appleSoundBuffer;
        sf::Sound appleSound;
        sf::SoundBuffer hitSoundBuffer;
        sf::Sound hitSound;
        sf::SoundBuffer loseSoundBuffer;
        sf::Sound loseSound;
        sf::Music backgroundMusic;

        float screenWidth;
        float screenHeight;

        Game(): snake(),
                apple(),
                settings()
        {
            settings.deltaTime = 0.0f;

            settings.partSize = Settings::SNAKE_PART_SIZE;
            settings.moveSpeed = 0.8f;

            gameStateChangeType = GameState::GameStateChangeType::None;
            pendingGameStateType = GameState::GameStateType::None;
            pendingGameStateIsExclusivelyVisible = false;

            userName = "XYZ";

            SwitchGameState(GameState::GameStateType::MainMenu);
            InitRecordTable();

            InitSound();
        }

        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

        Game(Game&&) = default;
        Game& operator=(Game&&) = default;


        void MoveInput();
        bool IsMoveUp(Snake_Direction::Direction currentDirection);
        bool IsMoveDown(Snake_Direction::Direction currentDirection);
        bool IsMoveLeft(Snake_Direction::Direction currentDirection);
        bool IsMoveRight(Snake_Direction::Direction currentDirection);

        void SetSettingsWithDifficultyLevel();

        bool UpdateGame();

        void HandleWindowEvents(sf::RenderWindow& window);
        void HandleWindowEventGameState(sf::Event& event);

        void SwitchGameState(GameState::GameStateType newState);

        void RestartGame();

        void PushGameState(GameState::GameStateType stateType, bool isExclusivelyVisible);

        void PopGameState();

        void InitGameState(GameState::GameState& state);
        void UpdateGameState(GameState::GameState& state);
        void DrawGameState(GameState::GameState& state, sf::RenderWindow& window);
        void DrawGame(sf::RenderWindow& window);
        std::string GetSettingInString(std::string settingName);
        std::string GetInString(bool value);

        void InitRecordTable();
        void SortRecordTable();

        bool Serialize();
        bool Deserialize();

        void InitSound();
        void InitScreenSize();
    };
}