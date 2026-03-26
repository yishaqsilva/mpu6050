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

int mpu6050::write_byte(__u8 reg, __u8 byte){

    __u8 msg[2] = {reg, byte};

    return write(fd, msg, sizeof(msg));
}

__u16 mpu6050::read_word(__u8 regA, __u8 regB){

    __u16 word = read_byte(regA);
    word = word << 8 | read_byte(regB);

    return word;
}

__u8 mpu6050::who_am_i(){
    return read_byte(0x75);
}

void mpu6050::wake_up(){
    write_byte(0x6B, 0x00);
}

__u16 mpu6050::gyro_x(){
    return read_word(0x43, 0x44);   
}
__u16 mpu6050::gyro_y(){
    return read_word(0x45, 0x46);   
}
__u16 mpu6050::gyro_z(){
    return read_word(0x47, 0x48);   
}

__u16 mpu6050::accel_x(){
    return read_word(0x3b, 0x3c);
}
__u16 mpu6050::accel_y(){
    return read_word(0x3d, 0x3e);
}
__u16 mpu6050::accel_z(){
    return read_word(0x3f, 0x40);
}

__u16 mpu6050::temp(){
    return read_word(0x41, 0x42);
}

__u8 mpu6050::ext_sens_data(__u8 n){
    return read_byte(0x49 + n);
}

void mpu6050::config(__u8 value){
    write_byte(0x1A, 0x00);
    write_byte(0x1A, value);
}

void mpu6050::accel_config(__u8 value){
    write_byte(0x1C, 0x00);
    write_byte(0x1C, value);
}
void mpu6050::gyro_config(__u8 value){
    write_byte(0x1B, 0x00);
    write_byte(0x1B, value);
}
