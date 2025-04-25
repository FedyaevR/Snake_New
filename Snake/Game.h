#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "GameState.h"


namespace Core_Game
{
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

        bool isStart = false;

        int scoreForApple = 2;

        int score = 0;

        Game()
        {
            snake = Snake::Snake();
            apple = Apple::Apple();

            settings = Settings::Settings();
            settings.deltaTime = 0.0f;

            settings.partSize = Settings::SNAKE_PART_SIZE;
            settings.moveSpeed = 0.8f;
            settings.screenWidth = 500;
            settings.screenHeight = 500;

            gameStateChangeType = GameState::GameStateChangeType::None;
            pendingGameStateType = GameState::GameStateType::None;
            pendingGameStateIsExclusivelyVisible = false;
            SwitchGameState(GameState::GameStateType::MainMenu);
        }


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

        // Add new game state on top of the stack
        void PushGameState(GameState::GameStateType stateType, bool isExclusivelyVisible);

        // Remove current game state from the stack
        void PopGameState();

        void InitGameState(GameState::GameState& state);
        void UpdateGameState(GameState::GameState& state);
        void DrawGameState(GameState::GameState& state, sf::RenderWindow& window);
        void DrawGame(sf::RenderWindow& window);
    };
}