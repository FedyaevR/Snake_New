#pragma once
#include <string>

namespace Settings
{
    const std::string RESOURCES_PATH = "Resources/";
    const std::string ASSETS_PATH = RESOURCES_PATH + "Assets";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts";
    const std::string DEFAULT_FONT_PATH = RESOURCES_PATH + FONTS_PATH + "/Roboto-Regular.ttf";

    const float SNAKE_PART_SIZE = 35.f;

    struct Settings
    {
        float deltaTime;
        float partSize;
        float screenWidth;
        float screenHeight;
        float moveSpeed;
    };
}