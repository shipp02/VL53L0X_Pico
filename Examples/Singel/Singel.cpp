/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/i2c.h"
#include "lib/VL53L0X/VL53L0X.hpp"
#include "pico/stdlib.h"
#include <stdio.h>

VL53L0X sensor;
void init_VL53L0X() {
    sensor.init_i2c(0, 4, 5);
    sensor.setTimeout(500);
    if (!sensor.init(true)) {
        printf("Failed to detect and initialize sensor!\n");
        return;
    }
}

int main() {
    stdio_init_all();
    init_VL53L0X();
    while (true) {
        uint16_t value = sensor.readRangeSingleMillimeters();
        printf("\n%i", value);
        if (sensor.timeoutOccurred()) {
            printf(" TIMEOUT");
        }

        printf("\n");
        sleep_ms(50);
    }

    return 0;
}
