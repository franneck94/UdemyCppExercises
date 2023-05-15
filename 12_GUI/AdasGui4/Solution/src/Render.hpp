#pragma once

#include "DataLoader.hpp"

void render_cycle(const VehicleType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes);

void plot_lanes(const VehicleType &ego_vehicle,
                const NeighborVehiclesType &vehicles,
                const LanesInformationType &lanes);

void plot_table(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);
