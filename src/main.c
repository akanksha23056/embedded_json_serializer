/*
 * main.c
 *
 *  Created on: 08-Jan-2026
 *      Author: rayak
 */
#include <stdio.h>
#include "meter_data.h"
#include "json_serializer.h"

int main(void)
{
    MeterPayload payload = {0};

    snprintf(payload.gatewayId, sizeof(payload.gatewayId), "gateway_1234");
    snprintf(payload.date, sizeof(payload.date), "1970-01-01");
    snprintf(payload.deviceType, sizeof(payload.deviceType), "stromleser");

    payload.interval_minutes = 15;
    payload.total_readings = 1;
    payload.device_count = 1;

    DeviceReading *dev = &payload.devices[0];
    snprintf(dev->media, sizeof(dev->media), "water");
    snprintf(dev->meter, sizeof(dev->meter), "waterstarm");
    snprintf(dev->deviceId, sizeof(dev->deviceId), "stromleser_50898527");
    snprintf(dev->unit, sizeof(dev->unit), "m3");
    dev->data_count = 1;

    MeterDataPoint *dp = &dev->data[0];
    snprintf(dp->timestamp, sizeof(dp->timestamp), "1970-01-01 00:00");
    snprintf(dp->meter_datetime, sizeof(dp->meter_datetime), "1970-01-01 00:00");
    dp->total_m3 = 107.752f;
    snprintf(dp->status, sizeof(dp->status), "OK");

    char json_buffer[1024];
    size_t written;

    if (serialize_to_json(&payload, json_buffer, sizeof(json_buffer), &written) == JSON_OK) {
        printf("%s\n", json_buffer);
    }

    return 0;
}


