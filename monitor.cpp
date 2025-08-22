#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <utility>  // for std::pair
#include <string>   // explicit include for std::string

// ------------------- Pure Functions (Testable) -------------------
VitalStatus checkTemperature(float temperature) {
    return (temperature > 102 || temperature < 95) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkPulseRate(float pulseRate) {
    return (pulseRate < 60 || pulseRate > 100) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkSpo2(float spo2) {
    return (spo2 < 90) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

// ------------------- I/O Functions -------------------
static void blinkAlert() {
    for (int i = 0; i < 6; i++) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void showAlert(const std::string& message) {
    std::cout << message << std::endl;
    blinkAlert();
}

// ------------------- Main Vital Check -------------------
bool vitalsOk(float temperature, float pulseRate, float spo2) {
    std::vector<std::pair<VitalStatus, std::string>> results = {
        {checkTemperature(temperature), "Temperature is critical!"},
        {checkPulseRate(pulseRate), "Pulse Rate is out of range!"},
        {checkSpo2(spo2), "Oxygen Saturation out of range!"}
    };

    for (auto& r : results) {
        if (r.first == VitalStatus::CRITICAL) {
            showAlert(r.second);
            return false;
        }
    }
    return true;
}
