#include "../src/MPU6050.h"

#define ACC_X_BIAS 919.48f
#define ACC_Y_BIAS -437.80f
#define ACC_Z_BIAS 3838.37f
#define GYRO_X_BIAS -344.23f
#define GYRO_Y_BIAS -31.68f
#define GYRO_Z_BIAS -105.15f

#define CALIBRATE

#define MPU6050_ADDRESS 0x68 // Original device address when ADO = 0, change to your own address

MPU6050 mpu6050;
float ahrs_roll, ahrs_pitch, ahrs_yaw = 0.f;
float gyroX, gyroY, gyroZ = 0.f;

int main()
{
    // If using in an Arduino environment this part of the code should be in setup()
    Wire.begin();
    Serial.begin(9600);
    while (!Serial)
        ;

    if (!mpu6050.setup(MPU6050_ADDRESS))
    {
        Serial.println("No MPU found! Check connection");
        for (;;)
            ;
    }

#if defined(CALIBRATE)
    // To display calibration bias values set verbose to true
    mpu6050.verbose(false);
    mpu6050.calibrateAccelGyro();
#else
    mpu6050.setAccBias(ACC_X_BIAS, ACC_Y_BIAS, ACC_Z_BIAS);
    mpu6050.setGyroBias(GYRO_X_BIAS, GYRO_Y_BIAS, GYRO_Z_BIAS);
#endif

    // This part of the code should be in loop()
    for (;;)
    {
        // If we have data from MPU6050, use it
        if (mpu6050.update())
        {
            ahrs_roll = mpu6050.getRoll();
            ahrs_pitch = mpu6050.getPitch();
            ahrs_yaw = mpu6050.getYaw();

            gyroX = mpu6050.getGyroX();
            gyroY = mpu6050.getGyroY();
            gyroZ = mpu6050.getGyroZ();

            Serial.print("Roll: ");
            Serial.println(ahrs_roll);
            Serial.print("Pitch: ");
            Serial.println(ahrs_pitch);
            Serial.print("Yaw: ");
            Serial.println(ahrs_yaw);
            Serial.println();

            Serial.print("GyroX: ");
            Serial.println(gyroX);
            Serial.print("GyroY: ");
            Serial.println(gyroY);
            Serial.print("GyroZ: ");
            Serial.println(gyroZ);
            Serial.println();
        }
    }
}