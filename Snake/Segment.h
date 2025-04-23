#pragma once
#include "Math.h"
#include "SnakeBodyAssets.h"
#include "Direction.h"
#include "Apple.h"

namespace Snake_Segment
{
    struct Segment
    {
        Math::Position position;
        Math::Position previousPosition;
        float targetDistance = 35.0f;

        sf::Texture texture;
        sf::Sprite sprite;
        
        Snake_Direction::Direction direction;
        Snake_Direction::Direction previousDirection;

        std::shared_ptr<Segment> previousSegment;

        bool isTail = false;
        bool isHead = false;
        bool isTurn = false;

        void SetPosition(Math::Position setPosition);
        void SetTurnFlag(Snake_Direction::Direction setDirection);
        void SetTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets);
        void UpdateSpritePosition();
        void FollowPreviousSegment();
        bool CheckCollision(std::shared_ptr<Segment> other);
        bool CheckCollision(const Apple::Apple& apple);
        float CalculateDistance(const Math::Position& pos1, const Math::Position& pos2);
    };
}