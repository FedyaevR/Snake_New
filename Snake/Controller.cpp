#include "Controller.h"
#include "GameStateMainMenu.h"
#include "SFML/Window/Keyboard.hpp"
#include "GameStateExitDialog.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"

namespace Core_Controller
{
    void Controller::MoveInput(Snake::Snake& snake, Apple::Apple& apple)
    {
        if (snake.IsAlive() == false)
        {
            return;
        }

        Snake_Direction::Direction currentDirection = snake.GetDirection();
        Snake_Direction::Direction newDirection = currentDirection;

        if (IsMoveUp(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Up;
        }
        else if (IsMoveDown(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Down;
        } 
        else if (IsMoveLeft(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Left;
        } 
        else if (IsMoveRight(currentDirection))
        {
            newDirection = Snake_Direction::Direction::Right;
        }
        
        // Устанавливаем новое направление только если оно изменилось
        if (newDirection != currentDirection)
        {
            snake.SetDirection(newDirection, apple);
        }
    }

    bool Controller::IsMoveUp(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Down)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            return true;
        }

        return false;
    }

    bool Controller::IsMoveDown(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Up)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            return true;
        }

        return false;
    }

    bool Controller::IsMoveLeft(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Right)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            return true;
        }

        return false;
    }

    bool Controller::IsMoveRight(Snake_Direction::Direction currentDirection)
    {
        if (currentDirection == Snake_Direction::Direction::Left)
        {
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            return true;
        }

        return false;
    }

    bool Controller::UpdateGame(float timeDelta)
    {
        if (gameStateChangeType == GameState::GameStateChangeType::Switch)
        {
            // Shutdown all game states
            while (gameStateStack.size() > 0)
            {
                //ShutdownGameState(game, game.gameStateStack.back());
                gameStateStack.pop_back();
            }
        }
        else if (gameStateChangeType == GameState::GameStateChangeType::Pop)
        {
            // Shutdown only current game state
            if (gameStateStack.size() > 0)
            {
                //ShutdownGameState(game, game.gameStateStack.back());
                gameStateStack.pop_back();
            }
        }

        // Initialize new game state if needed
        if (pendingGameStateType != GameState::GameStateType::None)
        {
            gameStateStack.push_back({ pendingGameStateType, nullptr, pendingGameStateIsExclusivelyVisible });
            InitGameState(gameStateStack.back());
        }

        gameStateChangeType = GameState::GameStateChangeType::None;
        pendingGameStateType = GameState::GameStateType::None;
        pendingGameStateIsExclusivelyVisible = false;

        if (gameStateStack.size() > 0)
        {
            UpdateGameState(gameStateStack.back(), timeDelta);

            return true;
        }

        return false;
    }

    void Controller::HandleWindowEvents(sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if close button or Escape key pressed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (gameStateStack.size() > 0)
            {
                HandleWindowEventGameState(event);
            }
        }
    }

    void Controller::HandleWindowEventGameState(sf::Event& event)
    {
        auto state = gameStateStack.back();

        switch (state.type)
        {
            case GameState::GameStateType::MainMenu:
            {
                GameStateMainMenuData::HandleGameStateMainMenuWindowEvent(*(GameStateMainMenuData::GameStateMainMenuData*)state.data, *this, event);

                break;
            }
            case GameState::GameStateType::Playing:
            {
                GameStatePlayingData::HandleGameStatePlayingWindowEvent(*(GameStatePlayingData::GameStatePlayingData*)state.data, *this, event);
                break;
            }
            case GameState::GameStateType::GameOver:
            {
                GameStateGameOverData::HandleGameStateGameOverWindowEvent(*(GameStateGameOverData::GameStateGameOverData*)state.data, *this, event);
                break;
            }
            case GameState::GameStateType::ExitDialog:
            {
                GameStateExitDialogData::HandleGameStateExitDialogWindowEvent(*(GameStateExitDialogData::GameStateExitDialogData*)state.data, *this, event);
                break;
            }
            default:
                assert(false); // На случай если забыли обработать какой-то игровой state 
                break;
        }
    }

    void Controller::SwitchGameState(GameState::GameStateType newState)
    {
        pendingGameStateType = newState;
        pendingGameStateIsExclusivelyVisible = false;
        gameStateChangeType = GameState::GameStateChangeType::Switch;
    }

    void Controller::PushGameState(GameState::GameStateType stateType, bool isExclusivelyVisible)
    {
        pendingGameStateType = stateType;
        pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
        gameStateChangeType = GameState::GameStateChangeType::Push;
    }

    void Controller::PopGameState()
    {
        pendingGameStateType = GameState::GameStateType::None;
        pendingGameStateIsExclusivelyVisible = false;
        gameStateChangeType = GameState::GameStateChangeType::Pop;
    }

    void Controller::InitGameState(GameState::GameState& state)
    {
        switch (state.type)
        {
        case GameState::GameStateType::MainMenu:
            {
                auto data = new GameStateMainMenuData::GameStateMainMenuData();
                data->InitGameStateMainMenu();
                state.data = data;

                break;
            }
        case GameState::GameStateType::Playing:
            {
                auto data = new GameStatePlayingData::GameStatePlayingData();
                data->InitGameStatePlaying();
                state.data = data;

                break;
            }
        case GameState::GameStateType::GameOver:
            {
                auto data = new GameStateGameOverData::GameStateGameOverData();
                data->InitGameStateGameOver();

                state.data = data;

                break;
            }
        case GameState::GameStateType::ExitDialog:
            {
                auto data = new GameStateExitDialogData::GameStateExitDialogData();
                data->InitGameStateExitDialog();
                state.data = data;

                break;
            }
            default:
                assert(false); 
                break;
        }
    }

    void Controller::UpdateGameState(GameState::GameState& state, float timeDelta)
    {
        switch (state.type)
        {
            case GameState::GameStateType::MainMenu:
            {
                UpdateGameStateMainMenu(*(GameStateMainMenuData::GameStateMainMenuData*)state.data, timeDelta);

                break;
            }
            case GameState::GameStateType::Playing:
            {
                UpdateGameStatePlaying(*(GameStatePlayingData::GameStatePlayingData*)state.data, timeDelta);

                break;
            }
            case GameState::GameStateType::GameOver:
            {
                UpdateGameStateGameOver(*(GameStateGameOverData::GameStateGameOverData*)state.data, timeDelta);

                break;
            }
            case GameState::GameStateType::ExitDialog:
            {
                UpdateGameStateExitDialog(*(GameStateExitDialogData::GameStateExitDialogData*)state.data, timeDelta);

                break;
            }
            default:
                assert(false); // We want to know if we forgot to implement new game statee
                break;
        }
    }

    void Controller::DrawGameState(GameState::GameState& state, sf::RenderWindow& window)
    {
        switch (state.type)
        {
        case GameState::GameStateType::MainMenu:
        {
            DrawGameStateMainMenu(*(GameStateMainMenuData::GameStateMainMenuData*)state.data, window);

            break;
        }
        case GameState::GameStateType::Playing:
        {
            DrawGameStatePlaying(*(GameStatePlayingData::GameStatePlayingData*)state.data, window);

            break;
        }
        case GameState::GameStateType::GameOver:
        {
            DrawGameStateGameOver(*(GameStateGameOverData::GameStateGameOverData*)state.data, window);

            break;
        }
        case GameState::GameStateType::ExitDialog:
        {
            DrawGameStateExitDialog(*(GameStateExitDialogData::GameStateExitDialogData*)state.data, window);

            break;
        }
        default:
            assert(false); // We want to know if we forgot to implement new game statee
            break;
        }
    }

    void Controller::DrawGame(sf::RenderWindow& window)
    {
        if (gameStateStack.size() > 0)
        {
            std::vector<GameState::GameState*> visibleGameStates;
            for (auto it = gameStateStack.rbegin(); it != gameStateStack.rend(); ++it)
            {
                visibleGameStates.push_back(&(*it));
                if (it->isExclusivelyVisible)
                {
                    break;
                }
            }

            for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
            {
                DrawGameState(**it, window);
            }
        }
    }
}
