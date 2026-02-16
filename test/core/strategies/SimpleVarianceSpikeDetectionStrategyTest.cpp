#include "strategies/SimpleVarianceSpikeDetectionStrategy.h"

#include <CircularBuffer.hpp>
#include <random>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(SimpleVarianceSpikeDetectionStrategyTests, shouldReturnFalseOnNotEnoughData) {
    auto strategy = std::make_shared<SimpleVarianceSpikeDetectionStrategy>();

    auto bufferX = std::make_shared<CircularBuffer<float, 50>>();
    auto bufferY = std::make_shared<CircularBuffer<float, 50>>();

    EXPECT_FALSE(strategy->detectSpike(bufferX, bufferY));

    // Feed some reproducible random data.
    int seed = 123;
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(-4.0f, 4.0f);
    for (int i = 0; i < 30; i++) {
        bufferX->push(dist(rng));
        bufferY->push(dist(rng));
    }

    EXPECT_FALSE(strategy->detectSpike(bufferX, bufferY));
}

TEST(SimpleVarianceSpikeDetectionStrategyTests, shouldReturnTrueOnSpike) {
    auto strategy = std::make_shared<SimpleVarianceSpikeDetectionStrategy>();

    auto bufferX = std::make_shared<CircularBuffer<float, 50>>();
    auto bufferY = std::make_shared<CircularBuffer<float, 50>>();

    // Generate a simple spike
    for (int i = 0; i < 45; i++) {
        if (i % 2 == 0) {
            bufferX->push(1);
            bufferY->push(1);
        } else {
            bufferX->push(-1);
            bufferY->push(-1);
        }
    }

    bufferX->push(5);
    bufferX->push(10);
    bufferX->push(25);
    bufferX->push(10);
    bufferX->push(5);

    bufferY->push(5);
    bufferY->push(10);
    bufferY->push(25);
    bufferY->push(10);
    bufferY->push(5);

    EXPECT_TRUE(strategy->detectSpike(bufferX, bufferY));
}
