#include "mpu6050.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <cstdint>
#include <stdio.h>

void mpu6050::wake_up(){
    write_byte(0x6B, 0x00);
}

mpu6050::mpu6050(int n) {

    char bus[11];
    snprintf(bus, sizeof(bus), "/dev/i2c-%d", n);
    fd = open(bus, O_RDWR);
    ioctl(fd, I2C_SLAVE, ADDR);
    write_byte(0x6B, 0x00); //wakeup
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

void mpu6050::write_byte(__u8 reg, __u8 byte){

    __u8 msg[2] = {reg, byte};

    write(fd, msg, sizeof(msg));
}

__u16 mpu6050::read_word(__u8 regA, __u8 regB){

    __u16 word = read_byte(regA);
    word = word << 8 | read_byte(regB);

    return word;
}

__u8 mpu6050::who_am_i(){
    return read_byte(0x75);
}


__u16 mpu6050::gyro_x_raw(){
    return read_word(0x43, 0x44);   
}
__u16 mpu6050::gyro_y_raw(){
    return read_word(0x45, 0x46);   
}
__u16 mpu6050::gyro_z_raw(){
    return read_word(0x47, 0x48);   
}

float mpu6050::gyro_x(){
    return read_word(0x43, 0x44) / gyro_lsb;
}

float mpu6050::gyro_y(){
    return read_word(0x45, 0x46) / gyro_lsb;
}

float mpu6050::gyro_z(){
    return read_word(0x47, 0x48) / gyro_lsb;
}

__u16 mpu6050::accel_x_raw(){
    return read_word(0x3b, 0x3c);
}
__u16 mpu6050::accel_y_raw(){
    return read_word(0x3d, 0x3e);
}
__u16 mpu6050::accel_z_raw(){
    return read_word(0x3f, 0x40);
}

float mpu6050::accel_x(){
    return read_word(0x3b, 0x3c) / accl_lsb;
}

float mpu6050::accel_y(){
    return read_word(0x3d, 0x3e) / accl_lsb;
}

float mpu6050::accel_z(){
    return read_word(0x3f, 0x40) / accl_lsb;
}

float mpu6050::temp(){
    return (read_word(0x41, 0x42) / 340.0f) + 36.53f;
}

__u8 mpu6050::ext_sens_data(__u8 n){
    return read_byte(0x49 + n);
}

void mpu6050::accel_config_afs_sel(int n) {
    
    __u8 conf = read_byte(0x1C);

    //preserve XA_ST, YA_ST, ZA_ST bits
    conf = conf & 0xE0;

    switch(n) {
        case 0: 
            write_byte(0x1C, conf);
            accl_lsb = 16384.0f;
        case 1:
            write_byte(0x1C, conf | 0x08);
            accl_lsb = 8192.0f;
        case 2:
            write_byte(0x1C, conf | 0x10);
            accl_lsb = 4096.0f;
        case 3:
            write_byte(0x1C, conf | 0x18);
            accl_lsb = 2048.0f;
        default:
            perror("max value is 3 - input is %d, n");
    }
}

void mpu6050::gyro_config_fs_sel(int n){

    __u8 conf = 0x00;

    switch(n) {
        case 0: 
            write_byte(0x1C, conf);
            gyro_lsb = 131.0f;
        case 1:
            write_byte(0x1C, conf | 0x08);
            gyro_lsb = 65.5f;
        case 2:
            write_byte(0x1C, conf | 0x10);
            gyro_lsb = 32.8f;
        case 3:
            write_byte(0x1C, conf | 0x18);
            gyro_lsb = 16.4f;
        default:
            perror("max value is 3 - input is %d, n");
    }
}
