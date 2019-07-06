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

        /**
         * return the magnetometer measurement in the x direction 
         */
        float getMag_X_uT();
        /**
         * return the magnetometer measurement in the y direction
         */
        float getMag_Y_uT();
        /**
         * return the magnetometer measurement in the z direction
         */
        float getMag_Z_uT();

        /**
         * finds bias and scale factor calibration for the magnetometer,
         * the sensor should be rotated in a figure 8 motion until complete
         */
        int calibrate_Mag();

        /**
         * return the magnetometer bias in the X direction
         */
        float get_MagBias_X_uT();

        /**
         * return the magnetometer scale factor in the X direction
         */
        float get_MagScaleFactor_X();

        /**
         * return the magnetometer bias in the Y direction
         */
        float get_MagBias_Y_uT();

        /**
         * return the magnetometer scale factor in the Y direction
         */
        float get_MagScaleFactor_Y();

        /**
         * return the magnetometer bias in the Z direction
         */
        float get_MagBias_Z_uT();

        /**
         * return the magnetometer scale factor in the Z direction
         */
        float get_MagScaleFactor_Z();

        /**
         * set the magnetometer bias (uT) and scale factor in the X direction
         */
        void set_MagCal_X(float bias,float scaleFactor);

        /**
         * set the magnetometer bias (uT) and scale factor in the Y direction 
         */
        void set_MagCal_Y(float bias,float scaleFactor);

        /**
         * set the magnetometer bias (uT) and scale factor in the Z direction
         */
        void set_MagCal_Z(float bias,float scaleFactor);

    protected:
        float _magScaleX, _magScaleY, _magScaleZ;
            // magnetometer bias and scale factor estimation
        uint16_t _maxCounts = 1000;
        float _deltaThresh = 0.3f;
        uint8_t _coeff = 8;
        uint16_t _counter;
        float _framedelta, _delta;
        float _hxfilt, _hyfilt, _hzfilt;
        float _hxmax, _hymax, _hzmax;
        float _hxmin, _hymin, _hzmin;
        float _hxb, _hyb, _hzb;
        float _hxs = 1.0f;
        float _hys = 1.0f;
        float _hzs = 1.0f;
        float _avgs;
        // transformation matrix
        /* transform the accel and gyro axes to match the magnetometer axes */
        const int16_t tX[3] = {0,  1,  0}; 
        const int16_t tY[3] = {1,  0,  0};
        const int16_t tZ[3] = {0,  0, -1};
        // constants
        const float G = 9.807f;
        const float _d2r = 3.14159265359f/180.0f;

    private:
        /**
         * I2C bus from R2D2
         * */
        r2d2::i2c::i2c_bus_c &i2c_bus;
        gyro_data_s gyro_data;
    };
} // namespace r2d2::gyroscope