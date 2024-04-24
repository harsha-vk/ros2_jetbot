# JetBot Controller

The Jetbot controller uses PID controller to regulate the DC motors and determines speed by utilizing encoders attached to the motors.

## Hardware

- 1 Raspberry Pi Pico
- 2 Planetary Gear DC Motor(12V, 370RPM, Gear Ratio 19.2:1) with Encoder(7 counts per revolution)
- 1 Dual Channel DC Motor Driver

## References

- https://github.com/br3ttb/Arduino-PID-Library.git
- https://github.com/vmilea/pico_i2c_slave.git
