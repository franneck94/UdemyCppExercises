#pragma once

#include "AdTypes.hpp"
#include "DataLoaderTypes.hpp"

void compute_ego_kinematics(EgoVehicleLogData &ego_vehicle_log_data);

void compute_vehicle_kinematics(const EgoVehicleLogData &ego_vehicle_log_data,
                                VehicleLogData &vehicle_log_data);
