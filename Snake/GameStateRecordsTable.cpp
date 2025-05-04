#include "GameStateRecordsTable.h"
#include "Settings.h"
#include "Math.h"
#include <cassert>

namespace GameStateNameForRecordsTable
{
    void GameStateNameForRecordsTable::InitGameStatePlaying()
    {
        assert(font.loadFromFile(Settings::DEFAULT_FONT_PATH));

        inputNameMenuItem.text.setString("Input name");
        inputNameMenuItem.text.setFont(font);
        inputNameMenuItem.text.setCharacterSize(24);
        inputNameMenuItem.hintText.setString("Input name");
        inputNameMenuItem.hintText.setFont(font);
        inputNameMenuItem.hintText.setCharacterSize(48);
        inputNameMenuItem.hintText.setFillColor(sf::Color::White);


    }
}
