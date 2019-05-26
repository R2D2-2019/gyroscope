#include <hwlib.hpp>

#include <i2c_bus.hpp>

int main(void) {
  // kill the watchdog
    auto bus = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_1, 50000);

    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    uint8_t raw_data[1];

    for (;;){

        bus.read(0x68,raw_data,1,0x73,1);

        hwlib::cout << raw_data;

        hwlib::cout << "this works via arduino";
        hwlib::wait_ms(1000);
    }
}