#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

#include "AdTypes.hpp"

std::vector<const VehicleInformationType *> get_vehicles_on_lane(const LaneAssociationType lane,
                                                                 const NeighborVehiclesType &vehicles);

const VehicleInformationType *get_impeding_vehicle(
    const std::vector<const VehicleInformationType *> &vehicles);

const VehicleInformationType *get_closing_vehicle(
    const std::vector<const VehicleInformationType *> &vehicles);

bool get_longitudinal_request(const VehicleInformationType *const front_vehicle,
                              VehicleInformationType &ego_vehicle);

void longitudinal_control(VehicleInformationType &ego_vehicle);

LaneAssociationType get_lat_request(const VehicleInformationType &ego_vehicle,
                                    const NeighborVehiclesType &vehicles);

bool lateral_control(const LaneAssociationType lat_request, VehicleInformationType &ego_vehicle);
