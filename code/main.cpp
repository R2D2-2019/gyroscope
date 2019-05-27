#include <hwlib.hpp>
#include <i2c_bus.hpp>
#include <mpu9250.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);


    auto bus = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_1, 400000);

    r2d2::gyroscope::mpu9250_c gyro(bus);

    for (;;) {

        r2d2::gyroscope::gyro_data_s gyro_data = gyro.get_gyro_xyz();
        hwlib::cout << "gx: "<< gyro_data.x << "\n" << "gy: "<< gyro_data.y << "\n"<< "gz: "<< gyro_data.z<< "\n\n";

        r2d2::gyroscope::accel_data_s accel_data = gyro.get_accel_xyz();
        hwlib::cout << "ax: "<< accel_data.x << "\n" << "ay: "<< accel_data.y << "\n"<< "az: "<< accel_data.z<< "\n\n";

        r2d2::gyroscope::magno_data_s magno_data = gyro.get_Magno_xyz();
        hwlib::cout << "mx: "<< magno_data.x << "\n" << "my: "<< magno_data.y << "\n"<< "mz: "<< magno_data.z<< "\n\n";

        hwlib::wait_ms(1000);
    }
}