#pragma once
#include <string>
#include "Settings.h"
#include <cassert>
#include <SFML/Graphics.hpp>

namespace Views
{
    const std::string ASSETS_APPLE = Settings::ASSETS_PATH + "/apple.png";

    struct AppleAsset
    {
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;

        AppleAsset() : texture(std::make_shared<sf::Texture>())
        {
            assert(texture->loadFromFile(ASSETS_APPLE));

            sprite.setTexture(*texture);
            sprite.setOrigin(Math::GetItemOrigin(sprite, { 0.5f, 0.5f }));
            sprite.setScale(Math::GetSpriteScale(sprite, { Settings::APPLE_SIZE, Settings::APPLE_SIZE }));
        }
    };
}