#ifndef __DC_CONSTANTS
#define __DC_CONSTANTS

// Input pins
#define HALL_A_LEFT         10
#define HALL_B_LEFT         11
#define HALL_A_RIGHT        12
#define HALL_B_RIGHT        13
// Output pins
#define OUT_DIR1            18
#define OUT_PWM1            19
#define OUT_DIR2            20
#define OUT_PWM2            21
// Communication pins
#define PICO_I2C_SDA        4
#define PICO_I2C_SCL        5

#define PWM_CLKDIV          12.2
#define PWM_TOP             1023

#define PICO_I2C            i2c0
#define PICO_I2C_ADDR       0x55
#define PICO_I2C_BAUDRATE   (100 * 1000)

#define LEFT_KD             0.03
#define LEFT_KI             3.8
#define LEFT_KP             1.9

#define RIGHT_KD            0.03
#define RIGHT_KI            3.8
#define RIGHT_KP            1.9

#define SAMPLE_TIME_us      10000

#define PULSE_PER_ROTATION  134.4
#define PERIOD_s            0.2
#define PERIOD_us           (PERIOD_s * 1000000)
#define WHEEL_DIAMETER      0.1

#define LEN_PER_PULSE       ((M_PI * WHEEL_DIAMETER) / PULSE_PER_ROTATION)
#define VEL_CONST           (LEN_PER_PULSE / PERIOD_s)
#define RPM_CONST           (60.0 / (PULSE_PER_ROTATION * PERIOD_s))

#define I2C_BUFFER_SIZE     8
#define TMR_PERIOD_ms       10
#define TMR_MEASURE_CNT     (PERIOD_s * 1000 / TMR_PERIOD_ms)
#define TMR_LOG_CNT         2

typedef enum
{
    Mode_START = 0x80,
    Mode_STOP
} DC_Mode_e;

typedef enum
{
    Configuration_LEFT_SPEED = 0x82,
    Configuration_RIGHT_SPEED,
    Configuration_LEFT_KP,
    Configuration_LEFT_KI,
    Configuration_LEFT_KD,
    Configuration_RIGHT_KP,
    Configuration_RIGHT_KI,
    Configuration_RIGHT_KD,
} DC_Configuration_e;

#endif // __DC_CONSTANTS
