#pragma once

#include "AirConditioner.h"

enum class AcStates
{
    IDLE,
    HEATING,
    COOLING,
};

class AcStateMachine
{
public:
    AcStateMachine() = delete;
    AcStateMachine(AirConditioner *const _ac) : ac(_ac){};
    ~AcStateMachine() = default;

    void evaluation(const float curr_temp_cel);
    AcStates get_state();

private:
    void eval_state(const float curr_temp_cel);
    void eval_transition(const float curr_temp_cel);

    AirConditioner *const ac = nullptr;
    AcStates state = AcStates::IDLE;
};
