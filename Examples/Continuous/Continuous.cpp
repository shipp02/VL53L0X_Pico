/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lib/VL53L0X/VL53L0X.hpp"

void scanBus()
{

    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr)
    {
        if (addr % 16 == 0)
        {
            printf("%02x ", addr);
        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78)
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking_until(i2c0, addr, &rxdata, 1, false, make_timeout_time_ms(10));

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
}


VL53L0X sensor;
void init_VL53L0X()
{
    sensor.init_i2c(0, 4, 5);
    sensor.setTimeout(500);
    if (!sensor.init(true))
    {
        printf("Failed to detect and initialize sensor!\n");
        return;
    }
    sensor.startContinuous();
}

int main()
{
    stdio_init_all();
    init_VL53L0X();
    while (true)
    {
        uint16_t value = sensor.readRangeContinuousMillimeters();
        printf("\n%i", value);
        if (sensor.timeoutOccurred())
        {
            printf(" TIMEOUT");
        }

        printf("\n");
        sleep_ms(50);
    }

    return 0;
}
