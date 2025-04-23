#pragma once

namespace GameState
{
    enum class GameStateType
    {
        None = 0,
        MainMenu,
        Playing,
        GameOver,
        ExitDialog,
    };

    struct GameState
    {
        GameStateType type = GameStateType::None;
        void* data = nullptr;
        bool isExclusivelyVisible = false;
    };

    enum class GameStateChangeType
    {
        None,
        Push,
        Pop,
        Switch
    };
}