# Exercise

Update the following functions:

```cpp
void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);
```

- print_scene: Such that the ego vehicle can be displayed on every lane not only the center lane

Implement the following functions:

```cpp
const VehicleType *get_vehicle_array(const LaneAssociationType lane, const NeighborVehiclesType &vehicles);
```

- get_vehicle_array
  - Return the vehicle array for a certain lane

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

        compute_future_state(ego_vehicle, vehicles, 0.100F);
        print_scene(ego_vehicle, vehicles);

        const auto ego_lane_vehicles = get_vehicle_array(ego_vehicle.lane, vehicles);
        longitudinal_control(ego_lane_vehicles[0], ego_vehicle);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
```
