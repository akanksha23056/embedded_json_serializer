/*
 * json_serializer.h
 *
 *  Created on: 08-Jan-2026
 *      Author: rayak
 */

#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <stddef.h>
#include "meter_data.h"

typedef enum {
    JSON_OK = 0,
    JSON_BUFFER_TOO_SMALL,
    JSON_INVALID_INPUT
} JsonStatus;

JsonStatus serialize_to_json(const MeterPayload *payload,
                             char *buffer,
                             size_t buffer_size,
                             size_t *written_length);

#endif
