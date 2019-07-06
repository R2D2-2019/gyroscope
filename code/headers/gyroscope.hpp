#pragma once
#include <base_module.hpp>
#include <hwlib.hpp>

namespace r2d2::gyroscope {

    /**
     * Class gyroscope_c is an abstract class that can be implemented for
     * the mpu sensor. 
     * this class exists to process the data from the mpu9250. 
     */
    class gyroscope_c: public base_module_c{
        public:
        gyroscope_c(base_com_c & comm);
        /**
         * @brief
         * This function will process the frames from the canbus.
         * Only reads from the canbus.
         */
        void process() override;

        /**
         * get the gyroscoop x, y and z axis values;
         */
        virtual void get_gyro_xyz() = 0;

        /**
         * get the acceleration values of the x, y and z axis
         */
        virtual void get_accel_xyz() = 0;

                /**
         * return the magnetometer measurement in the x direction 
         */
        virtual float getMag_X_uT() = 0;
        /**
         * return the magnetometer measurement in the y direction
         */
        virtual float getMag_Y_uT() = 0;
        /**
         * return the magnetometer measurement in the z direction
         */
        virtual float getMag_Z_uT() = 0;

        /**
         * finds bias and scale factor calibration for the magnetometer,
         * the sensor should be rotated in a figure 8 motion until complete
         */
        virtual int calibrate_Mag() = 0;

        /**
         * return the magnetometer bias in the X direction
         */
        virtual float get_MagBias_X_uT() = 0;

        /**
         * return the magnetometer scale factor in the X direction
         */
        virtual float get_MagScaleFactor_X() = 0;

        /**
         * return the magnetometer bias in the Y direction
         */
        virtual float get_MagBias_Y_uT() = 0;

        /**
         * return the magnetometer scale factor in the Y direction
         */
        virtual float get_MagScaleFactor_Y() = 0;

        /**
         * return the magnetometer bias in the Z direction
         */
        virtual float get_MagBias_Z_uT() = 0;

        /**
         * return the magnetometer scale factor in the Z direction
         */
        virtual float get_MagScaleFactor_Z() = 0;

        /**
         * set the magnetometer bias (uT) and scale factor in the X direction
         */
        virtual void set_MagCal_X(float bias,float scaleFactor) = 0;

        /**
         * set the magnetometer bias (uT) and scale factor in the Y direction 
         */
        virtual void set_MagCal_Y(float bias,float scaleFactor) = 0;

        /**
         * set the magnetometer bias (uT) and scale factor in the Z direction
         */
        virtual void set_MagCal_Z(float bias,float scaleFactor) = 0;
    };

} // namespace r2d2::gyroscope