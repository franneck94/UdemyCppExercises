#include <chrono>
#include <cstring>
#include <iostream>
#include <numeric>
#include <thread>

#include "AdFunctions.hpp"
#include "AdTypes.hpp"

#include "utils.hpp"

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
        longitudinal_control(vehicles.vehicles_center_lane[0], ego_vehicle);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
