#pragma once

#include <cstdint>

/**
 * Represents the different modes of motion that the vehicle can be in.
 * * Moving: the vehicle is moving (motors are on).
 * * Still: the vehicle is intentionally standing still (motors are off).
 * * Blocked: the vehicle not moving due to outside factors (motors are on).
 */
enum class MotionStatus : uint8_t { Moving, Still, Blocked };
