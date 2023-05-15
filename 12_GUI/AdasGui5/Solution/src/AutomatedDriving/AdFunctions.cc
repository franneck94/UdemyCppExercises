#include <exception>
#include <iostream>
#include <vector>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

void decrease_speed(VehicleInformationType &ego_vehicle)
{
    const auto decrease = ego_vehicle.velocity_mps * LONGITUDINAL_DIFFERENCE_PERCENTAGE;

    if ((ego_vehicle.velocity_mps - decrease) >= 0.0F)
    {
        ego_vehicle.velocity_mps -= decrease;
    }
}

std::vector<const VehicleInformationType *> get_vehicles_on_lane(const LaneAssociationType lane,
                                                                 const NeighborVehiclesType &vehicles)
{
    std::vector<const VehicleInformationType *> lane_vehicles{};

    for (const auto &veh : vehicles)
    {
        if (lane == veh.lane)
        {
            lane_vehicles.push_back(&veh);
        }
    }


    return lane_vehicles;
}

const VehicleInformationType *get_impeding_vehicle(
    const std::vector<const VehicleInformationType *> &vehicles)
{
    float closest_distance_m = FLT_MAX;
    std::uint32_t closest_idx = static_cast<std::uint32_t>(-1);

    for (std::uint32_t idx = 0; idx < vehicles.size(); ++idx)
    {
        const auto veh = vehicles[idx];

        if (veh->long_distance_m <= 0.0F)
        {
            continue;
        }

        if (veh->long_distance_m < closest_distance_m)
        {
            closest_distance_m = veh->long_distance_m;
            closest_idx = idx;
        }
    }

    if (closest_idx != static_cast<std::uint32_t>(-1))
    {
        return vehicles[closest_idx];
    }

    return nullptr;
}

const VehicleInformationType *get_closing_vehicle(const std::vector<const VehicleInformationType *> &vehicles)
{
    float closest_distance_m = -FLT_MAX;
    std::uint32_t closest_idx = static_cast<std::uint32_t>(-1);

    for (std::uint32_t idx = 0; idx < vehicles.size(); ++idx)
    {
        const auto veh = vehicles[idx];

        if (veh->long_distance_m >= 0.0F)
        {
            continue;
        }

        if (veh->long_distance_m > closest_distance_m)
        {
            closest_distance_m = veh->long_distance_m;
            closest_idx = idx;
        }
    }

    if (closest_idx != static_cast<std::uint32_t>(-1))
    {
        return vehicles[closest_idx];
    }

    return nullptr;
}

bool get_longitudinal_request(const VehicleInformationType *const front_vehicle,
                              VehicleInformationType &ego_vehicle)
{
    if (nullptr == front_vehicle)
    {
        return false;
    }

    const auto minimal_distance_m = mps_to_kph(ego_vehicle.velocity_mps) / 2.0F;
    const auto front_distance_m = front_vehicle->long_distance_m;

    if (front_distance_m < minimal_distance_m)
    {
        return true;
    }

    return false;
}

void longitudinal_control(VehicleInformationType &ego_vehicle)
{
    decrease_speed(ego_vehicle);
}

LaneAssociationType get_lat_request(const VehicleInformationType &ego_vehicle,
                                    const NeighborVehiclesType &vehicles)
{
    const auto ego_lane_vehicles = get_vehicles_on_lane(ego_vehicle.lane, vehicles);
    const auto rear_vehicle = get_closing_vehicle(ego_lane_vehicles);

    const auto minimal_distance_m = mps_to_kph(ego_vehicle.velocity_mps) / 5.0F;
    const auto rear_distance_m = std::abs(rear_vehicle->long_distance_m);

    if (rear_distance_m < minimal_distance_m)
    {
        switch (ego_vehicle.lane)
        {
        case LaneAssociationType::RIGHT:
            [[fallthrough]];
        case LaneAssociationType::LEFT:
        {
            const auto target_lane = LaneAssociationType::CENTER;
            const auto center_vehicles = get_vehicles_on_lane(target_lane, vehicles);

            const auto abs_front_center_distance_m = std::abs(center_vehicles[0]->long_distance_m);
            const auto abs_rear_center_distance_m = std::abs(center_vehicles[1]->long_distance_m);

            if ((abs_front_center_distance_m > minimal_distance_m) &&
                (abs_rear_center_distance_m > minimal_distance_m))
            {
                return target_lane;
            }

            break;
        }
        case LaneAssociationType::CENTER:
        {
            auto target_lane = LaneAssociationType::RIGHT;

            const auto right_vehicles = get_vehicles_on_lane(target_lane, vehicles);

            const auto abs_front_right_distance_m = std::abs(right_vehicles[0]->long_distance_m);
            const auto abs_rear_right_distance_m = std::abs(right_vehicles[1]->long_distance_m);

            if ((abs_front_right_distance_m > minimal_distance_m) &&
                (abs_rear_right_distance_m > minimal_distance_m))
            {
                return target_lane;
            }

            target_lane = LaneAssociationType::LEFT;
            const auto left_vehicles = get_vehicles_on_lane(target_lane, vehicles);

            const auto abs_front_left_distance_m = std::abs(left_vehicles[0]->long_distance_m);
            const auto abs_rear_left_distance_m = std::abs(left_vehicles[1]->long_distance_m);

            if ((abs_front_left_distance_m > minimal_distance_m) &&
                (abs_rear_left_distance_m > minimal_distance_m))
            {
                return target_lane;
            }

            break;
        }
        default:
        {
            break;
        }
        }
    }

    return ego_vehicle.lane;
}


bool lateral_control(const LaneAssociationType lat_request, VehicleInformationType &ego_vehicle)
{
    if (lat_request == ego_vehicle.lane)
    {
        return false;
    }

    ego_vehicle.lane = lat_request;

    return true;
}
