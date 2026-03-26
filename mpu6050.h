#ifndef MPU6050_H
#define MPU6050_H
#include <linux/types.h>
#define ADDR 0x68
#define EXT_SYNC_SET 0x38 //config
#define DLPF_CFG 0x08
#define AFS_SEL 0x18 //accel config
#define ZA_ST 0x20
#define YA_ST 0x40
#define XA_ST 0x80
#define FS_SEL 0x18 //gyro config

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
       __u16 accel_x();
       __u16 accel_y();
       __u16 accel_z();
       __u16 temp();
       __u8 ext_sens_data(__u8 n);
     
       void config(__u8 value);
       void accel_config(__u8 value);
       void gyro_config(__u8 value);
};  

#endif
