#ifndef MPU6050_H
#define MPU6050_H
#include <linux/types.h>
#define ADDR 0x68

class mpu6050 {

    private:
        int fd;
    public:
       mpu6050(int bus); 
       __u8 read_byte(__u8 payload);
       __u8 who_am_i();
};  

#endif
