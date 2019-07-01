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
    };

} // namespace r2d2::gyroscope