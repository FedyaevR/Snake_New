#pragma once

namespace GameState
{
    enum class GameStateType
    {
        None = 0,
        MainMenu,
        Playing,
        NameForRecord,
        GameOver,
        PauseDialog,
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

    enum class GameOptions : std::uint8_t
    {
        Easy = 1 << 0,
        HarderThanEasy = 1 << 1,
        Medium = 1 << 2,
        EasierThanHard = 1 << 3,
        Hard = 1 << 4,

        Default = HarderThanEasy,
        Empty = 0

    };
}