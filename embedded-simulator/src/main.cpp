
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

// Sensor data structure
struct VehicleSensorData {
    double motorTemperature;
    double wheelVibration;
    double batteryVoltage;
    double motorCurrent;
};

// Generate simulated sensor readings
class SensorSimulator {
private:
    mt19937 generator{random_device{}()};

public:
    VehicleSensorData generateData() {

        uniform_real_distribution<double> temp(55.0, 105.0);
        uniform_real_distribution<double> vibration(0.5, 8.0);
        uniform_real_distribution<double> voltage(60.0, 85.0);
        uniform_real_distribution<double> current(5.0, 40.0);

        return {
            temp(generator),
            vibration(generator),
            voltage(generator),
            current(generator)
        };
    }
};

// Vehicle diagnostic system
class DiagnosticSystem {

public:
    string checkHealth(const VehicleSensorData& data) {

        if (data.motorTemperature > 90.0)
            return "CRITICAL: MOTOR OVERHEATING";

        if (data.wheelVibration > 6.0)
            return "WARNING: ABNORMAL VIBRATION";

        if (data.batteryVoltage < 65.0 ||
            data.batteryVoltage > 80.0)
            return "WARNING: BATTERY VOLTAGE";

        if (data.motorCurrent > 35.0)
            return "WARNING: HIGH MOTOR CURRENT";

        return "NORMAL";
    }
};

int main() {

    SensorSimulator simulator;
    DiagnosticSystem diagnostics;

    cout << "SMART RAIL VEHICLE MONITORING SYSTEM\n";
    cout << "Vehicle ID: TRAIN_001\n";

    while (true) {

        VehicleSensorData data = simulator.generateData();

        string status = diagnostics.checkHealth(data);

        cout << fixed << setprecision(2);

        cout << "\n-----------------------------\n";

        cout << "Motor Temperature: "
             << data.motorTemperature << " C\n";

        cout << "Wheel Vibration: "
             << data.wheelVibration << " mm/s\n";

        cout << "Battery Voltage: "
             << data.batteryVoltage << " V\n";

        cout << "Motor Current: "
             << data.motorCurrent << " A\n";

        cout << "Vehicle Status: " << status << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
