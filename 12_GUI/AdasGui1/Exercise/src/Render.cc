#include <cstdint>

#include "imgui.h"
#include "implot.h"

#include "Render.hpp"
#include "RenderConstants.hpp"

void render_cycle(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));

    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        plot_lanes(ego_vehicle, vehicles);
        plot_table(ego_vehicle, vehicles);
        ImGui::End();
    }
}

void plot_lanes(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    (void)ego_vehicle; // to avoid warning
    (void)vehicles;    // to avoid warning

    if (ImPlot::BeginPlot("Lanes"))
    {

        ImPlot::EndPlot();
    }
}

void plot_table(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    (void)ego_vehicle; // to avoid warning
    (void)vehicles;    // to avoid warning

    const auto num_cols = std::size_t{ 5 };

    if (ImGui::Begin("TableWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        if (ImGui::BeginTable("Table", num_cols, TABLE_FLAGS))
        {

            ImGui::EndTable();
        }

        ImGui::End();
    }
}
