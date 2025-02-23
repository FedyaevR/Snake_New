#include "Math.h"

namespace Math
{
    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Position& relativePosition)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        return sf::Vector2f{ relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
    }

    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Position& desiredSize)//SNakeSize
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
        return spriteScale;
    }
}
