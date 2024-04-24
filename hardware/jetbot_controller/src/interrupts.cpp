#include "main.hpp"

void gpioExtiCallback(uint gpio, uint32_t events)
{
    if (HALL_A_LEFT == gpio && GPIO_IRQ_EDGE_RISE == events)
    {
        if (gpio_get(HALL_B_LEFT))
            hallTicksLeft++;
        else
            hallTicksLeft--;
    }
    else if (gpio == HALL_A_RIGHT && events == GPIO_IRQ_EDGE_RISE)
    {
        if (gpio_get(HALL_B_RIGHT))
            hallTicksRight--;
        else
            hallTicksRight++;
    }
}
