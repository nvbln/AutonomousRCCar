#pragma once

#include "ISpikeDetectionStrategy.h"

/**
 * @class SimpleVarianceSpikeDetectionStrategy
 * @brief detects a spike using the variance of the baseline and interest periods.
 *
 * The following strategy is implemented in this class:
 * The variance is calculated for both the baseline period and the
 * period of interest. If the variance in the period of interest is
 * a factor of outlierMultiple higher than the variance in the
 * baseline period, it detects it as a spike.
 */
class SimpleVarianceSpikeDetectionStrategy : public ISpikeDetectionStrategy {
private:
    static constexpr uint8_t BUFFER_SIZE = 50;

public:
    /**
     * @brief creates an instance of the strategy.
     *
     * @params baselineSize Number of samples to use as baseline.
     * @params outlierMultiple How many times higher the spike variance
     *         should be than the baseline to be considered a spike.
     */
    SimpleVarianceSpikeDetectionStrategy(uint8_t baselineSize = 45,
                                         uint8_t outlierMultiple = 10) :
                                         mOutlierMultiple(outlierMultiple) {
        if (mBaselineSize > BUFFER_SIZE - 1) {
            mBaselineSize = 45;
        } else {
            mBaselineSize = baselineSize;
        }
    };

    /**
     * @brief detects spikes based on the relative difference in variance.
     *
     * NOTE: If the buffer is not filled, the function will always return false.
     * @see ISpikeDetectionStrategy::detectSpike()
     */
    bool detectSpike(const std::shared_ptr<CircularBuffer<float, BUFFER_SIZE>> bufferX,
                     const std::shared_ptr<CircularBuffer<float, BUFFER_SIZE>> bufferY) const override;

private:
    uint8_t mBaselineSize;
    uint8_t mOutlierMultiple;
};
