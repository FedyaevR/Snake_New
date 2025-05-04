#pragma once
#include <SFML/Graphics.hpp>

namespace Math
{
    struct Position
    {
        float x;
        float y;
    };

	// Helper method for organizing text items
	enum class Orientation
	{
		Horizontal,
		Vertical
	};

	enum class Alignment
	{
		Min, // Left or Top
		Middle,
		Max // Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

    sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Position& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Position& desiredSize);
}