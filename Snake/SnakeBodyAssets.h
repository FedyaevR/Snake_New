#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <string>
#include <cassert>
#include <iostream>

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
            if(up.loadFromFile(ASSETS_SNAKE_HEAD_UP))
            {
                std::cout << "Loaded ASSETS_SNAKE_HEAD_UP font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_HEAD_UP could not be loaded");
            }
            
            if(down.loadFromFile(ASSETS_SNAKE_HEAD_DOWN))
            {
                std::cout << "Loaded ASSETS_SNAKE_HEAD_DOWN font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_HEAD_DOWN could not be loaded");
            }
            
            if(left.loadFromFile(ASSETS_SNAKE_HEAD_LEFT))
            {
                std::cout << "Loaded ASSETS_SNAKE_HEAD_LEFT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_HEAD_LEFT could not be loaded");
            }
            
            if(right.loadFromFile(ASSETS_SNAKE_HEAD_RIGHT))
            {
                std::cout << "Loaded ASSETS_SNAKE_HEAD_RIGHT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_HEAD_RIGHT could not be loaded");
            }
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
            if(vertical.loadFromFile(ASSETS_SNAKE_BODY_VERTICAL))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_VERTICAL font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_VERTICAL could not be loaded");
            }
            
            if(horizontal.loadFromFile(ASSETS_SNAKE_BODY_HORIZONTAL))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_HORIZONTAL font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_HORIZONTAL could not be loaded");
            }
            
            if(topLeft.loadFromFile(ASSETS_SNAKE_BODY_TOPLEFT))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_TOPLEFT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_TOPLEFT could not be loaded");
            }
            
            if(topRight.loadFromFile(ASSETS_SNAKE_BODY_TOPRIGHT))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_TOPRIGHT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_TOPRIGHT could not be loaded");
            }
            
            if(bottomLeft.loadFromFile(ASSETS_SNAKE_BODY_BOTTOMLEFT))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_BOTTOMLEFT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_BOTTOMLEFT could not be loaded");
            }
            
            if(bottomRight.loadFromFile(ASSETS_SNAKE_BODY_BOTTOMRIGHT))
            {
                std::cout << "Loaded ASSETS_SNAKE_BODY_BOTTOMRIGHT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_BODY_BOTTOMRIGHT could not be loaded");
            }
            
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
            if(up.loadFromFile(ASSETS_SNAKE_TAIL_UP))
            {
                std::cout << "Loaded ASSETS_SNAKE_TAIL_UP font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_TAIL_UP could not be loaded");
            }
            
            if(down.loadFromFile(ASSETS_SNAKE_TAIL_DOWN))
            {
                std::cout << "Loaded ASSETS_SNAKE_TAIL_DOWN font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_TAIL_DOWN could not be loaded");
            }
            
            if(left.loadFromFile(ASSETS_SNAKE_TAIL_LEFT))
            {
                std::cout << "Loaded ASSETS_SNAKE_TAIL_LEFT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_TAIL_LEFT could not be loaded");
            }
            
            if(right.loadFromFile(ASSETS_SNAKE_TAIL_RIGHT))
            {
                std::cout << "Loaded ASSETS_SNAKE_TAIL_RIGHT font path is failed" << std::endl;

                throw std::invalid_argument("ASSETS_SNAKE_TAIL_RIGHT could not be loaded");
            }
            
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