/*
  SITL airspeed backend - a perfect airspeed sensor
 */
#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL_Boards.h>

#ifndef AP_AIRSPEED_ENABLED
#define AP_AIRSPEED_ENABLED 1
#endif

#ifndef AP_AIRSPEED_MSP_ENABLED
#define AP_AIRSPEED_MSP_ENABLED (AP_AIRSPEED_ENABLED && HAL_MSP_SENSORS_ENABLED)
#endif

#ifndef AIRSPEED_MAX_SENSORS
#define AIRSPEED_MAX_SENSORS 2
#endif

#ifndef AP_AIRSPEED_AUTOCAL_ENABLE
#define AP_AIRSPEED_AUTOCAL_ENABLE AP_AIRSPEED_ENABLED
#endif

#ifndef AP_AIRSPEED_HYGROMETER_ENABLE
#define AP_AIRSPEED_HYGROMETER_ENABLE (AP_AIRSPEED_ENABLED && BOARD_FLASH_SIZE > 1024)
#endif


#include "AP_Airspeed_Backend.h"

class AP_Airspeed_SITL : public AP_Airspeed_Backend
{
public:

    using AP_Airspeed_Backend::AP_Airspeed_Backend;

    bool init(void) override {
        return true;
    }

    // return the current differential_pressure in Pascal
    bool get_differential_pressure(float &pressure) override;

    // temperature not available via analog backend
    bool get_temperature(float &temperature) override;

private:
};

