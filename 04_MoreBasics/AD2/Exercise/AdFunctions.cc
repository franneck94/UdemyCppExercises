#include <cmath>
#include <cstdint>
#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"

float kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

void init_ego_vehicle(VehicleType &ego_vehicle)
{
    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.speed_mps = kph_to_mps(135.0F);
    ego_vehicle.distance_m = 0.0F;
    ego_vehicle.lane = LaneAssociationType::CENTER;
}

void init_vehicle(VehicleType &vehicle,
                  const std::int32_t id,
                  const float speed_kph,
                  const float distance_m,
                  const LaneAssociationType lane)
{
    vehicle.id = id;
    vehicle.speed_mps = kph_to_mps(speed_kph);
    vehicle.distance_m = distance_m;
    vehicle.lane = lane;
}

void init_vehicles(NeighborVehiclesType &vehicles)
{
    init_vehicle(vehicles.vehicles_left_lane[0],
                 0,
                 130.0F,
                 80.0F,
                 LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_left_lane[1],
                 1,
                 80.0F,
                 -20.0F,
                 LaneAssociationType::LEFT);
    init_vehicle(vehicles.vehicles_center_lane[0],
                 2,
                 80.0F,
                 50.0F,
                 LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_center_lane[1],
                 3,
                 120.0F,
                 -50.0F,
                 LaneAssociationType::CENTER);
    init_vehicle(vehicles.vehicles_right_lane[0],
                 4,
                 110.0F,
                 30.0F,
                 LaneAssociationType::RIGHT);
    init_vehicle(vehicles.vehicles_right_lane[1],
                 5,
                 90.0F,
                 -30.0F,
                 LaneAssociationType::RIGHT);
}

void print_vehicle(const VehicleType &vehicle)
{
    std::cout << "ID: " << vehicle.id << '\n';
    std::cout << "Speed (m/s): " << vehicle.speed_mps << '\n';
    std::cout << "Distance (m): " << vehicle.distance_m << '\n';
    std::cout << "Lane: " << static_cast<std::int32_t>(vehicle.lane) << '\n';
}

void print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    print_vehicle(vehicles.vehicles_left_lane[0]);
    print_vehicle(vehicles.vehicles_left_lane[1]);
    print_vehicle(vehicles.vehicles_center_lane[0]);
    print_vehicle(vehicles.vehicles_center_lane[1]);
    print_vehicle(vehicles.vehicles_right_lane[0]);
    print_vehicle(vehicles.vehicles_right_lane[1]);
}
