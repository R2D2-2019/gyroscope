#include <hwlib.hpp>
#include <i2c_bus.hpp>

int main(void) {
    // kill the watchdog
    auto bus = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_1, 400000);

    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    uint8_t temp_high[1];
    uint8_t temp_low[1];

    //float gyroRes = 250.0f/32768.0f;

    for (;;){

        bus.read(0x68,temp_low,1,0x43,1); // GYRO_XOUT_H = 0x43,
        bus.read(0x68,temp_high,1,0x44,1); // GYRO_XOUT_L = 0x44,
        int16_t x = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];
        //int16_t x = static_cast<int16_t>(temp_high[0] << 8) | temp_low[0];
        //x = static_cast<int>(x * gyroRes);
        hwlib::cout << "x: " << x << "\n";

        bus.read(0x68,temp_low,1,0x45,1); // GYRO_XOUT_H = 0x45,
        bus.read(0x68,temp_high,1,0x46,1); // GYRO_XOUT_L = 0x46,
        int16_t y = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];
        //y = static_cast<int>(y * gyroRes);
        hwlib::cout << "y: " << y << "\n";

        bus.read(0x68,temp_low,1,0x47,1); // GYRO_XOUT_H = 0x47,
        bus.read(0x68,temp_high,1,0x48,1); // GYRO_XOUT_L = 0x48,
        int16_t z = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];
        //z = static_cast<int>(z * gyroRes);
        hwlib::cout << "z: " <<  z << "\n";

        hwlib::cout << "\n";



        hwlib::wait_ms(1000);
    }
}