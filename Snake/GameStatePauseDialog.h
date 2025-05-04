#include <SFML/Graphics.hpp>
#include "Game.h"

namespace GameStatePauseDialogData
{
    struct GameStatePauseDialogData
    {
        sf::Font font;

        sf::RectangleShape background;
        sf::Text hintText;

        void InitGameStatePauseDialog();
        void ShutdownGameStatePauseDialog();
    };

    void HandleGameStatePauseDialogWindowEvent(GameStatePauseDialogData& data, Core_Game::Game& game, const sf::Event& event);
    void UpdateGameStatePauseDialog(GameStatePauseDialogData& data, float timeDelta);
    void DrawGameStatePauseDialog(GameStatePauseDialogData& data, sf::RenderWindow& window);
}