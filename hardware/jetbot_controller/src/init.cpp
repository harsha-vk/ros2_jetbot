#include "main.hpp"

uint pwm1Slice;
uint pwm1Channel;
uint pwm2Slice;
uint pwm2Channel;

uint8_t tmrMeasureTimer;
uint8_t tmrLogTimer;

void initializeGPIO()
{
    gpio_init(HALL_B_LEFT);
    gpio_set_dir(HALL_B_LEFT, GPIO_IN);
    gpio_pull_down(HALL_B_LEFT);

    gpio_init(HALL_B_RIGHT);
    gpio_set_dir(HALL_B_RIGHT, GPIO_IN);
    gpio_pull_down(HALL_B_RIGHT);

    gpio_init(OUT_DIR1);
    gpio_set_dir(OUT_DIR1, GPIO_OUT);

    gpio_init(OUT_DIR2);
    gpio_set_dir(OUT_DIR2, GPIO_OUT);

    gpio_set_irq_enabled_with_callback(HALL_A_LEFT, GPIO_IRQ_EDGE_RISE, true, &gpioExtiCallback);
    gpio_pull_down(HALL_A_LEFT);

    gpio_set_irq_enabled_with_callback(HALL_A_RIGHT, GPIO_IRQ_EDGE_RISE, true, &gpioExtiCallback);
    gpio_pull_down(HALL_A_RIGHT);
}

void initializePWM()
{
    pwm1Slice = pwm_gpio_to_slice_num(OUT_PWM1);
    pwm1Channel = pwm_gpio_to_channel(OUT_PWM1);
    pwm2Slice = pwm_gpio_to_slice_num(OUT_PWM2);
    pwm1Channel = pwm_gpio_to_channel(OUT_PWM2);

    gpio_set_function(OUT_PWM1, GPIO_FUNC_PWM);
    pwm_set_clkdiv(pwm1Slice, PWM_CLKDIV);
    pwm_set_wrap(pwm1Slice, PWM_TOP);
    pwm_set_chan_level(pwm1Slice, pwm1Channel, 0);
    pwm_set_enabled(pwm1Slice, true);

    gpio_set_function(OUT_PWM2, GPIO_FUNC_PWM);
    pwm_set_clkdiv(pwm2Slice, PWM_CLKDIV);
    pwm_set_wrap(pwm2Slice, PWM_TOP);
    pwm_set_chan_level(pwm2Slice, pwm2Channel, 0);
    pwm_set_enabled(pwm2Slice, true);
}

void initializeI2C()
{
    gpio_set_function(PICO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_I2C_SDA);
    gpio_pull_up(PICO_I2C_SCL);
    i2c_init(PICO_I2C, PICO_I2C_BAUDRATE);
}

void initializeSystem()
{
    pwm_set_chan_level(pwm1Slice, pwm1Channel, 0);
    gpio_put(OUT_DIR1, false);
    pwm_set_chan_level(pwm2Slice, pwm2Channel, 0);
    gpio_put(OUT_DIR2, false);

    pidLeft = PID(&rpmLeft, &pulseLeft, &setRpmLeft, kpLeft, kiLeft, kdLeft, DIRECT);
    pidLeft.SetMode(AUTOMATIC);
    pidLeft.SetSampleTime(SAMPLE_TIME_ms);
    pidLeft.SetOutputLimits(((-1) * PWM_TOP), PWM_TOP);

    pidRight = PID(&rpmRight, &pulseRight, &setRpmRight, kpRight, kiRight, kdRight, DIRECT);
    pidRight.SetMode(AUTOMATIC);
    pidRight.SetSampleTime(SAMPLE_TIME_ms);
    pidRight.SetOutputLimits(((-1) * PWM_TOP), PWM_TOP);

    tmrMeasureTimer = TMR_MEASURE_CNT;
    tmrLogTimer = TMR_LOG_CNT;
    flags.logFlag = 1;

    flags.stopFlag = 0;
}
