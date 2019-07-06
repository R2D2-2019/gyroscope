#include <mpu9250.hpp>


r2d2::gyroscope::mpu9250_c::mpu9250_c(r2d2::i2c::i2c_bus_c &i2c_bus,base_comm_c &comm) : i2c_bus(i2c_bus), gyroscope_c(comm){


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

float r2d2::gyroscope::mpu9250_c::get_mag_x_ut(){
    return _hx;
}

/* , uT */
float r2d2::gyroscope::mpu9250_c::get_mag_y_ut() {
  return _hy;
}

/* returns the magnetometer measurement in the z direction, uT */
float r2d2::gyroscope::mpu9250_c::get_mag_z_ut() {
  return _hz;
}

float r2d2::gyroscope::mpu9250_c::getMagBiasX_uT() {
  return _hxb;
}

float r2d2::gyroscope::mpu9250_c::getMagScaleFactorX() {
  return _hxs;
}

float r2d2::gyroscope::mpu9250_c::getMagBiasY_uT() {
  return _hyb;
}

float r2d2::gyroscope::mpu9250_c::getMagScaleFactorY() {
  return _hys;
}

float r2d2::gyroscope::mpu9250_c::getMagBiasZ_uT() {
  return _hzb;
}

float r2d2::gyroscope::mpu9250_c::getMagScaleFactorZ() {
  return _hzs;
}

void  r2d2::gyroscope::mpu9250_c::setMagCalX(float bias,float scaleFactor) {
  _hxb = bias;
  _hxs = scaleFactor;
}

void  r2d2::gyroscope::mpu9250_c::setMagCalY(float bias,float scaleFactor) {
  _hyb = bias;
  _hys = scaleFactor;
}

void  r2d2::gyroscope::mpu9250_c::setMagCalZ(float bias,float scaleFactor) {
  _hzb = bias;
  _hzs = scaleFactor;
}