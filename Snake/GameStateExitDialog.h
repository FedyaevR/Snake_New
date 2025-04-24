#include <SFML/Graphics.hpp>
#include "Game.h"

namespace GameStateExitDialogData
{
    struct GameStateExitDialogData
    {
        sf::Font font;

        sf::RectangleShape background;
        sf::Text hintText;

        void InitGameStateExitDialog();
        void ShutdownGameStateExitDialog();
    };

    void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStateExitDialog(GameStateExitDialogData& data, float timeDelta);
    void DrawGameStateExitDialog(GameStateExitDialogData& data, sf::RenderWindow& window);
}