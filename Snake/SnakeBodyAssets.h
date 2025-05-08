#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <string>
#include <cassert>
#include "Settings.h"

namespace Views
{
    //Head
    const std::string ASSETS_SNAKE_HEAD_UP = Settings::ASSETS_PATH + "/head_up.png";
    const std::string ASSETS_SNAKE_HEAD_DOWN = Settings::ASSETS_PATH + "/head_down.png";
    const std::string ASSETS_SNAKE_HEAD_LEFT = Settings::ASSETS_PATH + "/head_left.png";
    const std::string ASSETS_SNAKE_HEAD_RIGHT = Settings::ASSETS_PATH + "/head_right.png";

    //Body
    const std::string ASSETS_SNAKE_BODY_VERTICAL = Settings::ASSETS_PATH + "/body_vertical.png";
    const std::string ASSETS_SNAKE_BODY_HORIZONTAL = Settings::ASSETS_PATH + "/body_horizontal.png";
    const std::string ASSETS_SNAKE_BODY_TOPLEFT = Settings::ASSETS_PATH + "/body_topleft.png";
    const std::string ASSETS_SNAKE_BODY_TOPRIGHT = Settings::ASSETS_PATH + "/body_topright.png";
    const std::string ASSETS_SNAKE_BODY_BOTTOMLEFT = Settings::ASSETS_PATH + "/body_bottomleft.png";
    const std::string ASSETS_SNAKE_BODY_BOTTOMRIGHT = Settings::ASSETS_PATH + "/body_bottomright.png";

    const std::string ASSETS_SNAKE_TAIL_UP = Settings::ASSETS_PATH + "/tail_up.png";
    const std::string ASSETS_SNAKE_TAIL_DOWN = Settings::ASSETS_PATH + "/tail_down.png";
    const std::string ASSETS_SNAKE_TAIL_LEFT = Settings::ASSETS_PATH + "/tail_left.png";
    const std::string ASSETS_SNAKE_TAIL_RIGHT = Settings::ASSETS_PATH + "/tail_right.png";

    struct Head
    {
        sf::Texture up;
        sf::Texture down;
        sf::Texture left;
        sf::Texture right;

        Head()
        {
            assert(up.loadFromFile(ASSETS_SNAKE_HEAD_UP));
            assert(down.loadFromFile(ASSETS_SNAKE_HEAD_DOWN));
            assert(left.loadFromFile(ASSETS_SNAKE_HEAD_LEFT));
            assert(right.loadFromFile(ASSETS_SNAKE_HEAD_RIGHT));
        }
    };

    struct Body
    {
        sf::Texture vertical;
        sf::Texture horizontal;
        sf::Texture topLeft;
        sf::Texture topRight;
        sf::Texture bottomLeft;
        sf::Texture bottomRight;

        Body()
        {
            assert(vertical.loadFromFile(ASSETS_SNAKE_BODY_VERTICAL));
            assert(horizontal.loadFromFile(ASSETS_SNAKE_BODY_HORIZONTAL));
            assert(topLeft.loadFromFile(ASSETS_SNAKE_BODY_TOPLEFT));
            assert(topRight.loadFromFile(ASSETS_SNAKE_BODY_TOPRIGHT));
            assert(bottomLeft.loadFromFile(ASSETS_SNAKE_BODY_BOTTOMLEFT));
            assert(bottomRight.loadFromFile(ASSETS_SNAKE_BODY_BOTTOMRIGHT));
        }
    };

    struct Tail
    {
        sf::Texture up;
        sf::Texture down;
        sf::Texture left;
        sf::Texture right;

        Tail()
        {
            assert(up.loadFromFile(ASSETS_SNAKE_TAIL_UP));
            assert(down.loadFromFile(ASSETS_SNAKE_TAIL_DOWN));
            assert(left.loadFromFile(ASSETS_SNAKE_TAIL_LEFT));
            assert(right.loadFromFile(ASSETS_SNAKE_TAIL_RIGHT));
        }
    };

    struct SnakeBodyViews
    {
        Head head;
        Body body;
        Tail tail;

        SnakeBodyViews()
        {
            head = Head();
            body = Body();
            tail = Tail();
        }

        sf::Texture GetBodyTexture(Snake_Direction::Direction previousDirection, Snake_Direction::Direction setDirection);

    private:
        sf::Texture GetStandartBodyTexture(Snake_Direction::Direction direction);
    };
}