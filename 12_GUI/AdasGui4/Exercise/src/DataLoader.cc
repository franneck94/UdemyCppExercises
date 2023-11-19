#include <fstream>
#include <vector>

#include "AdTypes.hpp"
#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
#include "DataLoaderTypes.hpp"

static auto vehicles_log_data = VehiclesLogData{};
static auto lanes_log_data = LanesLogData{};

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

void load_cycle(const std::uint32_t cycle, NeighborVehiclesType &vehicles, LanesInformationType &lanes)
{
    vehicles.vehicles_left_lane[0].speed_mps = vehicles_log_data[0].speeds_mps[cycle];
    vehicles.vehicles_left_lane[1].speed_mps = vehicles_log_data[1].speeds_mps[cycle];
    vehicles.vehicles_center_lane[0].speed_mps = vehicles_log_data[2].speeds_mps[cycle];
    vehicles.vehicles_center_lane[1].speed_mps = vehicles_log_data[3].speeds_mps[cycle];
    vehicles.vehicles_right_lane[0].speed_mps = vehicles_log_data[4].speeds_mps[cycle];
    vehicles.vehicles_right_lane[1].speed_mps = vehicles_log_data[5].speeds_mps[cycle];

    lanes.left_lane.left_polynomial = lanes_log_data[0].left_polynomials[cycle];
    lanes.left_lane.right_polynomial = lanes_log_data[0].right_polynomials[cycle];
    lanes.left_lane.left_view_range_m = lanes_log_data[0].left_view_ranges_m[cycle];
    lanes.left_lane.left_boundary_type = lanes_log_data[0].left_boundary_types[cycle];
    lanes.left_lane.right_view_range_m = lanes_log_data[0].right_view_ranges_m[cycle];
    lanes.left_lane.right_boundary_type = lanes_log_data[0].right_boundary_types[cycle];

    lanes.center_lane.left_polynomial = lanes_log_data[1].left_polynomials[cycle];
    lanes.center_lane.right_polynomial = lanes_log_data[1].right_polynomials[cycle];
    lanes.center_lane.left_view_range_m = lanes_log_data[1].left_view_ranges_m[cycle];
    lanes.center_lane.left_boundary_type = lanes_log_data[1].left_boundary_types[cycle];
    lanes.center_lane.right_view_range_m = lanes_log_data[1].right_view_ranges_m[cycle];
    lanes.center_lane.right_boundary_type = lanes_log_data[1].right_boundary_types[cycle];

    lanes.right_lane.left_polynomial = lanes_log_data[2].left_polynomials[cycle];
    lanes.right_lane.right_polynomial = lanes_log_data[2].right_polynomials[cycle];
    lanes.right_lane.left_view_range_m = lanes_log_data[2].left_view_ranges_m[cycle];
    lanes.right_lane.left_boundary_type = lanes_log_data[2].left_boundary_types[cycle];
    lanes.right_lane.right_view_range_m = lanes_log_data[2].right_view_ranges_m[cycle];
    lanes.right_lane.right_boundary_type = lanes_log_data[2].right_boundary_types[cycle];
}

void get_lane_border_data(const std::uint32_t i, const size_t lane_idx, const json &parsed_data)
{
    const auto i_str = std::to_string(i);
    const auto lane_str = std::to_string(lane_idx);

    lanes_log_data[lane_idx].left_polynomials[i].a = parsed_data[lane_str]["0"][i_str]["p"]["a"];
    lanes_log_data[lane_idx].left_polynomials[i].b = parsed_data[lane_str]["0"][i_str]["p"]["b"];
    lanes_log_data[lane_idx].left_polynomials[i].c = parsed_data[lane_str]["0"][i_str]["p"]["c"];
    lanes_log_data[lane_idx].left_polynomials[i].d = parsed_data[lane_str]["0"][i_str]["p"]["d"];
    lanes_log_data[lane_idx].left_view_ranges_m[i] = parsed_data[lane_str]["0"][i_str]["r"];
    lanes_log_data[lane_idx].left_boundary_types[i] = parsed_data[lane_str]["0"][i_str]["t"];

    lanes_log_data[lane_idx].right_polynomials[i].a = parsed_data[lane_str]["1"][i_str]["p"]["a"];
    lanes_log_data[lane_idx].right_polynomials[i].b = parsed_data[lane_str]["1"][i_str]["p"]["b"];
    lanes_log_data[lane_idx].right_polynomials[i].c = parsed_data[lane_str]["1"][i_str]["p"]["c"];
    lanes_log_data[lane_idx].right_polynomials[i].d = parsed_data[lane_str]["1"][i_str]["p"]["d"];
    lanes_log_data[lane_idx].right_view_ranges_m[i] = parsed_data[lane_str]["1"][i_str]["r"];
    lanes_log_data[lane_idx].right_boundary_types[i] = parsed_data[lane_str]["1"][i_str]["t"];
}

void set_lanes_start_data(LaneInformationType &lane, const size_t lane_idx)
{
    lane.left_polynomial = lanes_log_data[lane_idx].left_polynomials[0];
    lane.left_view_range_m = lanes_log_data[lane_idx].left_view_ranges_m[0];
    lane.left_boundary_type = lanes_log_data[lane_idx].left_boundary_types[0];

    lane.right_polynomial = lanes_log_data[lane_idx].right_polynomials[0];
    lane.right_view_range_m = lanes_log_data[lane_idx].right_view_ranges_m[0];
    lane.right_boundary_type = lanes_log_data[lane_idx].right_boundary_types[0];
}

void init_lanes(std::string_view filepath, LanesInformationType &lanes)
{
    std::ifstream ifs(filepath.data());
    json parsed_data = json::parse(ifs);

    for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        get_lane_border_data(i, 0, parsed_data);
        get_lane_border_data(i, 0, parsed_data);
        get_lane_border_data(i, 1, parsed_data);
        get_lane_border_data(i, 1, parsed_data);
        get_lane_border_data(i, 2, parsed_data);
        get_lane_border_data(i, 2, parsed_data);
    }

    set_lanes_start_data(lanes.left_lane, 0);
    set_lanes_start_data(lanes.center_lane, 1);
    set_lanes_start_data(lanes.right_lane, 2);
}
