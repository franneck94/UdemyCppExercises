#pragma once

#include "DataLoader.hpp"

static constexpr const char *const LANE_NAMES[] = {
    "Left",
    "Center",
    "Right",
    "None",
};

static constexpr const char *const OBJECT_NAMES[] = {
    "Car",
    "Truck",
    "Motorbike",
    "None",
};

void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes,
                  const bool long_request,
                  const LaneAssociationType lat_request);

static void plot_lanes(const VehicleInformationType &ego_vehicle,
                       const NeighborVehiclesType &vehicles,
                       const LanesInformationType &lanes,
                       const bool long_request,
                       const LaneAssociationType lat_request);

static void plot_table(const VehicleInformationType &ego_vehicle, const NeighborVehiclesType &vehicles);
