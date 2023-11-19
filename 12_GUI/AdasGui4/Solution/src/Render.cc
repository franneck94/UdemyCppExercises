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

void render_cycle(const VehicleType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));

    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        plot_lanes(ego_vehicle, vehicles, lanes);
        plot_table(ego_vehicle, vehicles);
        ImGui::End();
    }
}

void plot_lanes_straight_solid_line(const Polynomial3rdDegreeType &polynomial,
                                    std::string_view label,
                                    const float start_m,
                                    const float end_m)
{
    const auto num_rear_points = std::size_t{2};

    const auto x_rear = std::array<float, num_rear_points>{start_m, end_m};
    const auto y_rear = std::array<float, num_rear_points>{polynomial.d, polynomial.d};
    ImPlot::SetNextLineStyle(WHITE, REAR_LINE_WIDTH);
    const auto rear_label = label.data() + std::string{"###rear"};
    ImPlot::PlotLine(rear_label.data(), x_rear.data(), y_rear.data(), num_rear_points);
}

void plot_lanes_polynomial_solid_line(const Polynomial3rdDegreeType &polynomial,
                                      std::string_view label,
                                      const float start_m,
                                      const float end_m)
{
    const auto num_front_points = std::size_t{100};
    const auto range_m = std::abs(end_m - start_m);
    const auto slice_length_m = range_m / static_cast<float>(num_front_points);

    auto xs = std::array<float, num_front_points>{};
    auto ys = std::array<float, num_front_points>{};

    for (std::int32_t slice_idx = 0; slice_idx < num_front_points; ++slice_idx)
    {
        const auto x = static_cast<float>(slice_idx) * slice_length_m;
        xs[slice_idx] = x;
        ys[slice_idx] = polynomial(x);
    }

    ImPlot::SetNextLineStyle(WHITE, LINE_WIDTH);
    const auto front_label = label.data() + std::string{"###front"};
    ImPlot::PlotLine(front_label.data(), xs.data(), ys.data(), num_front_points);
}

void plot_lanes_polynomial_dashed_line(const Polynomial3rdDegreeType &polynomial,
                                       std::string_view label,
                                       const float start_m,
                                       const float end_m)
{
    const auto num_points = std::size_t{2};
    const auto range_m = std::abs(end_m - start_m);
    const auto num_slices = static_cast<std::uint32_t>(range_m / SLICE_LENGTH_M);

    for (std::uint32_t slice_idx = 0; slice_idx < num_slices; slice_idx++)
    {
        const auto slice_m = static_cast<float>(slice_idx);

        const auto xs = std::array<float, num_points>{start_m + slice_m * SLICE_LENGTH_M,
                                                      start_m + slice_m * SLICE_LENGTH_M + DASHED_LENGTH_M};
        const auto ys = std::array<float, num_points>{polynomial(xs[0]), polynomial(xs[1])};

        ImPlot::SetNextLineStyle(WHITE, LINE_WIDTH);
        ImPlot::PlotLine(label.data(), xs.data(), ys.data(), num_points);
    }
}

void plot_lane_boundary(const Polynomial3rdDegreeType &polynomial,
                        const LaneBoundaryType boundary_type,
                        const float view_range_m,
                        std::string_view label)
{
    plot_lanes_straight_solid_line(polynomial, label, -VIEW_RANGE_M, 0.0F);

    switch (boundary_type)
    {
    case LaneBoundaryType::DASHED:
    {
        plot_lanes_polynomial_dashed_line(polynomial, label, 0.0F, view_range_m);
        break;
    }
    case LaneBoundaryType::SOLID:
    {
        plot_lanes_polynomial_solid_line(polynomial, label, 0.0F, view_range_m);
        break;
    }
    default:
    {
        return;
    }
    }
}

void plot_lanes_vehicles(const LaneInformationType &lane,
                         const std::array<VehicleType, NUM_VEHICLES_ON_LANE> &vehicles,
                         const std::array<std::string_view, NUM_VEHICLES_ON_LANE> &labels)
{
    const auto num_elements = std::size_t{1};

    for (std::size_t i = 0; i < NUM_VEHICLES_ON_LANE; i++)
    {
        const auto xs = vehicles[i].distance_m;
        const auto ys = lane.get_lateral_position(xs);

        ImPlot::SetNextMarkerStyle(VEHICLE_MARKER, VEHICLE_SCATTER_SIZE);
        ImPlot::PlotScatter(labels[i].data(), &xs, &ys, num_elements);
    }
}

void plot_lanes_ego_vehicle(const LanesInformationType &lanes,
                            const VehicleType &ego_vehicle,
                            std::string_view label)
{
    const auto num_elements = std::size_t{1};
    auto lateral_distance_m = 0.0F;

    ImPlot::SetNextMarkerStyle(VEHICLE_MARKER, VEHICLE_SCATTER_SIZE);

    switch (ego_vehicle.lane)
    {
    case LaneAssociationType::LEFT:
    {
        lateral_distance_m = lanes.left_lane.get_lateral_position(ego_vehicle.distance_m);
        break;
    }
    case LaneAssociationType::CENTER:
    {
        lateral_distance_m = lanes.center_lane.get_lateral_position(ego_vehicle.distance_m);
        break;
    }
    case LaneAssociationType::RIGHT:
    {
        lateral_distance_m = lanes.right_lane.get_lateral_position(ego_vehicle.distance_m);
        break;
    }
    case LaneAssociationType::NONE:
    default:
    {
        return;
        break;
    }
    }

    ImPlot::PlotScatter(label.data(), &ego_vehicle.distance_m, &lateral_distance_m, num_elements);
}

void plot_lanes(const VehicleType &ego_vehicle,
                const NeighborVehiclesType &vehicles,
                const LanesInformationType &lanes)
{
    if (ImPlot::BeginPlot("Lanes", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes("Rel. LongDist. (m)", "Rel. LatDist. (m)", ImPlotAxisFlags_Lock, AXES_FLAGS);
        ImPlot::SetupAxisLimits(ImAxis_X1, -VIEW_RANGE_M, VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1,
                                LEFT_LEFT_BORDER - 3.0F,
                                RIGHT_RIGHT_BORDER + 3.0F,
                                ImGuiCond_Always);

        plot_lane_boundary(lanes.left_lane.left_polynomial,
                           lanes.left_lane.left_boundary_type,
                           lanes.left_lane.left_view_range_m,
                           "LeftLeftBorder");
        plot_lane_boundary(lanes.center_lane.left_polynomial,
                           lanes.center_lane.left_boundary_type,
                           lanes.center_lane.left_view_range_m,
                           "CenterLeftBorder");
        plot_lane_boundary(lanes.center_lane.right_polynomial,
                           lanes.center_lane.right_boundary_type,
                           lanes.center_lane.right_view_range_m,
                           "CenterRightBorder");
        plot_lane_boundary(lanes.right_lane.right_polynomial,
                           lanes.right_lane.right_boundary_type,
                           lanes.right_lane.right_view_range_m,
                           "RightRightBorder");

        plot_lanes_vehicles(lanes.left_lane, vehicles.vehicles_left_lane, {"LF", "LR"});
        plot_lanes_vehicles(lanes.center_lane, vehicles.vehicles_center_lane, {"CF", "CR"});
        plot_lanes_vehicles(lanes.right_lane, vehicles.vehicles_right_lane, {"RF", "RR"});
        plot_lanes_ego_vehicle(lanes, ego_vehicle, "Ego");

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
