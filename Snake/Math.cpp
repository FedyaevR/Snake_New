#include "Math.h"

namespace Math
{
    void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
    {
        sf::FloatRect totalRect;
        // Calculate total height/width of all texts
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            sf::FloatRect itemRect = (*it)->getGlobalBounds();

            if (orientation == Orientation::Horizontal)
            {
                totalRect.width += itemRect.width + (it != items.end() - 1 ? spacing : 0.f);
                totalRect.height = std::max(totalRect.height, itemRect.height);
            }
            else
            {
                totalRect.width = std::max(totalRect.width, itemRect.width);
                totalRect.height += itemRect.height + (it != items.end() - 1 ? spacing : 0.f);
            }
        }

        totalRect.left = position.x - origin.x * totalRect.width;
        totalRect.top = position.y - origin.y * totalRect.height;
        sf::Vector2f currentPos = { totalRect.left, totalRect.top };

        for (auto it = items.begin(); it != items.end(); ++it)
        {
            sf::FloatRect itemRect = (*it)->getGlobalBounds();
            sf::Vector2f itemOrigin;

            if (orientation == Orientation::Horizontal)
            {
                itemOrigin.y = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                itemOrigin.x = 0.f;
                currentPos.y = totalRect.top + itemOrigin.y * totalRect.height;
            }
            else
            {
                itemOrigin.y = 0.f;
                itemOrigin.x = alignment == Alignment::Min ? 0.f : alignment == Alignment::Middle ? 0.5f : 1.f;
                currentPos.x = totalRect.left + itemOrigin.x * totalRect.width;
            }

            (*it)->setOrigin(GetItemOrigin(**it, itemOrigin));
            (*it)->setPosition(currentPos);
            window.draw(**it);

            if (orientation == Orientation::Horizontal)
            {
                currentPos.x += itemRect.width + spacing;
            }
            else
            {
                currentPos.y += itemRect.height + spacing;
            }


        }
    }

    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Position& relativePosition)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        return sf::Vector2f{ relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
    }

    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Position& desiredSize)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
        return spriteScale;
    }

    sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        return
        {
            (textSize.left + textSize.width) * relativePosition.x,
            (textSize.top + textSize.height) * relativePosition.y,
        };
    }
}
