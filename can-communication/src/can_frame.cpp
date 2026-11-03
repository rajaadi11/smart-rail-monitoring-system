
#include "can_frame.hpp"

#include <cmath>
#include <stdexcept>

// Encode sensor value into a CAN frame
CANFrame encodeSensorFrame(
    uint16_t canId,
    double value,
    uint16_t sequence,
    uint8_t status
) {

    // Validate CAN identifier
    if (canId > MAX_CAN_ID) {
        throw std::invalid_argument("Invalid CAN identifier");
    }

    // Validate sensor reading
    if (!std::isfinite(value) || value < 0 || value > 655.35) {
        throw std::invalid_argument("Invalid sensor value");
    }

    CANFrame frame{};

    frame.id = canId;
    frame.dlc = 5;

    // Fixed-point encoding: multiply by 100
    uint16_t rawValue = static_cast<uint16_t>(
        std::lround(value * 100.0)
    );

    // Byte 0: Most significant byte
    frame.data[0] = (rawValue >> 8) & 0xFF;

    // Byte 1: Least significant byte
    frame.data[1] = rawValue & 0xFF;

    // Byte 2: Sequence number MSB
    frame.data[2] = (sequence >> 8) & 0xFF;

    // Byte 3: Sequence number LSB
    frame.data[3] = sequence & 0xFF;

    // Byte 4: Diagnostic status
    frame.data[4] = status;

    return frame;
}

// Decode sensor value
double decodeSensorValue(const CANFrame& frame) {

    if (frame.id > MAX_CAN_ID || frame.dlc != 5) {
        throw std::invalid_argument("Invalid CAN frame");
    }

    // Reconstruct 16-bit sensor value
    uint16_t rawValue =
        (static_cast<uint16_t>(frame.data[0]) << 8) |
        frame.data[1];

    return rawValue / 100.0;
}

// Decode sequence number
uint16_t decodeSequence(const CANFrame& frame) {

    if (frame.dlc != 5) {
        throw std::invalid_argument("Invalid CAN frame");
    }

    return
        (static_cast<uint16_t>(frame.data[2]) << 8) |
        frame.data[3];
}
