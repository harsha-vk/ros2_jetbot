#ifndef __I2C_FIFO_HPP
#define __I2C_FIFO_HPP

#include "hardware/i2c.h"

static inline uint8_t i2c_read_byte(i2c_inst_t *i2c) {
    i2c_hw_t *hw = i2c_get_hw(i2c);
    assert(hw->status & I2C_IC_STATUS_RFNE_BITS);
    return (uint8_t)hw->data_cmd;
}

static inline void i2c_write_byte(i2c_inst_t *i2c, uint8_t value) {
    i2c_hw_t *hw = i2c_get_hw(i2c);
    assert(hw->status & I2C_IC_STATUS_TFNF_BITS);
    hw->data_cmd = value;
}

#endif // __I2C_FIFO_HPP
