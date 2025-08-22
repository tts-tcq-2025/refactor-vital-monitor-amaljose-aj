#include <iostream>
#include <thread>
#include <chrono>
#include <string>
using namespace std;


enum class VitalStatus { OK, CRITICAL };


VitalStatus checkTemperature(float temperature) {
    return (temperature > 102 || temperature < 95) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkPulseRate(float pulseRate) {
    return (pulseRate < 60 || pulseRate > 100) ? VitalStatus::CRITICAL : VitalStatus::OK;
}

VitalStatus checkSpo2(float spo2) {
    return (spo2 < 90) ? VitalStatus::CRITICAL : VitalStatus::OK;
}


static void blinkAlert() {
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\r *" << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void showAlert(const string& message) {
    cout << message << endl;
    blinkAlert();
}


bool vitalsOk(float temperature, float pulseRate, float spo2) {
    if (checkTemperature(temperature) == VitalStatus::CRITICAL) {
        showAlert("Temperature is critical!");
        return false;
    }
    if (checkPulseRate(pulseRate) == VitalStatus::CRITICAL) {
        showAlert("Pulse Rate is out of range!");
        return false;
    }
    if (checkSpo2(spo2) == VitalStatus::CRITICAL) {
        showAlert("Oxygen Saturation out of range!");
        return false;
    }
    return true;
}

#ifdef RUN_MAIN
int main() {
    vitalsOk(98.6, 72, 96);   
    vitalsOk(104, 72, 96);   
    return 0;
}
#endif
