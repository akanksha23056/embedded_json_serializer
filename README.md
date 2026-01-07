# Embedded JSON Serialization Library for Smart Meter Data

## Project Overview

This project implements an **embedded-friendly JSON serialization library** for structured smart meter data, inspired by a typical **w-M-Bus gateway → backend data pipeline**.

The library converts well-defined internal C data structures into a **strictly specified JSON format**, ensuring correctness, deterministic memory usage, and robustness — all essential properties for embedded firmware development.

## Platform & Programming Language

* **Programming Language:** C
* **Target Platform:** STM32 (embedded firmware context)
* **Development & Testing:** Host-based C application (GCC)

### Justification

C was chosen due to its:

* Deterministic memory behavior
* Wide adoption in embedded systems
* Fine-grained control over memory and data layout

Although the library is designed for STM32 firmware, correctness was validated using a **host-based C test application** compiled with GCC.
The serialization logic itself is **completely hardware-agnostic** and can be integrated into STM32 firmware without modification.

---

## Project Structure

```
/
├── src/
│   ├── main.c                # Example application
│   ├── json_serializer.c     # JSON serialization logic
│   └── meter_data.c          # Data model implementation
├── include/
│   ├── json_serializer.h     # Public serialization API
│   └── meter_data.h          # Data structure definitions
├── README.md
└── LICENSE (optional)
```

---

## Data Model

The internal data model closely mirrors the required JSON schema while remaining suitable for embedded systems.


### API Characteristics

* Transport-agnostic (no UART, radio, MQTT, etc.)
* Caller-provided output buffer
* Explicit buffer size handling
* Clear error reporting

### Error Handling

```c
typedef enum {
    JSON_OK = 0,
    JSON_BUFFER_TOO_SMALL,
    JSON_INVALID_INPUT
} JsonStatus;
```

The serializer:

* Detects invalid input pointers
* Prevents buffer overflows
* Fails safely if output buffer is too small

## JSON Output Format

The library generates **exactly** the following JSON structure (outer array always present):

```json
[
  {
    "gatewayId": "gateway_1234",
    "date": "1970-01-01",
    "deviceType": "stromleser",
    "interval_minutes": 15,
    "total_readings": 1,
    "values": {
      "device_count": 1,
      "readings": [
        {
          "media": "water",
          "meter": "waterstarm",
          "deviceId": "stromleser_50898527",
          "unit": "m3",
          "data": [
            {
              "timestamp": "1970-01-01 00:00",
              "meter_datetime": "1970-01-01 00:00",
              "total_m3": 107.752,
              "status": "OK"
            }
          ]
        }
      ]
    }
  }
]
```

### Compliance Notes

* Field names are unchanged
* Structure is unchanged
* Numbers are serialized as numbers (not strings)
* No additional fields are added
* Floating-point values preserve precision

## Example Application

The example application demonstrates typical usage:

1. Create and populate sample meter data
2. Call the serialization library
3. Output the generated JSON to the console

This validates correctness and provides a reference for firmware integration.


## Memory Usage & Limits

* All memory usage is **static and deterministic**
* No heap allocation
* Maximum JSON output size (current configuration): **≤ 1024 bytes**

This makes the library suitable for resource-constrained embedded systems.

---

## Build & Run Instructions (Host-Based Test)

From the project root:

```bash
gcc src/main.c src/json_serializer.c src/meter_data.c -Iinclude -o embedded_json_serializer
./embedded_json_serializer
```

The generated JSON will be printed to the console.

---

## Design Decisions & Assumptions

* Fixed-size buffers were chosen to ensure deterministic behavior
* Serialization logic is separated from data modeling
* Transport and hardware dependencies are intentionally excluded
* Host-based testing is used to validate logic before firmware integration

 
