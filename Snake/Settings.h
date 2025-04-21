#pragma once
#include <string>

namespace Settings
{
    const std::string RESOURCES_PATH = "Resources/";
    const std::string ASSETS_PATH = RESOURCES_PATH + "Assets";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts";
    const std::string DEFAULT_FONT_PATH = RESOURCES_PATH + FONTS_PATH + "/Roboto-Regular.ttf";

    const float SNAKE_PART_SIZE = 35.f;

    // Значение для плавности поворота
    const int SNAKE_TURNS_COUNTER_VALUE = 2;

    const int SNAKE_INIT_BODY_PART_COUNT = 3;

    struct Settings
    {
        float deltaTime;
        float partSize;
        float screenWidth;
        float screenHeight;
        float moveSpeed;
    };
}