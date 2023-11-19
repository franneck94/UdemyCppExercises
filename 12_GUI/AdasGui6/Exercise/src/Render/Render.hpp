#pragma once

#include "DataLoader.hpp"

void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes,
                  const bool long_request,
                  const LaneAssociationType lat_request,
                  const std::uint32_t cycle_idx);
