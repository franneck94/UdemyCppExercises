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

}

void init_vehicles(std::string_view filepath, NeighborVehiclesType &vehicles)
{

}

void load_cycle(const std::uint32_t cycle, NeighborVehiclesType &vehicles)
{

}
