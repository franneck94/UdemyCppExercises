#include <cassert>
#include <iostream>

#include "AirConditioner.h"

int main()
{
    auto ac = AirConditioner{20};
    const auto measured_temp = ac.measure();
    ac.activate(measured_temp);

    auto ac2 = AirConditioner{15};

    const auto measured1 = 0.0F;
    assert(ac2.activate(measured1) == 30);

    const auto measured2 = -20.0F;
    assert(ac2.activate(measured2) == 70);

    const auto measured3 = -21.0F;
    assert(ac2.activate(measured3) == -1);

    const auto measured4 = 45.0F;
    assert(ac2.activate(measured4) == 30);

    const auto measured5 = 46.0F;
    assert(ac2.activate(measured5) == -1);

    return 0;
}
