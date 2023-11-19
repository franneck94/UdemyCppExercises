#include "AcStateMachine.h"

void AcStateMachine::evaluation(const float curr_temp_cel)
{
    eval_state(curr_temp_cel);
    eval_transition(curr_temp_cel);
}

AcStates AcStateMachine::get_state()
{
    return state;
}

void AcStateMachine::eval_state(const float curr_temp_cel)
{
    switch (state)
    {
    case AcStates::COOLING:
    case AcStates::HEATING:
    {
        ac->activate(curr_temp_cel);
    }
    case AcStates::IDLE:
    default:
    {
        break;
    }
    }
}

void AcStateMachine::eval_transition(const float curr_temp_cel)
{
    const auto need_heating = curr_temp_cel < ac->get_target_temp_cel();
    const auto need_cooling = curr_temp_cel > ac->get_target_temp_cel();

    if (need_heating)
    {
        state = AcStates::HEATING;
    }
    else if (need_cooling)
    {
        state = AcStates::COOLING;
    }
    else
    {
        state = AcStates::IDLE;
    }
}
