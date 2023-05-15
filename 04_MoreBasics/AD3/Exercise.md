# Exercise

Update the following functions

```cpp
void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);
```

- print_scene:
  - Update the distance slices to 10m instead of 20m
  - Add the console output of the ego vehicle speed

<img src="../../media/vehicle2.png" alt="vehicle"/>

Implement the following functions:

```cpp
float mps_to_kph(const float mps);

void decrease_speed(VehicleType &ego_vehicle);

void longitudinal_control(const VehicleType &front_vehicle, VehicleType &ego_vehicle);
```

- mps_to_kph
  - Convert the $\frac{m}{s}$ input to $\frac{km}{h}$ value
- longitudinal_control
  - The ego vehicle needs to **decrease_speed** whenever
    - There is a vehicle in front of the ego vehicle
    - and the distance is below half speed (kph, "halbe tacho")
- decrease_speed
  - Decrease the ego vehicle speed by the constant: **LONGITUDINAL_DIFFERENCE_PERCENTAGE**

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
        longitudinal_control(vehicles.vehicles_center_lane[0], ego_vehicle);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
```
