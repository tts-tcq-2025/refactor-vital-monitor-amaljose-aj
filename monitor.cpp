#include "monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <utility>  

using std::cout;
using std::flush;
using std::string;
using std::vector;

static void blinkAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "\r *" << flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

VitalStatus checkTemperature(float temperature) {
    return (temperature > 102 || temperature < 95) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkPulseRate(float pulseRate) {
    return (pulseRate < 60 || pulseRate > 100) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkSpo2(float spo2) {
    return (spo2 < 90) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

void showAlert(const string& message) {
    cout << message << std::endl;
    blinkAlert();
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
    vector<std::pair<VitalStatus, string>> results = {
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
