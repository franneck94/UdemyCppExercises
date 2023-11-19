#pragma once

#include <cstdint>

#include "AdTypes.hpp"

float kph_to_mps(const float kph);

float mps_to_kph(const float mps);

void print_vehicle(const VehicleType &vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);

void print_scene(const VehicleType &ego_vehicle,
                 const NeighborVehiclesType &vehicles);

void print_vehicle_speed(const VehicleType &vehicle, const char *name);

void compute_future_distance(VehicleType &vehicle,
                             const float ego_driven_distance,
                             const float seconds);

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds);

void longitudinal_control(const VehicleType &front_vehicle,
                          VehicleType &ego_vehicle);

const VehicleType *get_vehicle_array(const LaneAssociationType lane,
                                     const NeighborVehiclesType &vehicles);

LaneAssociationType get_lane_change_request(
    const VehicleType &ego_vehicle,
    const NeighborVehiclesType &vehicles);

bool lateral_control(const LaneAssociationType lane_change_request,
                     VehicleType &ego_vehicle);
