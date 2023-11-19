# Exercise

Implement the following functions:

```cpp
void print_scene(const VehicleType &ego_vehicle,
                 const NeighborVehiclesType &vehicles);

void compute_future_state(const VehicleType &ego_vehicle,
                          NeighborVehiclesType &vehicles,
                          const float seconds);
```

- print_scene
  - Output the vehicles at their postion (regarding the relative distance and lane)
  - Every *row* of the console output has a size of 20 meters (this should be modifiable)

![vehicle](../../media/vehicle.png)

- compute_future_state
  - Compute the position of a vehicles in **n** seconds
  - Assuming the vehicle has constant velocity (no change in the speed)
  - Note: The future distance of a vehicle is dependent on the ego vehicle

Example:

Other Vehicle $V_1$

- Distance = $100 m$
- Speed = $30 \frac{m}{s}$

Ego Vehicle $E$

- Speed = $25 \frac{m}{s}$

Predict the distance in 1 second

- $V_1$ will drive $1 s * 30 \frac{m}{s} = 30 m$ meters.
- $E$ will drive $1 s * 25 \frac{m}{s} = 25 m$ meters.
- The new relative distance will be $100 + (30 - 25) = 95$

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

    print_scene(ego_vehicle, vehicles);

    std::cout << "Compute forward (1sec)?: ";
    auto Input = char{};
    std::cin >> Input;

    while (Input == 'y')
    {
        compute_future_state(ego_vehicle, vehicles, 1);
        print_scene(ego_vehicle, vehicles);

        std::cout << "Compute forward (1sec)?: ";
        std::cin >> Input;
    }

    return 0;
}
```
