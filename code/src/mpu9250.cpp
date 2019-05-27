//
// Created by Slimmerik on 27/05/2019.
//
#include <mpu9250.hpp>


r2d2::gyroscope::mpu9250_c::mpu9250_c(r2d2::i2c::i2c_bus_c &i2c_bus) : i2c_bus(i2c_bus){


}




uint8_t r2d2::gyroscope::mpu9250_c::AK8963ReadByte(uint8_t reg)
{
    uint8_t akass =  (uint8_t)mpu9250_adress_map::AK8963_ADDRESS ;
    uint8_t readd =  (uint8_t)mpu9250_adress_map::READ_FLAG;

    uint8_t data[1] = {0x81};
    uint8_t regdata[1] = {reg};
    uint8_t akrefl[1] = {(uint8_t)(akass | readd)};
    uint8_t response[1];
    i2c_bus.write(0x68, akrefl,1,(int)mpu9250_adress_map::I2C_SLV0_ADDR, 1); //Set the I2C slave addres of AK8963 and set for read.
    i2c_bus.write(0x68, regdata,1 ,(int)mpu9250_adress_map::I2C_SLV0_REG, 1); //I2C slave 0 register address from where to begin data transfer
    i2c_bus.write(0x68, data,1, (int)mpu9250_adress_map::I2C_SLV0_CTRL, 1); //Read 1 byte from the magnetometer

    i2c_bus.read(0x68,response,1,(uint8_t)mpu9250_adress_map::EXT_SENS_DATA_00,1); //Read I2C



    return response[0];
}

r2d2::gyroscope::gyro_data_s r2d2::gyroscope::mpu9250_c::get_gyro_xyz(){
    uint8_t temp_high[1];
    uint8_t temp_low[1];
    gyro_data_s temp = gyro_data_s();

    i2c_bus.read(0x68,temp_low,1,0x44,1); // GYRO_XOUT_L = 0x44,
    i2c_bus.read(0x68,temp_high,1,0x43,1); // GYRO_XOUT_H = 0x43,
    temp.x = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    i2c_bus.read(0x68,temp_low,1,0x46,1);  // GYRO_XOUT_L = 0x46
    i2c_bus.read(0x68,temp_high,1,0x45,1); // GYRO_XOUT_H = 0x45,
    temp.y = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    i2c_bus.read(0x68,temp_low,1,0x48,1); // GYRO_XOUT_L = 0x48,
    i2c_bus.read(0x68,temp_high,1,0x47,1); // GYRO_XOUT_H = 0x47
    temp.z = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    return temp;
}


r2d2::gyroscope::accel_data_s r2d2::gyroscope::mpu9250_c::get_accel_xyz(){
    uint8_t temp_high[1];
    uint8_t temp_low[1];
    accel_data_s temp = accel_data_s();

    i2c_bus.read(0x68,temp_low,1,0x3C,1); // ACCEL_XOUT_L = 0x3C,
    i2c_bus.read(0x68,temp_high,1,0x3B,1); // ACCEL_XOUT_H = 0x3B,
    temp.x = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    i2c_bus.read(0x68,temp_low,1,0x3E,1);  // ACCEL_YOUT_L = 0x3E,
    i2c_bus.read(0x68,temp_high,1,0x3D,1); // ACCEL_YOUT_H = 0x3D,
    temp.y = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    i2c_bus.read(0x68,temp_low,1,0x40,1); //  ACCEL_ZOUT_L = 0x40,
    i2c_bus.read(0x68,temp_high,1,0x3F,1); // ACCEL_ZOUT_H = 0x3F,
    temp.z = (int16_t)(temp_high[0] << 8) | (int16_t)temp_low[0];

    return temp;
}

r2d2::gyroscope::magno_data_s r2d2::gyroscope::mpu9250_c::get_Magno_xyz() {
    magno_data_s temp = magno_data_s();
    temp.x = (int16_t)(r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_XOUT_H) << 8) |
            (int16_t)r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_XOUT_L);

    temp.y = (int16_t)(r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_YOUT_H) << 8) |
              (int16_t)r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_YOUT_L);

    temp.z = (int16_t)(r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_ZOUT_H) << 8) |
              (int16_t)r2d2::gyroscope::mpu9250_c::AK8963ReadByte((uint8_t)mpu9250_adress_map::AK8963_ZOUT_L);


    return temp;
}