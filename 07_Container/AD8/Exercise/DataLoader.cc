#include <fstream>
#include <vector>

#include "AdTypes.hpp"
#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "DataLoaderTypes.hpp"

static VehiclesData vehicles_data = std::vector<std::vector<VehicleType>>(
    NUM_VEHICLES,
    std::vector<VehicleType>(NUM_ITERATIONS));

void init_ego_vehicle(std::string_view filepath, VehicleType &ego_vehicle)
{
    std::ifstream ifs(filepath.data());
    json parsed_data = json::parse(ifs);

    ego_vehicle.id = EGO_VEHICLE_ID;
    ego_vehicle.distance_m = 0.0F;

    ego_vehicle.speed_mps = static_cast<float>(parsed_data["Speed"]);
    ego_vehicle.lane = static_cast<LaneAssociationType>(parsed_data["Lane"]);
}

void init_vehicles(std::string_view filepath, NeighborVehiclesType &vehicles)
{
    std::ifstream ifs(filepath.data());
    json parsed_data = json::parse(ifs);

    for (std::size_t vehicle_idx = 0; vehicle_idx < NUM_VEHICLES; vehicle_idx++)
    {
        const auto &vehicle_data = parsed_data[std::to_string(vehicle_idx)];

        const auto id = static_cast<std::int32_t>(vehicle_idx);
        const auto lane =
            static_cast<LaneAssociationType>(vehicle_data["Lane"]);
        const auto distance_m = static_cast<float>(vehicle_data["Distance"]);

        for (std::size_t it = 0; it < NUM_ITERATIONS; it++)
        {
            const auto speed_mps =
                static_cast<float>(vehicle_data["Speed"][it]);

            vehicles_data[vehicle_idx][it] = {.id = id,
                                              .lane = lane,
                                              .speed_mps = speed_mps,
                                              .distance_m = distance_m};
        }
    }

    vehicles.vehicles_left_lane[0] = vehicles_data[0][0];
    vehicles.vehicles_left_lane[1] = vehicles_data[1][0];
    vehicles.vehicles_center_lane[0] = vehicles_data[2][0];
    vehicles.vehicles_center_lane[1] = vehicles_data[3][0];
    vehicles.vehicles_right_lane[0] = vehicles_data[4][0];
    vehicles.vehicles_right_lane[1] = vehicles_data[5][0];
}


void load_cycle(const std::uint32_t cycle, NeighborVehiclesType &vehicles)
{
    vehicles.vehicles_left_lane[0].speed_mps =
        vehicles_data[0][cycle].speed_mps;
    vehicles.vehicles_left_lane[1].speed_mps =
        vehicles_data[1][cycle].speed_mps;
    vehicles.vehicles_center_lane[0].speed_mps =
        vehicles_data[2][cycle].speed_mps;
    vehicles.vehicles_center_lane[1].speed_mps =
        vehicles_data[3][cycle].speed_mps;
    vehicles.vehicles_right_lane[0].speed_mps =
        vehicles_data[4][cycle].speed_mps;
    vehicles.vehicles_right_lane[1].speed_mps =
        vehicles_data[5][cycle].speed_mps;
}
