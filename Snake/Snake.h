#pragma once
#include <vector>
#include "SnakeBodyAssets.h"
#include "Segment.h"
#include <deque>
#include "Math.h"
#include "Settings.h"

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

        float speed = 0.5f; 
        float deltaTime;
        float accumulator = 0.0f; // Накопитель времени для контроля скорости движения
        float minTurnDistance = Settings::SNAKE_PART_SIZE * 0.9f; // Минимальное расстояние между поворотами
        bool alive = true;
        Settings::Settings settings;
        
        // Флаг для отслеживания поворота. Пока не применяется
        bool pendingDirectionChange = false;
        Snake_Direction::Direction pendingDirection = Snake_Direction::Direction::None;

        Snake() = default;
        void Initialize(Settings::Settings settings);
        void Update(float deltaTime);
        void SetDirection(Snake_Direction::Direction newDirection);
        void UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets);
        void Draw(sf::RenderWindow& window);

        void AddSegment();
        bool CheckCollisions();
        bool IsAlive() const { return alive; }
        Snake_Direction::Direction GetDirection() const { return head ? head->direction : Snake_Direction::Direction::None; }
        
        //int GetScore() const { return segments.size() - 3; } 

    private:
        int score = 0; // Счет игрока
        
        void InitSegment(bool isHead = false, bool isTail = false, Snake_Direction::Direction setDirection = Snake_Direction::Direction::Up);
        Snake_Segment::Segment InitSegment(sf::Texture texture, Math::Position position);
        void MoveHead(); 
        void MoveBody();
        void MoveSegments(static std::vector<std::vector<bool>>& processedTurns, static std::vector<int>& turnCounters);
        void MoveSnake();
        void SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection);
        bool IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition);
        float GetDistance(Math::Position p1, Math::Position p2);
        bool CanAddTurnPoint(const Math::Position& position);
    };
}