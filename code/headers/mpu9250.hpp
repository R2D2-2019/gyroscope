#pragma once
#include <base_module.hpp>
#include <hwlib.hpp>
#include <i2c_bus.hpp>
#include <gyroscope.hpp>
#include <mpu9250_adress_map.hpp>

#pragma once

namespace r2d2::gyroscope {
    /**
     * This struct holds the gyro data on z y and z axis
     */
    struct gyro_data_s {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    /**
     * This struct holds the acceldata on x y and z axis.
     */
    struct accel_data_s {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    /**
     * Class mpu9250_c is used to get the accel gyro and magneto values from the
     * mpu9250
     * comm: the interal communication bus.
     */
    class mpu9250_c {
    public:
        /**
         * This is the constructor of mpu9250_c
         *
         * @param i2c_bus i2c bus is used to interact with the sensor.
         */
        mpu9250_c(r2d2::i2c::i2c_bus_c &i2c_bus, base_comm_c &comm);

        /**
         * This function gets the gyro values of the mpu9250 these values
         * represent the rotation since last pull.
         *
         * @return gyro_data_s
         */
        gyro_data_s get_gyro_xyz();

        /**
         * This function gets the acceleration data from the mpu9250 this is the
         * current force on the chip.
         *
         *
         * @return accel_data_s
         */
        accel_data_s get_accel_xyz();

    private:
        /**
         * I2C bus from R2D2
         * */
        r2d2::i2c::i2c_bus_c &i2c_bus;
        gyro_data_s gyro_data;
    };
} // namespace r2d2::gyroscope