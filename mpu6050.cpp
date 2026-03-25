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

__u8 mpu6050::read_byte(__u8 reg) {

    __u8 response;

    struct i2c_msg msgs[2] = {
        {.addr = ADDR, .flags = 0, .len = 1, .buf = &reg},
        {.addr = ADDR, .flags = I2C_M_RD, .len = 1, .buf = &response }
    };

    struct i2c_rdwr_ioctl_data data = {
        .msgs = msgs, .nmsgs = 2
    };

    ioctl(fd, I2C_RDWR, &data);

    return response;
}


__u16 mpu6050::read_word(__u8 regA, __u8 regB){

    __u16 word = read_byte(regA);
    word = word << 8 | read_byte(regB);

    return word;
}

__u8 mpu6050::who_am_i(){
    return read_byte(0x75);
}
