#include "Game.h"
#include "GameStateMainMenu.h"
#include "SFML/Window/Keyboard.hpp"
#include "GameStatePauseDialog.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateNameForRecordsTable.h"

namespace Core_Game
{
    void Game::MoveInput()
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
            snake.SetDirection(newDirection, *this);
        }
    }

    bool Game::IsMoveUp(Snake_Direction::Direction currentDirection)
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

    bool Game::IsMoveDown(Snake_Direction::Direction currentDirection)
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

    bool Game::IsMoveLeft(Snake_Direction::Direction currentDirection)
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

    bool Game::IsMoveRight(Snake_Direction::Direction currentDirection)
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

    void Game::SetSettingsWithDifficultyLevel()
    {
        snake.speed = Settings::SNAKE_SPEED_LVL_EASY;

        if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::Easy)
        {
            snake.speed = Settings::SNAKE_SPEED_LVL_EASY;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_EASY;
        }
        else if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::HarderThanEasy)
        {
            snake.speed *= Settings::SNAKE_SPEED_LVL_HARDERTHANEASY;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_HARDERTHANEASY;
        }
        else if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::Medium)
        {
            snake.speed *= Settings::SNAKE_SPEED_LVL_MEDIUM;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_MEDIUM;
        }
        else if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::EasierThanHard)
        {
            snake.speed *= Settings::SNAKE_SPEED_LVL_EASIERTHANHARD;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_EASIERTHANHARD;
        }
        else if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::Hard)
        {
            snake.speed *= Settings::SNAKE_SPEED_LVL_HARD;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_HARD;
        }
        else if ((std::uint8_t)options & (std::uint8_t)GameState::GameOptions::Default)
        {
            snake.speed = Settings::SNAKE_SPEED_LVL_DEFAULT;
            scoreForApple = Settings::SCORE_FOR_APPLE_LVL_DEFAULT;
        }
    }

    bool Game::UpdateGame()
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
            UpdateGameState(gameStateStack.back());

            return true;
        }

        return false;
    }

    void Game::HandleWindowEvents(sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
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

    void Game::HandleWindowEventGameState(sf::Event& event)
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
            case GameState::GameStateType::NameForRecord:
            {
                GameStateNameForRecordsTable::HandleGameStateNameForRecordWindowEvent(*(GameStateNameForRecordsTable::GameStateNameForRecordsTable*)state.data, *this, event);

                break;
            }
            case GameState::GameStateType::GameOver:
            {
                GameStateGameOverData::HandleGameStateGameOverWindowEvent(*(GameStateGameOverData::GameStateGameOverData*)state.data, *this, event);

                break;
            }
            case GameState::GameStateType::PauseDialog:
            {
                GameStatePauseDialogData::HandleGameStatePauseDialogWindowEvent(*(GameStatePauseDialogData::GameStatePauseDialogData*)state.data, *this, event);

                break;
            }
            default:
                assert(false); // На случай если забыли обработать какой-то игровой state 
                break;
        }
    }

    void Game::SwitchGameState(GameState::GameStateType newState)
    {
        pendingGameStateType = newState;
        pendingGameStateIsExclusivelyVisible = false;
        gameStateChangeType = GameState::GameStateChangeType::Switch;
    }

    void Game::RestartGame()
    {
        snake = Snake::Snake();
        apple = Apple::Apple();

        settings = Settings::Settings();
        settings.deltaTime = 0.0f;
        settings.screenWidth = screenWidth;
        settings.screenHeight = screenHeight;
        settings.partSize = Settings::SNAKE_PART_SIZE;
        settings.moveSpeed = 0.8f;

        score = 0;

        snake.Initialize(settings);
        apple.GenerateApplePosition(settings, snake);
        isStart = true;
        wasPause = false;

        SetSettingsWithDifficultyLevel();
    }

    void Game::PushGameState(GameState::GameStateType stateType, bool isExclusivelyVisible)
    {
        pendingGameStateType = stateType;
        pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
        gameStateChangeType = GameState::GameStateChangeType::Push;
    }

    void Game::PopGameState()
    {
        pendingGameStateType = GameState::GameStateType::None;
        pendingGameStateIsExclusivelyVisible = false;
        gameStateChangeType = GameState::GameStateChangeType::Pop;
    }

    void Game::InitGameState(GameState::GameState& state)
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
            case GameState::GameStateType::NameForRecord:
            {
                auto data = new GameStateNameForRecordsTable::GameStateNameForRecordsTable();
                data->InitGameStateNameForRecords();
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
            case GameState::GameStateType::PauseDialog:
            {
                auto data = new GameStatePauseDialogData::GameStatePauseDialogData();
                data->InitGameStatePauseDialog();
                state.data = data;

                break;
            }
            default:
                assert(false); 
                break;
        }
    }

    void Game::UpdateGameState(GameState::GameState& state)
    {
        switch (state.type)
        {
            case GameState::GameStateType::MainMenu:
            {
                UpdateGameStateMainMenu(*(GameStateMainMenuData::GameStateMainMenuData*)state.data, deltaTime);

                break;
            }
            case GameState::GameStateType::Playing:
            {
                UpdateGameStatePlaying(*(GameStatePlayingData::GameStatePlayingData*)state.data, *this);

                break;
            }
            case GameState::GameStateType::NameForRecord:
            {
                UpdateGameStateNameForRecord(*(GameStateNameForRecordsTable::GameStateNameForRecordsTable*)state.data, deltaTime, *this);

                break;
            }
            case GameState::GameStateType::GameOver:
            {
                UpdateGameStateGameOver(*(GameStateGameOverData::GameStateGameOverData*)state.data, *this, deltaTime);

                break;
            }
            case GameState::GameStateType::PauseDialog:
            {
                UpdateGameStatePauseDialog(*(GameStatePauseDialogData::GameStatePauseDialogData*)state.data, deltaTime);

                break;
            }
            default:
                assert(false); // We want to know if we forgot to implement new game statee
                break;
        }
    }

    void Game::DrawGameState(GameState::GameState& state, sf::RenderWindow& window)
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
            DrawGameStatePlaying(*(GameStatePlayingData::GameStatePlayingData*)state.data, *this, window);

            break;
        }
        case GameState::GameStateType::NameForRecord:
        {
            DrawGameStateNameForRecord(*(GameStateNameForRecordsTable::GameStateNameForRecordsTable*)state.data, window);

            break;
        }
        case GameState::GameStateType::GameOver:
        {
            DrawGameStateGameOver(*(GameStateGameOverData::GameStateGameOverData*)state.data, window);

            break;
        }
        case GameState::GameStateType::PauseDialog:
        {
            DrawGameStatePauseDialog(*(GameStatePauseDialogData::GameStatePauseDialogData*)state.data, window);

            break;
        }
        default:
            assert(false); 
            break;
        }
    }

    void Game::DrawGame(sf::RenderWindow& window)
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

    std::string Game::GetSettingInString(std::string settingName)
    {
        if (settingName.compare("music") == 0)
        {
            return (GetInString(music));
        }
        else if (settingName.compare("sound") == 0)
        {
            return (GetInString(sound));
        }
    }

    std::string Game::GetInString(bool value)
    {
        if (value)
        {
            return "On";
        }

        return "Off";
    }

    void Game::InitRecordTable()
    {
        Deserialize();
        recordsTable.push_back({userName, 0, true});

        SortRecordTable();
    }

    void Game::SortRecordTable()
    {
        std::sort(recordsTable.begin(), recordsTable.end(),
            [](const RecordsTableItem& a, const RecordsTableItem& b)
            {
                return a.score > b.score;
            }
        );
    }

    bool Game::Serialize()
    {
        std::ofstream file(Settings::RECORD_TABLE_FILE_PATH);
        if (file.is_open())
        {
            for (const auto& record : recordsTable)
            {
                file << std::quoted(record.name) << " " << record.score << std::endl;
            }

            file.close();

            return true;
        }

        return false;
    }

    bool Game::Deserialize()
    {
        std::ifstream file(Settings::RECORD_TABLE_FILE_PATH);
        if (!file.is_open())
        {
            return false;
        }

        recordsTable.clear();

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name;
            int score;

            if (iss >> std::quoted(name) >> score)
            {
                recordsTable.push_back({ name, score });
            }
        }

        return true;
    }

    void Game::InitSound()
    {
        assert(appleSoundBuffer.loadFromFile(Settings::SOUND_PATH + "/Theevilsocks__menu-hover.wav"));
        appleSound.setBuffer(appleSoundBuffer);

        assert(hitSoundBuffer.loadFromFile(Settings::SOUND_PATH + "/Owlstorm__Snake_hit.wav"));
        hitSound.setBuffer(hitSoundBuffer);

        assert(loseSoundBuffer.loadFromFile(Settings::SOUND_PATH + "/Maodin204__Lose.wav"));
        loseSound.setBuffer(loseSoundBuffer);

        assert(backgroundMusic.openFromFile(Settings::SOUND_PATH + "/Clinthammer__Background_Music.wav"));

        backgroundMusic.setLoop(true);
        backgroundMusic.play();
    }

    void Game::InitScreenSize()
    {
        settings.screenHeight = screenHeight;
        settings.screenWidth = screenWidth;
    }
}
