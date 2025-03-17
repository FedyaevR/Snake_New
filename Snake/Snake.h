#pragma once
#include <vector>
#include "SnakeBodyAssets.h"
#include "Segment.h"
#include <deque>
#include "Math.h"

namespace Snake
{
    struct Turn
    {
        Math::Position position;
        Snake_Direction::Direction direction;
    };

    struct Snake
    {
        std::vector<Snake_Segment::Segment> segments;
        std::deque<Turn> turnPositions;
        Snake_Segment::Segment* head = nullptr;

        Views::SnakeBodyViews bodyAssets;

        float speed = 100.f;
        float deltaTime;

        void Initialize(Settings::Settings settings);
        void Update(Snake_Direction::Direction setDirection);
        void UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets);
        void Draw(sf::RenderWindow& window);

    private:
        Snake_Segment::Segment InitSegment(sf::Texture texture, Math::Position position);

        void MoveHead(Snake_Direction::Direction setDirection);

        void MoveBody();

        void SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection);

        bool IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition);

        //void UpdateSegmentsTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets);
    };
}