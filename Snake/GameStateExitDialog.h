#include <SFML/Graphics.hpp>
#include "Controller.h"

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

    void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Core_Controller::Controller& controller, const sf::Event& event);
    void UpdateGameStateExitDialog(GameStateExitDialogData& data, float timeDelta);
    void DrawGameStateExitDialog(GameStateExitDialogData& data, sf::RenderWindow& window);
}