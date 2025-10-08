#pragma once
#include <string>

// Enum for vital status
enum class VitalStatus { OK, CRITICAL };

// Pure functions
VitalStatus checkTemperature(float temperature);
VitalStatus checkPulseRate(float pulseRate);
VitalStatus checkSpo2(float spo2);

// I/O
void showAlert(const std::string& message);

// Main vital check
bool vitalsOk(float temperature, float pulseRate, float spo2);
