#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

#include "AdTypes.hpp"

AdOutputsType compute_cycle(VehicleInformationType &ego_vehicle,
                            NeighborVehiclesType &vehicles,
                            LanesInformationType &lanes);
