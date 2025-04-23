#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "GameState.h"


namespace Core_Controller
{
    struct Controller
    {
        std::vector<GameState::GameState> gameStateStack;
        GameState::GameStateChangeType gameStateChangeType = GameState::GameStateChangeType::None;
        GameState::GameStateType pendingGameStateType = GameState::GameStateType::None;
        bool pendingGameStateIsExclusivelyVisible = false;

        void MoveInput(Snake::Snake& snake, Apple::Apple& apple);
        bool IsMoveUp(Snake_Direction::Direction currentDirection);
        bool IsMoveDown(Snake_Direction::Direction currentDirection);
        bool IsMoveLeft(Snake_Direction::Direction currentDirection);
        bool IsMoveRight(Snake_Direction::Direction currentDirection);

        bool UpdateGame(float timeDelta);

        void HandleWindowEvents(sf::RenderWindow& window);
        void HandleWindowEventGameState(sf::Event& event);

        void SwitchGameState(GameState::GameStateType newState);

        // Add new game state on top of the stack
        void PushGameState(GameState::GameStateType stateType, bool isExclusivelyVisible);

        // Remove current game state from the stack
        void PopGameState();

        void InitGameState(GameState::GameState& state);
        void UpdateGameState(GameState::GameState& state, float timeDelta);
        void DrawGameState(GameState::GameState& state, sf::RenderWindow& window);
        void DrawGame(sf::RenderWindow& window);
    };
}