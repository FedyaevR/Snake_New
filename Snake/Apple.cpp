#include "Apple.h"
#include "Snake.h"
#include <iostream>

namespace Apple
{
    void Apple::GenerateApplePosition(Settings::Settings settings, Snake::Snake& snake)
    {   
        auto ready = false;
        while (ready == false)
        {
            position.x = (float)(rand() % ((int)settings.screenWidth + 1));
            position.y = (float)(rand() % ((int)settings.screenHeight + 1));

            if (snake.CheckCollisions(*this))
            {
                continue;
            }

            ready = true;
        }

        UpdateSpritePosition();
    }

    void Apple::UpdateSpritePosition()
    {
        asset.sprite.setPosition(position.x, position.y);
    }

    void Apple::Draw(sf::RenderWindow& window)
    {
        window.draw(this->asset.sprite);
    }
}