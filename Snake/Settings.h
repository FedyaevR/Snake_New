#pragma once
#include <string>

namespace Settings
{
    const std::string RESOURCES_PATH = "Resources/";
    const std::string ASSETS_PATH = RESOURCES_PATH + "Assets";
    const std::string SOUND_PATH = RESOURCES_PATH + "/Sound";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts";
    const std::string DEFAULT_FONT_PATH = FONTS_PATH + "/Roboto-Regular.ttf";

    const std::string RECORD_TABLE_FILE_PATH = "records.dat";

    const float SNAKE_PART_SIZE = 35.f;
    // Значение для плавности поворота
    const int SNAKE_TURNS_COUNTER_VALUE = 2;
    const int SNAKE_INIT_BODY_PART_COUNT = 3;
    const int SNAKE_PART_COUNT_AFTER_EATEN_APPLE = 1;
    const int SNAKE_INIT_SPEED = 0.5f;

    const int APPLE_INIT_COUNT = 3;
    const int APPLE_SIZE = 43.3f;

    const int TIME_FOR_DELAY_AFTER_PAUSE = 800;


    const int RECORDS_TABLE_POSITIONS_COUNT = 10;
    const int RECORDS_TABLE_POSITIONS_COUNT_POPUP = 5;

    const float SNAKE_SPEED_LVL_EASY = 1.f;
    const float SNAKE_SPEED_LVL_HARDERTHANEASY = 2.f;
    const float SNAKE_SPEED_LVL_MEDIUM = 3.f;
    const float SNAKE_SPEED_LVL_EASIERTHANHARD = 4.f;
    const float SNAKE_SPEED_LVL_HARD = 5.f;
    const float SNAKE_SPEED_LVL_DEFAULT = SNAKE_SPEED_LVL_EASY;

    const int SCORE_FOR_APPLE_LVL_EASY = 2;
    const int SCORE_FOR_APPLE_LVL_HARDERTHANEASY = 4;
    const int SCORE_FOR_APPLE_LVL_MEDIUM = 6;
    const int SCORE_FOR_APPLE_LVL_EASIERTHANHARD = 8;
    const int SCORE_FOR_APPLE_LVL_HARD =10;
    const int SCORE_FOR_APPLE_LVL_DEFAULT = SCORE_FOR_APPLE_LVL_EASY;

    const int SCORE_FOR_APPLE = SCORE_FOR_APPLE_LVL_EASY;

    struct Settings
    {
        float deltaTime;
        float partSize;
        float screenWidth;
        float screenHeight;
        float moveSpeed;
    };
}