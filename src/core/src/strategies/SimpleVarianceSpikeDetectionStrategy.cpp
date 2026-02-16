#include "SimpleVarianceSpikeDetectionStrategy.h"

#include <cmath>

// TODO: Split this algorithm into more modular chunks with private member functions.
bool SimpleVarianceSpikeDetectionStrategy::detectSpike(
        const std::shared_ptr<CircularBuffer<float, 50>> bufferX,
        const std::shared_ptr<CircularBuffer<float, 50>> bufferY) const {

    // Does not function predictably without full buffers.
    if (!bufferX->isFull() || !bufferY->isFull()) {
        return false;
    }

    auto& bufX = *bufferX;
    auto& bufY = *bufferY;

    float totalSumX = 0;
    float totalSumY = 0;
    for (int i = 0; i < mBaselineSize; i++) {
        totalSumX += bufX[i];
        totalSumY += bufY[i];
    }

    float avgX = totalSumX / mBaselineSize;
    float avgY = totalSumY / mBaselineSize;

    float varX = 0;
    float varY = 0;
    for (int i = 0; i < mBaselineSize; i++) {
        varX += std::abs(avgX - bufX[i]);
        varY += std::abs(avgY - bufY[i]);
    }

    varX /= mBaselineSize;
    varY /= mBaselineSize;

    float varInterestX = 0;
    float varInterestY = 0;
    for (int i = mBaselineSize; i < BUFFER_SIZE; i++) {
        varInterestX += std::abs(avgX - bufX[i]);
        varInterestY += std::abs(avgY - bufY[i]);
    }

    varInterestX /= BUFFER_SIZE - mBaselineSize;
    varInterestY /= BUFFER_SIZE - mBaselineSize;

    if (varInterestX > varX * mOutlierMultiple || varInterestY > varY * mOutlierMultiple) {
        return true;
    }

    return false;
}
