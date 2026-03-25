#include "mpu6050.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <cstdint>
#include <stdio.h>

mpu6050::mpu6050(int n) {
    char bus[11];
    snprintf(bus, sizeof(bus), "/dev/i2c-%d", n);
    fd = open(bus, O_RDWR);
    ioctl(fd, I2C_SLAVE, ADDR);
}

__u8 mpu6050::read_byte(__u8 payload) {

    __u8 response;

    struct i2c_msg msgs[2] = {
        {.addr = ADDR, .flags = 0, .len = 1, .buf = &payload},
        {.addr = ADDR, .flags = I2C_M_RD, .len = 1, .buf = &response }
    };

    struct i2c_rdwr_ioctl_data data = {
        .msgs = msgs, .nmsgs = 2
    };

    ioctl(fd, I2C_RDWR, &data);

    return response;
}

__u8 mpu6050::who_am_i(){
    return read_byte(0x75);
}
