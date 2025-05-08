#include "Serializer.h"

namespace Serializer
{
    bool Serializer::Serialize(const Core_Game::Game& game)
    {
        std::ofstream file(Settings::RECORD_TABLE_FILE_PATH);
        if (file.is_open())
        {
            for (const auto& record : game.recordsTable)
            {
                file << std::quoted(record.name) << " " << record.score << std::endl;
            }

            file.close();

            return true;
        }

        return false;
    }

    bool Serializer::Deserialize(Core_Game::Game& game)
    {
        std::ifstream file(Settings::RECORD_TABLE_FILE_PATH);
        if (!file.is_open())
        {
            return false;
        }

        game.recordsTable.clear();

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name;
            int score;

            if (iss >> std::quoted(name) >> score)
            {
                game.recordsTable.push_back({ name, score });
            }
        }

        return true;
    }
}