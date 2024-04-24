#ifndef __MAIN_HPP
#define __MAIN_HPP

#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/flash.h"
#include "pico/stdlib.h"
#include "pico/time.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "pid.hpp"
#include "wire.hpp"
#include "constants.hpp"

extern uint pwm1Slice;
extern uint pwm1Channel;
extern uint pwm2Slice;
extern uint pwm2Channel;

extern long hallTicksLeft;
extern long oldHallTicksLeft;
extern long hallTicksRight;
extern long oldHallTicksRight;

extern double rpmLeft;
extern double pulseLeft;
extern double setRpmLeft;
extern double kpLeft;
extern double kiLeft;
extern double kdLeft;
extern PID pidLeft;

extern double rpmRight;
extern double pulseRight;
extern double setRpmRight;
extern double kpRight;
extern double kiRight;
extern double kdRight;
extern PID pidRight;

typedef struct
{
    uint8_t tmrComputeFlag : 1;
    uint8_t tmrLoggerFlag : 1;
    uint8_t stopFlag : 1;
    uint8_t runFlag : 1;
    uint8_t logFlag : 1;
} DC_Flags_t;

extern DC_Flags_t flags;
extern uint8_t tmrMeasureTimer;
extern uint8_t tmrLogTimer;

void initializeGPIO();
void initializePWM();
void initializeI2C();

void initializeSystem();
void timeBaseManager();
void computeSpeed();
void speedManager();
void usartLogger();

void leftDrive(int pulse);
void rightDrive(int pulse);

void serialize(DC_Configuration_e config, float value, uint8_t *buffer);
void deserialize(const uint8_t *buffer);

void gpioExtiCallback(uint gpio, uint32_t events);

#endif // __MAIN_HPP
