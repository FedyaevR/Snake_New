#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"


namespace Core_Controller
{
    void MoveInput(Snake::Snake& snake, Apple::Apple& apple);
    bool IsMoveUp(Snake_Direction::Direction currentDirection);
    bool IsMoveDown(Snake_Direction::Direction currentDirection);
    bool IsMoveLeft(Snake_Direction::Direction currentDirection);
    bool IsMoveRight(Snake_Direction::Direction currentDirection);
}