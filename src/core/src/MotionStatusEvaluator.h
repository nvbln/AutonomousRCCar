#pragma once

#include "strategies/ISpikeDetectionStrategy.h"
#include "strategies/IMotionEvaluationStrategy.h"
#include "IAccelerator.h"
#include "MotionStatus.h"

#include <CircularBuffer.hpp>

#include <memory>

/**
 * @Class MotionStatusEvaluator
 * @brief accumulates data and uses the strategies to update the motion status.
 *
 * The class is designed to continuously gather data as it is made available.
 * Upon request of the status, if new data is available, the evaluator
 * will evaluate the current motion status using the strategies that have
 * been passed to the constructor.
 */
class MotionStatusEvaluator {
public:
    /**
     * @brief creates an instance of the MotionStatusEvaluator
     * 
     * @params accelerator an instance of the IMU data source.
     * @params spikeStrategy the strategy to use for detecting spikes.
     * @params motionStrategy the strategy to use for determining the new motion status.
     */
    MotionStatusEvaluator(std::shared_ptr<IAccelerator> accelerator,
                          std::shared_ptr<ISpikeDetectionStrategy> spikeStrategy,
                          std::shared_ptr<IMotionEvaluationStrategy> motionStrategy) :
            mSpikeStrategy(spikeStrategy), mMotionStrategy(motionStrategy) {
        mBufferX = std::make_shared<CircularBuffer<float, 50>>();
        mBufferY = std::make_shared<CircularBuffer<float, 50>>();
        accelerator->addCallback([this](AccelerationData data) {
            this->updateData(data);
        });
    }

    /**
     * @brief Calculates and returns the current MotionStatus.
     *
     * @return the most up-to-date MotionStatus
     */
    MotionStatus status(); 

private:
    MotionStatus mCurrentStatus = MotionStatus::Still;
    bool mHasNewData = false;
    std::shared_ptr<CircularBuffer<float, 50>> mBufferX;
    std::shared_ptr<CircularBuffer<float, 50>> mBufferY;
    std::shared_ptr<ISpikeDetectionStrategy> mSpikeStrategy;
    std::shared_ptr<IMotionEvaluationStrategy> mMotionStrategy;

    void updateData(AccelerationData data);
};
