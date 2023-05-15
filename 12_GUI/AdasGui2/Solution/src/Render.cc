#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>

#include "imgui.h"
#include "implot.h"

#include "DataLoader.hpp"
#include "DataLoaderConstants.hpp"
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

void plot_lanes_solid_line(const float border_y, std::string_view label)
{
    const auto num_points = std::size_t{2};
    const float xs[num_points] = {-VIEW_RANGE_M, VIEW_RANGE_M};
    const float ys[num_points] = {border_y, border_y};

    ImPlot::SetNextLineStyle(LINE_COLOR, LINE_WIDTH);
    ImPlot::PlotLine(label.data(), xs, ys, num_points);
}

void plot_lanes_dashed_line(const float border_y, std::string_view label)
{
    const auto num_points = std::size_t{2};

    const auto num_slices = std::uint32_t{40};
    const auto slice_length_m = (2.0F * VIEW_RANGE_M) / static_cast<float>(num_slices);
    const auto empty_length_m = 2.0F;
    const auto dash_length_m = slice_length_m - empty_length_m;

    for (std::uint32_t slice_idx = 0; slice_idx < num_slices; slice_idx++)
    {
        const auto slice_m = static_cast<float>(slice_idx);

        const float xs[num_points] = {-VIEW_RANGE_M + slice_m * slice_length_m,
                                      -VIEW_RANGE_M + slice_m * slice_length_m + dash_length_m};
        const float ys[num_points] = {border_y, border_y};

        ImPlot::SetNextLineStyle(LINE_COLOR, LINE_WIDTH);
        ImPlot::PlotLine(label.data(), xs, ys, num_points);
    }
}

void plot_lanes_vehicles(const std::array<VehicleType, NUM_VEHICLES_ON_LANE> &vehicles,
                         const std::array<std::string_view, NUM_VEHICLES_ON_LANE> &labels,
                         const float offset_y)
{
    const auto num_elements = std::size_t{1};
    const auto ys_front = offset_y;

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        const auto xs_front = vehicles[i].distance_m;

        ImPlot::SetNextMarkerStyle(VEHICLE_MARKER, VEHICLE_SCATTER_SIZE);
        ImPlot::PlotScatter(labels[i].data(), &xs_front, &ys_front, num_elements);
    }
}

void plot_lanes_ego_vehicle(const VehicleType &ego_vehicle, std::string_view label)
{
    const auto num_elements = std::size_t{1};

    ImPlot::SetNextMarkerStyle(VEHICLE_MARKER, VEHICLE_SCATTER_SIZE);

    switch (ego_vehicle.lane)
    {
    case LaneAssociationType::LEFT:
    {
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &LEFT_LANE_OFFSET_M, num_elements);
        break;
    }
    case LaneAssociationType::CENTER:
    {
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &CENTER_LANE_OFFSET_M, num_elements);
        break;
    }
    case LaneAssociationType::RIGHT:
    {
        ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &RIGHT_LANE_OFFSET_M, num_elements);
        break;
    }
    case LaneAssociationType::NONE:
    default:
    {
        break;
    }
    }
}

void plot_lanes(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    if (ImPlot::BeginPlot("Lanes", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes("Rel. LongDist. (m)", "Rel. LatDist. (m)", ImPlotAxisFlags_Lock, AXES_FLAGS);
        ImPlot::SetupAxisLimits(ImAxis_X1, -VIEW_RANGE_M, VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1,
                                LEFT_LEFT_BORDER - 0.05F,
                                RIGHT_RIGHT_BORDER + 0.05,
                                ImGuiCond_Always);

        plot_lanes_solid_line(LEFT_LEFT_BORDER, "LeftLeftBorder");
        plot_lanes_dashed_line(CENTER_LEFT_BORDER, "CenterLeftBorder");
        plot_lanes_dashed_line(CENTER_RIGHT_BORDER, "CenterRightBorder");
        plot_lanes_solid_line(RIGHT_RIGHT_BORDER, "RightRightBorder");

        plot_lanes_vehicles(vehicles.vehicles_left_lane, {"LF", "LR"}, LEFT_LANE_OFFSET_M);
        plot_lanes_vehicles(vehicles.vehicles_center_lane, {"CF", "CR"}, CENTER_LANE_OFFSET_M);
        plot_lanes_vehicles(vehicles.vehicles_right_lane, {"RF", "RR"}, RIGHT_LANE_OFFSET_M);
        plot_lanes_ego_vehicle(ego_vehicle, "Ego");

        ImPlot::EndPlot();
    }
}

void plot_vehicle_in_table(const VehicleType &vehicle, std::string_view label)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%s", label.data());
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
