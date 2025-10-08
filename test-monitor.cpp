#include <gtest/gtest.h>
#include "./monitor.h"

// Temperature Tests
TEST(Monitor, TemperatureCriticalHigh) {
    EXPECT_FALSE(vitalsOk(103, 70, 95));
}

TEST(Monitor, TemperatureCriticalLow) {
    EXPECT_FALSE(vitalsOk(94, 70, 95));
}

TEST(Monitor, TemperatureNormal) {
    EXPECT_TRUE(vitalsOk(98.6, 70, 95));
}

// Pulse Rate Tests
TEST(Monitor, PulseRateCriticalHigh) {
    EXPECT_FALSE(vitalsOk(98.6, 120, 95));
}

TEST(Monitor, PulseRateCriticalLow) {
    EXPECT_FALSE(vitalsOk(98.6, 50, 95));
}

TEST(Monitor, PulseRateNormal) {
    EXPECT_TRUE(vitalsOk(98.6, 70, 95));
}

// SpO2 Tests
TEST(Monitor, Spo2CriticalLow) {
    EXPECT_FALSE(vitalsOk(98.6, 70, 85));
}

TEST(Monitor, Spo2Normal) {
    EXPECT_TRUE(vitalsOk(98.6, 70, 95));
}

// Combined Failures
TEST(Monitor, MultipleVitalsCritical) {
    EXPECT_FALSE(vitalsOk(103, 120, 85));
    EXPECT_FALSE(vitalsOk(94, 50, 85));
}

// All Normal
TEST(Monitor, AllVitalsNormal) {
    EXPECT_TRUE(vitalsOk(98.1, 72, 97));
}
