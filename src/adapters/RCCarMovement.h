#pragma once

#include "IWheel.h"
#include "IVehicleMovement.h"

#include <memory>

class RCCarMovement : public IVehicleMovement {
public:
    RCCarMovement(std::shared_ptr<IWheel> leftWheel, std::shared_ptr<IWheel> rightWheel) :
            mLeftWheel(leftWheel), mRightWheel(rightWheel) {}

    /**
     * @see IVehicleMovement::forward()
     */
    void forward() override;

    /**
     * @see IVehicleMovement::backward()
     */
    void backward() override;

    /**
     * @see IVehicleMovement::turnDegrees()
     */
    void turnDegrees(int degrees) override;

    /**
     * @see IVehicleMovement::stop()
     */
    void stop() override;

private:
    const std::shared_ptr<IWheel> mLeftWheel, mRightWheel;
};
