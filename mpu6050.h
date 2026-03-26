#ifndef MPU6050_H
#define MPU6050_H
#include <linux/types.h>
#define ADDR 0x68

class mpu6050 {

    private:
        int fd;

    public:
       mpu6050(int bus); 
       __u8 read_byte(__u8 reg); //read from reg
       int write_byte(__u8 reg, __u8 byte); //write value to reg
       __u16 read_word(__u8 regA, __u8 regB);

       __u8 who_am_i();
       void wake_up();
       __u16 gyro_x();
       __u16 gyro_y();
       __u16 gyro_z();
};  

#endif
