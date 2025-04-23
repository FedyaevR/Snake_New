#pragma once
#include "Apple.h"
#include "Math.h"
#include "Segment.h"
#include "Settings.h"
#include "SnakeBodyAssets.h"
#include <deque>
#include <vector>

namespace Snake
{
    struct Turn
    {
        Math::Position position;
        Snake_Direction::Direction direction;
    };

    struct Snake
    {
        std::vector<std::shared_ptr<Snake_Segment::Segment>> segments;
        std::deque<Turn> turnPositions;
        std::shared_ptr <Snake_Segment::Segment> head = nullptr;

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
        ~Snake() 
        {
            segments.clear(); 
        }

        void Initialize(Settings::Settings settings);
        void Update(float deltaTime, Apple::Apple& apple);
        void SetDirection(Snake_Direction::Direction newDirection, Apple::Apple& apple);
        void UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets);
        void Draw(sf::RenderWindow& window);

        void AddSegment();
        bool CheckCollisions();
        bool CheckCollisions(const Apple::Apple& apple, bool checkOnlyHead = false);
        bool IsAlive() const { return alive; }
        Snake_Direction::Direction GetDirection() const { return head ? head->direction : Snake_Direction::Direction::None; }
        
        //int GetScore() const { return segments.size() - 3; } 

    private:
        int score = 0; // Счет игрока
        
        void InitSegment(bool isHead = false, bool isTail = false, Snake_Direction::Direction setDirection = Snake_Direction::Direction::Up);
        std::shared_ptr<Snake_Segment::Segment> InitSegment(sf::Texture texture, Math::Position position);
        void InitSegment(Math::Position position, Snake_Direction::Direction setDirection);
        void MoveHead();
        void MoveBody();
        void MoveSegments(static std::vector<std::vector<bool>>& processedTurns, static std::vector<int>& turnCounters);
        void MoveSnake(Apple::Apple& apple);
        void SegmentStep(std::shared_ptr < Snake_Segment::Segment> segment, Snake_Direction::Direction setDirection);
        bool IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition);
        float GetDistance(Math::Position p1, Math::Position p2);
        bool CanAddTurnPoint(const Math::Position& position);
    };
}