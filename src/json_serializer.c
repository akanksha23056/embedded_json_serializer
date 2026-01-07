/*
 * json_serializer.c
 *
 *  Created on: 08-Jan-2026
 *      Author: rayak
 */
#include "json_serializer.h"
#include <stdio.h>
#include <string.h>

#define WRITE(fmt, ...)                                   \
    do {                                                   \
        int len = snprintf(buffer + offset,               \
                            buffer_size - offset,         \
                            fmt, ##__VA_ARGS__);           \
        if (len < 0 || (size_t)len >= buffer_size - offset)\
            return JSON_BUFFER_TOO_SMALL;                  \
        offset += len;                                     \
    } while (0)

JsonStatus serialize_to_json(const MeterPayload *payload,
                             char *buffer,
                             size_t buffer_size,
                             size_t *written_length)
{
    if (!payload || !buffer)
        return JSON_INVALID_INPUT;

    size_t offset = 0;

    WRITE("[{");
    WRITE("\"gatewayId\":\"%s\",", payload->gatewayId);
    WRITE("\"date\":\"%s\",", payload->date);
    WRITE("\"deviceType\":\"%s\",", payload->deviceType);
    WRITE("\"interval_minutes\":%d,", payload->interval_minutes);
    WRITE("\"total_readings\":%d,", payload->total_readings);

    WRITE("\"values\":{");
    WRITE("\"device_count\":%d,", payload->device_count);
    WRITE("\"readings\":[");

    for (uint8_t i = 0; i < payload->device_count; i++) {
        DeviceReading *d = &payload->devices[i];

        WRITE("{");
        WRITE("\"media\":\"%s\",", d->media);
        WRITE("\"meter\":\"%s\",", d->meter);
        WRITE("\"deviceId\":\"%s\",", d->deviceId);
        WRITE("\"unit\":\"%s\",", d->unit);
        WRITE("\"data\":[");

        for (uint8_t j = 0; j < d->data_count; j++) {
            MeterDataPoint *p = &d->data[j];

            WRITE("{");
            WRITE("\"timestamp\":\"%s\",", p->timestamp);
            WRITE("\"meter_datetime\":\"%s\",", p->meter_datetime);
            WRITE("\"total_m3\":%.3f,", p->total_m3);
            WRITE("\"status\":\"%s\"", p->status);
            WRITE("}");

            if (j < d->data_count - 1) WRITE(",");
        }

        WRITE("]}");
        if (i < payload->device_count - 1) WRITE(",");
    }

    WRITE("]}}]");
    if (written_length) *written_length = offset;

    return JSON_OK;
}


