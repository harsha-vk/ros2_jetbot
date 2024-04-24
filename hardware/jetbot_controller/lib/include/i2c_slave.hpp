#ifndef __I2C_SLAVE_HPP
#define __I2C_SLAVE_HPP

#include "hardware/i2c.h"

typedef enum i2c_slave_event_t
{
    I2C_SLAVE_RECEIVE,
    I2C_SLAVE_REQUEST,
    I2C_SLAVE_FINISH,
} i2c_slave_event_t;

typedef void (*i2c_slave_handler_t)(i2c_inst_t *i2c, i2c_slave_event_t event);

void i2c_slave_init(i2c_inst_t *i2c, uint8_t address, i2c_slave_handler_t handler);

void i2c_slave_deinit(i2c_inst_t *i2c);

#endif // __I2C_SLAVE_HPP
