
#include "can_frame.hpp"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

// Display CAN frame
void printFrame(const CANFrame& frame) {

    cout << "CAN ID: 0x"
         << hex << uppercase
         << setw(3) << setfill('0')
         << frame.id;

    cout << dec << " | DLC: "
         << static_cast<int>(frame.dlc);

    cout << " | DATA: ";

    for (int i = 0; i < frame.dlc; i++) {

        cout << "0x"
             << hex << uppercase
             << setw(2) << setfill('0')
             << static_cast<int>(frame.data[i])
             << " ";
    }

    cout << dec << endl;
}

// Identify sensor using CAN ID
string getSensorName(uint16_t id) {

    switch (id) {

        case MOTOR_TEMP_ID:
            return "Motor Temperature";

        case WHEEL_VIBRATION_ID:
            return "Wheel Vibration";

        case BATTERY_VOLTAGE_ID:
            return "Battery Voltage";

        case MOTOR_CURRENT_ID:
            return "Motor Current";

        default:
            return "Unknown Sensor";
    }
}

// Simulated receiver
void receiveFrame(const CANFrame& frame) {

    cout << "\n[RECEIVER] Message received\n";

    cout << "Sensor: "
         << getSensorName(frame.id) << endl;

    cout << "Sequence: "
         << decodeSequence(frame) << endl;

    cout << "Decoded Value: "
         << fixed << setprecision(2)
         << decodeSensorValue(frame) << endl;

    cout << "Diagnostic Status: "
         << (frame.data[4] == 0 ? "NORMAL" : "WARNING")
         << endl;
}

int main() {

    cout << "====================================\n";
    cout << " SMART RAIL CAN COMMUNICATION SYSTEM\n";
    cout << "====================================\n";

    // Simulated sensor readings
    vector<CANFrame> messages;

    messages.push_back(
        encodeSensorFrame(MOTOR_TEMP_ID, 78.45, 1)
    );

    messages.push_back(
        encodeSensorFrame(WHEEL_VIBRATION_ID, 2.40, 2)
    );

    messages.push_back(
        encodeSensorFrame(BATTERY_VOLTAGE_ID, 72.00, 3)
    );

    messages.push_back(
        encodeSensorFrame(MOTOR_CURRENT_ID, 18.50, 4)
    );

    // TRANSMITTER
    cout << "\n[TRANSMITTER] Sending CAN messages\n\n";

    for (const auto& frame : messages) {
        printFrame(frame);
    }

    // RECEIVER
    cout << "\n====================================\n";
    cout << " RECEIVER PROCESSING\n";
    cout << "====================================\n";

    for (const auto& frame : messages) {
        receiveFrame(frame);
    }

    cout << "\nCAN communication simulation completed.\n";



    cout << "\n========== TEST 1 ==========\n";

    CANFrame testFrame =
        encodeSensorFrame(MOTOR_TEMP_ID, 78.45, 1);

    double decodedValue = decodeSensorValue(testFrame);

    cout << "Original Value: 78.45\n";
    cout << "Decoded Value: " << decodedValue << endl;

    if (decodedValue == 78.45) {
        cout << "TEST 1 PASSED\n";
    } 
    else {
        cout << "TEST 1 FAILED\n";
    }

    cout << "\n========== TEST 2 ==========\n";

    try {

        encodeSensorFrame(0x900, 78.45, 1);

        cout << "TEST 2 FAILED\n";

    }
    catch (const invalid_argument& e) {

        cout << "TEST 2 PASSED\n";
        cout << "Error: " << e.what() << endl;

    }
    cout << "\n========== TEST 3 ==========\n";

    try {

        encodeSensorFrame(MOTOR_TEMP_ID, -10.0, 1);

        cout << "TEST 3 FAILED\n";

    }
    catch (const invalid_argument& e) {

        cout << "TEST 3 PASSED\n";
        cout << "Error: " << e.what() << endl;

    }


    return 0;
}



