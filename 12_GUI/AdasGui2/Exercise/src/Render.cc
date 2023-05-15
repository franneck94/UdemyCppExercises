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

void plot_vehicle_in_table(const VehicleType &vehicle, std::string_view vehicle_name)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%s", vehicle_name.data());
    ImGui::TableNextColumn();
    ImGui::Text("%d", vehicle.id);
    ImGui::TableNextColumn();
    ImGui::Text("%d", static_cast<std::int32_t>(vehicle.lane));
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.distance_m);
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.speed_mps);
}

void plot_table(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    const auto num_cols = std::size_t{5};

    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES));
    ImGui::SetNextWindowSize(ImVec2(VEHICLE_TABLE_WIDTH, VEHICLE_TABLE_HEIGHT));

    if (ImGui::Begin("TableWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        if (ImGui::BeginTable("Table", num_cols, TABLE_FLAGS))
        {
            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            ImGui::TableNextColumn();
            ImGui::Text("Pos:");
            ImGui::TableNextColumn();
            ImGui::Text("ID:");
            ImGui::TableNextColumn();
            ImGui::Text("Lane:");
            ImGui::TableNextColumn();
            ImGui::Text("Distance:");
            ImGui::TableNextColumn();
            ImGui::Text("Speed:");

            plot_vehicle_in_table(ego_vehicle, "Ego");
            plot_vehicle_in_table(vehicles.vehicles_left_lane[0], "FrontLeft");
            plot_vehicle_in_table(vehicles.vehicles_left_lane[1], "RearLeft");
            plot_vehicle_in_table(vehicles.vehicles_center_lane[0], "FrontCenter");
            plot_vehicle_in_table(vehicles.vehicles_center_lane[1], "RearCenter");
            plot_vehicle_in_table(vehicles.vehicles_right_lane[0], "FrontRight");
            plot_vehicle_in_table(vehicles.vehicles_right_lane[1], "RearRight");

            ImGui::EndTable();
        }

        ImGui::End();
    }
}
