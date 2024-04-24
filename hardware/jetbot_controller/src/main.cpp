#include "main.hpp"

long hallTicksLeft;
long oldHallTicksLeft;
long hallTicksRight;
long oldHallTicksRight;

double rpmLeft;
double pulseLeft;
double setRpmLeft;
double kpLeft;
double kiLeft;
double kdLeft;
PID pidLeft(&rpmLeft, &pulseLeft, &setRpmLeft, 0, 0, 0, DIRECT);
double rpmRight;
double pulseRight;
double setRpmRight;
double kpRight;
double kiRight;
double kdRight;
PID pidRight(&rpmLeft, &pulseLeft, &setRpmLeft, 0, 0, 0, DIRECT);

DC_Flags_t flags;

uint32_t oldMicros;

static void requestEvent();
static void receiveEvent(int count);

int main()
{
    stdio_init_all();

    initializeGPIO();
    initializePWM();
    initializeI2C();

    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
    Wire.begin(PICO_I2C_ADDR);

    while (true)
    {
        if (flags.stopFlag)
        {
            initializeSystem();
        }
        computeSpeed();
        speedManager();
        usartLogger();
        sleep_ms(5);
    }
    return 0;
}

static void requestEvent()
{
    float tempVal;
    
    uint8_t temp0[I2C_BUFFER_SIZE] = {0};
    tempVal = rpmLeft * VEL_CONST / RPM_CONST;
    serialize(Configuration_LEFT_SPEED, tempVal, temp0);
    Wire.write(temp0, I2C_BUFFER_SIZE);

    uint8_t temp1[I2C_BUFFER_SIZE] = {0};
    tempVal = rpmRight * VEL_CONST / RPM_CONST;
    serialize(Configuration_RIGHT_SPEED, tempVal, temp1);
    Wire.write(temp1, I2C_BUFFER_SIZE);
}

static void receiveEvent(int count)
{
    hard_assert(Wire.available());
    uint8_t tempBuffer[I2C_BUFFER_SIZE];
    while (Wire.available())
    {
        tempBuffer[0] = (uint8_t)Wire.read();
        if (tempBuffer[0] != 0xFF)
        {
            continue;
        }
        tempBuffer[1] = (uint8_t)Wire.read();
        if (tempBuffer[1] != 0xFE)
        {
            continue;
        }
        if (Wire.available() < (I2C_BUFFER_SIZE - 2))
        {
            if (Wire.available() == 1)
            {
                switch (Wire.read())
                {
                case Mode_START:
                    flags.stopFlag = 1;
                    flags.runFlag = 1;
                    break;
                case Mode_STOP:
                    flags.stopFlag = 1;
                    flags.runFlag = 0;
                    break;
                default:
                    break;
                }
            }
            continue;
        }
        uint8_t checkSum = 0;
        for (int i = 2; i < I2C_BUFFER_SIZE; i++)
        {
            tempBuffer[i] = (uint8_t)Wire.read();
            checkSum += tempBuffer[i];
        }
        if ((checkSum % 256) != 255)
        {
            checkSum = 0;
            continue;
        }
        deserialize(tempBuffer);
    }
}

void timeBaseManager()
{
    if ((time_us_32() - oldMicros) >= TMR_PERIOD_ms)
    {
        oldMicros = time_us_32();
        flags.tmrComputeFlag = 1;
        flags.tmrLoggerFlag = 1;
    }
}

void usartLogger()
{
    if (!flags.logFlag)
    {
        return;
    }
    if (!flags.tmrLoggerFlag)
    {
        return;
    }
    flags.tmrLoggerFlag = 0;
    if (--tmrLogTimer)
    {
        tmrLogTimer = TMR_LOG_CNT;
        printf("l_rpm:%.2f,l_setRpm:%.2f,l_kp:%.2f,l_ki:%.2f,l_kd:%.2f", rpmLeft, setRpmLeft, kpLeft, kiLeft, kdLeft);
        printf("r_rpm:%.2f,r_setRpm:%.2f,r_kp:%.2f,r_ki:%.2f,r_kd:%.2f", rpmRight, setRpmRight, kpRight, kiRight, kdRight);
        printf("\n");
    }
}
