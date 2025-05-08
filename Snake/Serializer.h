#pragma once
#include "Game.h"
#include <fstream>
#include <iomanip>
#include <sstream>

namespace Serializer
{
    struct Serializer
    {
        bool Serialize(const Core_Game::Game& game);
        bool Deserialize(Core_Game::Game& game);
    };
}