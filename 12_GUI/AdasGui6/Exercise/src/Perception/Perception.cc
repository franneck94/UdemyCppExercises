#include <algorithm>
#include <array>
#include <iostream>

#include "AdTypes.hpp"
#include "DataLoaderTypes.hpp"
#include "Perception.hpp"
#include "Units.hpp"

void compute_ego_kinematics(EgoVehicleLogData &ego_data)
{
    compute_velocities(ego_data.long_velocities_mps, ego_data.lat_velocities_mps, ego_data.velocities_mps);
    compute_heading_degrees(ego_data.long_velocities_mps, ego_data.lat_velocities_mps, ego_data.heading_degs);
    compute_accelerations(ego_data.velocities_mps, CYCLE_TIME_MS, ego_data.accelerations_mps2);
}

void compute_vehicle_kinematics(const EgoVehicleLogData &ego_data, VehicleLogData &vehicle_data)
{
    compute_velocities(vehicle_data.long_velocities_mps,
                       vehicle_data.lat_velocities_mps,
                       vehicle_data.velocities_mps);
    compute_heading_degrees(vehicle_data.long_velocities_mps,
                            vehicle_data.lat_velocities_mps,
                            vehicle_data.heading_degs);
    compute_accelerations(vehicle_data.velocities_mps, CYCLE_TIME_MS, vehicle_data.accelerations_mps2);
    compute_rel_velocities(vehicle_data.velocities_mps,
                           ego_data.velocities_mps,
                           vehicle_data.rel_velocities_mps);
    compute_rel_accelerations(vehicle_data.accelerations_mps2,
                              ego_data.accelerations_mps2,
                              vehicle_data.rel_accelerations_mps2);
}
