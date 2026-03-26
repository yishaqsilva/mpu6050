#ifndef MPU6050_H
#define MPU6050_H
#include <linux/types.h>
#define ADDR 0x68
#define ZA_ST 0x20
#define YA_ST 0x40
#define XA_ST 0x80

class mpu6050 {

    private:
        int fd;
        float accl_lsb = 16384.0f;
        float gyro_lsb = 131.0f;

    public:
       mpu6050(int bus); 
       __u8 read_byte(__u8 reg); //read from reg
        void write_byte(__u8 reg, __u8 byte); //write value to reg
       __u16 read_word(__u8 regA, __u8 regB);

       __u8 who_am_i();
       inline void wake_up();

       __u16 gyro_x_raw();
       __u16 gyro_y_raw();
       __u16 gyro_z_raw();

       float gyro_x();
       float gyro_y();
       float gyro_z();

       __u16 accel_x_raw();
       __u16 accel_y_raw();
       __u16 accel_z_raw();

       float accel_x();
       float accel_y();
       float accel_z();
       float temp();

       __u8 ext_sens_data(__u8 n);
     
       void accel_config_afs_sel(int n);
       void gyro_config_fs_sel(int n);
};  

#endif
