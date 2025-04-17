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

        float speed = 1.0f;  // Уменьшаем скорость с 5 до 3
        float deltaTime;
        float accumulator = 0.0f; // Накопитель времени для контроля скорости движения
        float minTurnDistance = Settings::SNAKE_PART_SIZE * 0.9f; // Минимальное расстояние между поворотами
        bool alive = true; // Флаг, показывающий жива ли змейка
        Settings::Settings settings; // Добавляем настройки

        Snake() = default; // Конструктор по умолчанию
        void Initialize(Settings::Settings settings);
        void Update(float deltaTime); // Исправляем параметр
        void SetDirection(Snake_Direction::Direction newDirection);
        void UpdateSegmentsTexture(Views::SnakeBodyViews bodyAssets);
        void Draw(sf::RenderWindow& window);

        // Добавлю метод для добавления нового сегмента
        void AddSegment();
        
        // Метод для проверки столкновений
        bool CheckCollisions();
        
        // Метод для получения счета
        int GetScore() const { return segments.size() - 3; } // Первые 3 сегмента исходные
        
        // Метод для проверки, жива ли змейка
        bool IsAlive() const { return alive; }
        
        // Метод для получения текущего направления
        Snake_Direction::Direction GetDirection() const { return head ? head->direction : Snake_Direction::Direction::None; }

    private:
        int score = 0; // Счет игрока
        
        Snake_Segment::Segment InitSegment(sf::Texture texture, Math::Position position);
        void MoveHead(); // Исправляем сигнатуру
        void MoveBody();
        void SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection);
        bool IsAtTurnPoint(Math::Position segmentPosition, Math::Position turnPosition);
        float GetDistance(Math::Position p1, Math::Position p2);
        bool CanAddTurnPoint(const Math::Position& position);
    };
}