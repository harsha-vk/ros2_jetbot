#include "main.hpp"

void computeSpeed()
{
    if (!flags.tmrComputeFlag)
    {
        return;
    }
    flags.tmrComputeFlag = 0;
    if (--tmrMeasureTimer == 0)
    {
        tmrMeasureTimer = TMR_MEASURE_CNT;
        int tickDiffLeft = hallTicksLeft - oldHallTicksLeft;
        int tickDiffRight = hallTicksRight - oldHallTicksRight;
        rpmLeft = RPM_CONST * ((float)tickDiffLeft);
        rpmRight = RPM_CONST * ((float)tickDiffRight);
        oldHallTicksLeft = hallTicksLeft;
        oldHallTicksRight = hallTicksRight;
    }
}

void speedManager()
{
    if (flags.runFlag)
    {
        if (pidLeft.Compute())
        {
            leftDrive((int)pulseLeft);
        }
        if (pidRight.Compute())
        {
            rightDrive((int)pulseRight);
        }
    }
}

void leftDrive(int pulse)
{
    if (pulse > 0)
    {
        pwm_set_chan_level(pwm1Slice, pwm1Channel, (uint16_t)pulse);
        gpio_put(OUT_DIR1, true);
    }
    else
    {
        pwm_set_chan_level(pwm1Slice, pwm1Channel, (uint16_t)abs(pulse));
        gpio_put(OUT_DIR1, false);
    }
}

void rightDrive(int pulse)
{
    if (pulse > 0)
    {
        pwm_set_chan_level(pwm2Slice, pwm2Channel, (uint16_t)pulse);
        gpio_put(OUT_DIR2, false);
    }
    else
    {
        pwm_set_chan_level(pwm2Slice, pwm2Channel, (uint16_t)abs(pulse));
        gpio_put(OUT_DIR2, true);
    }
}
