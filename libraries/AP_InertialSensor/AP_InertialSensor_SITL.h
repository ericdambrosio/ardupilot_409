#pragma once

#include <SITL/SITL.h>

#include "AP_InertialSensor.h"
#include "AP_InertialSensor_Backend.h"
// For shared memory transport
#include <sys/ipc.h>
#include <sys/shm.h>
// #include <sys/sem.h>
#include <semaphore.h>

#define INS_SITL_INSTANCES 2

class AP_InertialSensor_SITL : public AP_InertialSensor_Backend
{
public:
    AP_InertialSensor_SITL(AP_InertialSensor &imu);

    /* update accel and gyro state */
    bool update() override;

    // detect the sensor
    static AP_InertialSensor_Backend *detect(AP_InertialSensor &imu);
    ~AP_InertialSensor_SITL();

private:
    bool init_sensor(void);
    void timer_update();
    float gyro_drift(void);
    void generate_accel(uint8_t instance);
    void generate_gyro(uint8_t instance);

    SITL::SITL *sitl;

    // simulated sensor rates in Hz. This matches a pixhawk1
    const uint16_t gyro_sample_hz[INS_SITL_INSTANCES]  { 1000, 760 };
    const uint16_t accel_sample_hz[INS_SITL_INSTANCES] { 1000, 800 };

    uint8_t gyro_instance[INS_SITL_INSTANCES];
    uint8_t accel_instance[INS_SITL_INSTANCES];
    uint64_t next_gyro_sample[INS_SITL_INSTANCES];
    uint64_t next_accel_sample[INS_SITL_INSTANCES];

    // Shared memory transport
    bool use_shm = false;
    key_t key;
    int shmid;
    uint8_t* data;
    sem_t* sem;

    struct ShmIMU
    {
        unsigned long msg_id = 0;
        uint64_t time_now_us = 0;
        // Vector3f accel {0., 0., 0.};
        // Vector3f gyro {0., 0., 0.};
        float accel[3] = {0., 0., 0.};
        float gyro[3] = {0., 0., 0.};
    }ShmIMUMsg;
};
