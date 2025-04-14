#pragma once
#include "Math.h"
#include "SnakeBodyAssets.h"
#include "Direction.h"

namespace Snake_Segment
{
    struct Segment
    {
        Math::Position position;

        sf::Texture texture;
        sf::Sprite sprite;
        
        Snake_Direction::Direction direction;
        Snake_Direction::Direction previousDirection;

        Segment* previousSegment;

        bool isTail = false;
        bool isHead = false;
        bool isTurn = false;

        void SetPosition(Math::Position setPosition);
        void SetTurnFlag(Snake_Direction::Direction setDirection);
        void SetTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets);
        void UpdateSpritePosition();
    };
}