#pragma once

#include "AdTypes.hpp"

float kph_to_mps(const float kph);

float mps_to_kph(const float mps);

void init_ego_vehicle(VehicleType &ego_vehicle);

void init_vehicles(NeighborVehiclesType &vehicles);

void print_vehicle(const VehicleType &vehicle);

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);

void print_vehicle_speed(const VehicleType &vehicle, const char *name);

void print_scene(const VehicleType &ego_vehicle,
                 const NeighborVehiclesType &vehicles);

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds);

void decrease_speed(VehicleType &ego_vehicle);

void longitudinal_control(const VehicleType &front_vehicle,
                          VehicleType &ego_vehicle);
