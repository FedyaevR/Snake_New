#pragma once
#include <string>

namespace Settings
{
    const std::string RESOURCES_PATH = "Resources/";
    const std::string ASSETS_PATH = RESOURCES_PATH + "Assets";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts";
    const std::string DEFAULT_FONT_PATH = FONTS_PATH + "/Roboto-Regular.ttf";

    const float SNAKE_PART_SIZE = 35.f;
    // Значение для плавности поворота
    const int SNAKE_TURNS_COUNTER_VALUE = 2;
    const int SNAKE_INIT_BODY_PART_COUNT = 3;
    const int SNAKE_PART_COUNT_AFTER_EATEN_APPLE = 1;
    const int SNAKE_INIT_SPEED = 0.5f;

    const int APPLE_INIT_COUNT = 3;
    const int APPLE_SIZE = 43.3f;

    const int TIME_FOR_DELAY_AFTER_PAUSE = 800;

    const int SCORE_FOR_APPLE = 2;

    const int RECORDS_TABLE_POSITIONS_COUNT = 10;
    const int RECORDS_TABLE_POSITIONS_COUNT_POPUP = 5;

    struct Settings
    {
        float deltaTime;
        float partSize;
        float screenWidth;
        float screenHeight;
        float moveSpeed;
    };
}