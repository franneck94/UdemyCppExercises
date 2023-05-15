#include <fstream>
#include <vector>

#include "AdTypes.hpp"
#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "DataLoaderTypes.hpp"

static auto vehicles_log_data = VehiclesLogData{};

void init_ego_vehicle(std::string_view filepath, VehicleType &ego_vehicle)
{
    std::ifstream ifs(filepath.data());
    json parsed_data = json::parse(ifs);

    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.distance_m = 0.0F;

    ego_vehicle.speed_mps = static_cast<float>(parsed_data["Speed"]);
    ego_vehicle.lane = static_cast<LaneAssociationType>(parsed_data["Lane"]);
}

void set_vehicle_start_data(VehicleType &vehicle, const VehicleLogData &vehicle_log_data)
{
    vehicle.id = vehicle_log_data.id;
    vehicle.lane = vehicle_log_data.lane;
    vehicle.distance_m = vehicle_log_data.start_distance_m;
    vehicle.speed_mps = vehicle_log_data.speeds_mps[0];
}

void init_vehicles(std::string_view filepath, NeighborVehiclesType &vehicles)
{
    std::ifstream ifs(filepath.data());
    json parsed_data = json::parse(ifs);

    for (std::size_t vehicle_idx = 0; vehicle_idx < NUM_VEHICLES; vehicle_idx++)
    {
        const auto &vehicle_data = parsed_data[std::to_string(vehicle_idx)];
        auto &vehicle_log_data = vehicles_log_data[vehicle_idx];

        const auto id = static_cast<std::int32_t>(vehicle_idx);
        const auto lane = static_cast<LaneAssociationType>(vehicle_data["Lane"]);
        const auto distance_m = static_cast<float>(vehicle_data["Distance"]);

        vehicle_log_data.id = id;
        vehicle_log_data.lane = lane;
        vehicle_log_data.start_distance_m = distance_m;
        vehicle_log_data.speeds_mps = vehicle_data["Speed"];
    }

    set_vehicle_start_data(vehicles.vehicles_left_lane[0], vehicles_log_data[0]);
    set_vehicle_start_data(vehicles.vehicles_left_lane[1], vehicles_log_data[1]);
    set_vehicle_start_data(vehicles.vehicles_center_lane[0], vehicles_log_data[2]);
    set_vehicle_start_data(vehicles.vehicles_center_lane[1], vehicles_log_data[3]);
    set_vehicle_start_data(vehicles.vehicles_right_lane[0], vehicles_log_data[4]);
    set_vehicle_start_data(vehicles.vehicles_right_lane[1], vehicles_log_data[5]);
}

void load_cycle(const std::uint32_t cycle, NeighborVehiclesType &vehicles)
{
    vehicles.vehicles_left_lane[0].speed_mps = vehicles_log_data[0].speeds_mps[cycle];
    vehicles.vehicles_left_lane[1].speed_mps = vehicles_log_data[1].speeds_mps[cycle];
    vehicles.vehicles_center_lane[0].speed_mps = vehicles_log_data[2].speeds_mps[cycle];
    vehicles.vehicles_center_lane[1].speed_mps = vehicles_log_data[3].speeds_mps[cycle];
    vehicles.vehicles_right_lane[0].speed_mps = vehicles_log_data[4].speeds_mps[cycle];
    vehicles.vehicles_right_lane[1].speed_mps = vehicles_log_data[5].speeds_mps[cycle];
}
