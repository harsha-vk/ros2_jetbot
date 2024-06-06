#include "main.hpp"
#include "string.h"

void loadData(DC_Configuration_e config, float value);

void serialize(DC_Configuration_e config, float value, uint8_t *buffer)
{
    buffer[0] = 0xFF;
    buffer[1] = 0xFE;
    buffer[2] = (uint8_t)config;

    memcpy(buffer + 3, &value, sizeof(value));

    uint8_t checkSum = 0;
    for (int i = 2; i < (I2C_BUFFER_SIZE - 1); i++)
    {
        checkSum += buffer[i];
    }
    buffer[I2C_BUFFER_SIZE - 1] = 255 - (checkSum % 256);
}

void deserialize(const uint8_t *buffer)
{
    float value;
    memcpy(&value, buffer + 3, sizeof(value));

    loadData((DC_Configuration_e)buffer[2], value);
}

void loadData(DC_Configuration_e config, float value)
{
    switch (config)
    {
    case Configuration_LEFT_SPEED:
        setRpmLeft = value * RPM_CONST / VEL_CONST;
        break;
    case Configuration_RIGHT_SPEED:
        setRpmRight = value * RPM_CONST / VEL_CONST;
        break;
    case Configuration_LEFT_KP:
        kpLeft = value;
        break;
    case Configuration_LEFT_KI:
        kiLeft = value;
        break;
    case Configuration_LEFT_KD:
        kdLeft = value;
        break;
    case Configuration_RIGHT_KP:
        kpRight = value;
        break;
    case Configuration_RIGHT_KI:
        kiRight = value;
        break;
    case Configuration_RIGHT_KD:
        kdRight = value;
        break;
    }
}
