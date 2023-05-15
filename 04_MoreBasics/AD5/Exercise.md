# Exercise

Implement the following functions:

```cpp
LaneAssociationType get_lane_change_request(
    const VehicleType &ego_vehicle,
    const NeighborVehiclesType &vehicles);

bool lateral_control(
    const LaneAssociationType lane_change_request,
    VehicleType &ego_vehicle);
```

- get_lane_change_request
  - Send a lane change request to avoid a crash of the ego vehicle with the incoming (behind) vehicle
    - Change to the neighbor lane that has the largest gap (free space)
      - Only iff: $GapSize \geq (EgoSpeed(\frac{k}{h}) / 5)$
- lateral_control
  - If there is a request from **get_lane_change_request** do a lane change

## Main Function

```cpp
int main()
{
    auto ego_vehicle = VehicleType{};
    auto vehicles = NeighborVehiclesType{};

    init_ego_vehicle(ego_vehicle);
    init_vehicles(vehicles);

    print_vehicle(ego_vehicle);
    print_neighbor_vehicles(vehicles);

    std::cout << "Start simulation?: ";
    auto Input = char{};
    std::cin >> Input;

    while (true)
    {
        clear_console();

        print_scene(ego_vehicle, vehicles);
        compute_future_state(ego_vehicle, vehicles, 0.100F);

        const auto ego_lane_vehicles =
            get_vehicle_array(ego_vehicle.lane, vehicles);
        longitudinal_control(ego_lane_vehicles[0], ego_vehicle);

        const auto lane_change_request =
            get_lane_change_request(ego_vehicle, vehicles);
        const auto lane_change_executed =
            lateral_control(lane_change_request, ego_vehicle);

        if (lane_change_executed)
        {
            printf("Executed lane change!");
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
```
