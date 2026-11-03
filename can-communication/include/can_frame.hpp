
#ifndef CAN_FRAME_HPP
#define CAN_FRAME_HPP

#include <array>
#include <cstdint>

// Classical CAN standard frame configuration
constexpr uint16_t MAX_CAN_ID = 0x7FF;
constexpr uint8_t MAX_CAN_DLC = 8;

// Railway diagnostic message identifiers
constexpr uint16_t MOTOR_TEMP_ID = 0x101;
constexpr uint16_t WHEEL_VIBRATION_ID = 0x102;
constexpr uint16_t BATTERY_VOLTAGE_ID = 0x103;
constexpr uint16_t MOTOR_CURRENT_ID = 0x104;

// CAN frame representation
struct CANFrame {
    uint16_t id{};
    uint8_t dlc{};
    std::array<uint8_t, 8> data{};
};

// Encode a sensor reading into a CAN frame
CANFrame encodeSensorFrame(
    uint16_t canId,
    double value,
    uint16_t sequence,
    uint8_t status = 0
);

// Decode sensor value from a CAN frame
double decodeSensorValue(const CANFrame& frame);

// Decode sequence number
uint16_t decodeSequence(const CANFrame& frame);

#endif
