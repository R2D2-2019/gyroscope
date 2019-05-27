//
// Created by Slimmerik on 27/05/2019.
//

#include <hwlib.hpp>
#include <i2c_bus.hpp>
#include <mpu9250_adress_map.hpp>

#pragma once

namespace r2d2::gyroscope {
    struct gyro_data_s {
        int16_t x;
        int16_t y;
        int16_t z;
    };
    struct accel_data_s {
        int16_t x;
        int16_t y;
        int16_t z;
    };
    struct magno_data_s {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    struct gyro_9_axis_data_s {
        int16_t gx;
        int16_t gy;
        int16_t gz;

        int16_t ax;
        int16_t ay;
        int16_t az;

        int16_t mx;
        int16_t my;
        int16_t mz;
    };


    class mpu9250_c{
    public:
        mpu9250_c(r2d2::i2c::i2c_bus_c &i2c_bus);

        gyro_data_s get_gyro_xyz();

        accel_data_s get_accel_xyz();

        magno_data_s get_Magno_xyz();

        gyro_data_s get_nine_axes();

    private:
        uint8_t AK8963ReadByte(uint8_t reg);

        void calibrate();

        /**
        * I2C bus from R2D2
        * */
        r2d2::i2c::i2c_bus_c &i2c_bus;
        gyro_data_s gyro_data;
    };
}