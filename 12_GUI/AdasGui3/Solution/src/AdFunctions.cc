#include <exception>
#include <iostream>

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "AdTypes.hpp"

float kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

float mps_to_kph(const float mps)
{
    return mps * 3.6F;
}

void decrease_speed(VehicleType &ego_vehicle)
{
    const auto decrease = ego_vehicle.speed_mps * LONGITUDINAL_DIFFERENCE_PERCENTAGE;

    if ((ego_vehicle.speed_mps - decrease) >= 0.0F)
    {
        ego_vehicle.speed_mps -= decrease;
    }
}

void longitudinal_control(const VehicleType &front_vehicle, VehicleType &ego_vehicle)
{
    const auto minimal_distance_m = mps_to_kph(ego_vehicle.speed_mps) / 2.0F;
    const auto front_distance_m = front_vehicle.distance_m;

    if (front_distance_m < minimal_distance_m)
    {
        decrease_speed(ego_vehicle);
    }
}

const std::array<VehicleType, NUM_VEHICLES_ON_LANE> &get_vehicle_array(const LaneAssociationType lane,
                                                                       const NeighborVehiclesType &vehicles)
{
    switch (lane)
    {
    case LaneAssociationType::LEFT:
    {
        return vehicles.vehicles_left_lane;
        break;
    }
    case LaneAssociationType::CENTER:
    {
        return vehicles.vehicles_center_lane;
        break;
    }
    case LaneAssociationType::RIGHT:
    {
        return vehicles.vehicles_right_lane;
        break;
    }
    default:
    {
        throw std::invalid_argument("Invalid lane data.");
        break;
    }
    }
}

void compute_future_distance(VehicleType &vehicle, const float ego_driven_distance_m, const float seconds)
{
    const auto driven_distance_m = vehicle.speed_mps * seconds;

    vehicle.distance_m += driven_distance_m - ego_driven_distance_m;
}

void compute_future_state(const VehicleType &ego_vehicle, NeighborVehiclesType &vehicles, const float seconds)
{
    const auto ego_driven_distance_m = ego_vehicle.speed_mps * seconds;

    compute_future_distance(vehicles.vehicles_left_lane[0], ego_driven_distance_m, seconds);
    compute_future_distance(vehicles.vehicles_left_lane[1], ego_driven_distance_m, seconds);
    compute_future_distance(vehicles.vehicles_center_lane[0], ego_driven_distance_m, seconds);
    compute_future_distance(vehicles.vehicles_center_lane[1], ego_driven_distance_m, seconds);
    compute_future_distance(vehicles.vehicles_right_lane[0], ego_driven_distance_m, seconds);
    compute_future_distance(vehicles.vehicles_right_lane[1], ego_driven_distance_m, seconds);
}

LaneAssociationType get_lane_change_request(const VehicleType &ego_vehicle,
                                            const NeighborVehiclesType &vehicles)
{
    const auto &ego_lane_vehicles = get_vehicle_array(ego_vehicle.lane, vehicles);
    const auto &rear_vehicle = ego_lane_vehicles[1];

    const auto minimal_distance_m = mps_to_kph(ego_vehicle.speed_mps) / 5.0F;
    const auto rear_distance_m = std::abs(rear_vehicle.distance_m);

    if (rear_distance_m < minimal_distance_m)
    {
        switch (ego_vehicle.lane)
        {
        case LaneAssociationType::RIGHT:
            [[fallthrough]];
        case LaneAssociationType::LEFT:
        {
            const auto target_lane = LaneAssociationType::CENTER;
            const auto &center_vehicles = get_vehicle_array(target_lane, vehicles);

            const auto abs_front_center_distance_m = std::abs(center_vehicles[0].distance_m);
            const auto abs_rear_center_distance_m = std::abs(center_vehicles[1].distance_m);

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

            const auto &right_vehicles = get_vehicle_array(target_lane, vehicles);

            const auto abs_front_right_distance_m = std::abs(right_vehicles[0].distance_m);
            const auto abs_rear_right_distance_m = std::abs(right_vehicles[1].distance_m);

            if ((abs_front_right_distance_m > minimal_distance_m) &&
                (abs_rear_right_distance_m > minimal_distance_m))
            {
                return target_lane;
            }

            target_lane = LaneAssociationType::LEFT;
            const auto &left_vehicles = get_vehicle_array(target_lane, vehicles);

            const auto abs_front_left_distance_m = std::abs(left_vehicles[0].distance_m);
            const auto abs_rear_left_distance_m = std::abs(left_vehicles[1].distance_m);

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


bool lateral_control(const LaneAssociationType lane_change_request, VehicleType &ego_vehicle)
{
    if (lane_change_request == ego_vehicle.lane)
    {
        return false;
    }

    ego_vehicle.lane = lane_change_request;

    return true;
}
