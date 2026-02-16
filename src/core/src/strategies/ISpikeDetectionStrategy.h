#pragma once

#include <CircularBuffer.hpp>

#include <memory>

/**
 * @class ISpikeDetectionStrategy
 * @brief interface for the strategies that detect spikes in IMU data.
 */
class ISpikeDetectionStrategy {
public:
    virtual ~ISpikeDetectionStrategy() = default;

    /**
     * @brief detects spikes in the most recent IMU data.
     *
     * @params bufferX The buffer with the most recent IMU data on the x-axis.
     * @params bufferY The buffer with the most recent IMU data on the y-axis.
     * @return Whether a spike was detected or not in the data.
     */
    virtual bool detectSpike(const std::shared_ptr<CircularBuffer<float, 50>> bufferX,
                             const std::shared_ptr<CircularBuffer<float, 50>> bufferY) const = 0;
};
