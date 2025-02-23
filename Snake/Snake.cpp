#include "Snake.h"
#include "Math.h"

namespace Snake
{
    void Snake::Initialize(Settings::Settings settings)
    {
        deltaTime = settings.deltaTime;

        auto head = InitSegment(bodyAssets.head.up, {500 / 2, 500 / 2}); // Заменить потом на настройки высоты и ширина экрана
        head.isHead = true;

        segments.push_back(head);

        this->head = &segments[0];

        Update(head.direction);
    }

    Snake_Segment::Segment Snake::InitSegment(sf::Texture texture, Math::Position position)
    {
        auto segment = Snake_Segment::Segment();

        segment.texture = texture;

        segment.SetPosition(position);
        segment.direction = Snake_Direction::Direction::Up;

        segment.sprite.setTexture(segment.texture);
        segment.sprite.setOrigin(Math::GetItemOrigin(segment.sprite, { 0.5f, 0.5f }));
        segment.sprite.setScale(Math::GetSpriteScale(segment.sprite, { Settings::SNAKE_PART_SIZE, Settings::SNAKE_PART_SIZE }));

        return segment;
    }


    void Snake::Update(Snake_Direction::Direction setDirection)
    {
        MoveHead(setDirection);
    }

    void Snake::MoveHead(Snake_Direction::Direction setDirection)
    {
        SegmentStep(*head, setDirection);
    }

    void Snake::SegmentStep(Snake_Segment::Segment& segment, Snake_Direction::Direction setDirection)
    {
        float distance = std::min(speed * deltaTime, Settings::SNAKE_PART_SIZE / 2.f);

        segment.SetTurnFlag(setDirection);

        switch (setDirection)
        {
            case Snake_Direction::Direction::Up:
                segment.position.y -= distance;

                break;
            case Snake_Direction::Direction::Down:
                segment.position.y += distance;

                break;
            case Snake_Direction::Direction::Left:
                segment.position.x -= distance;

                break;
            case Snake_Direction::Direction::Right:
                segment.position.x += distance;

                break;
        }

        UpdateSegmentsTexture(setDirection, bodyAssets);
        segment.UpdateSpritePosition();

        segment.direction = setDirection;
    }

    void Snake::UpdateSegmentsTexture(Snake_Direction::Direction setDirection, Views::SnakeBodyViews bodyAssets)
    {
        for (auto& segment : segments)
        {
            segment.SetTexture(setDirection, bodyAssets);
        }
    }

    void Snake::Draw(sf::RenderWindow& window)
    {
        for(auto& segment : segments)
        {
            window.draw(segment.sprite);
        }
    }
}
