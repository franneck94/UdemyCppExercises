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
#include "Units.hpp"

void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes,
                  const bool long_request,
                  const LaneAssociationType lat_request)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));

    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        plot_lanes(ego_vehicle, vehicles, lanes, long_request, lat_request);
        plot_table(ego_vehicle, vehicles);
        ImGui::End();
    }
}

void plot_shaded_rect(const float x1,
                      const float x2,
                      const float y1,
                      const float y2,
                      const float y3,
                      const float y4,
                      std::string_view label)
{
    const auto num_points = size_t{2};

    const auto xs = std::array<float, num_points>{x1, x2};
    const auto ys1 = std::array<float, num_points>{y1, y2};
    const auto ys2 = std::array<float, num_points>{y3, y4};

    ImPlot::PlotShaded(label.data(), xs.data(), ys1.data(), ys2.data(), num_points);
}

void plot_vehicle_marker(const VehicleInformationType &vehicle, const ImVec4 &color, std::string_view label)
{
    if (vehicle.id == NONE_VEHICLE_ID)
    {
        return;
    }

    const auto height_offset = (vehicle.height_m / 2.0F);
    const auto width_offset = (vehicle.width_m / 5.0F);

    const auto x1 = vehicle.long_distance_m - height_offset;
    const auto x2 = vehicle.long_distance_m + height_offset;
    const auto y1 = vehicle.lat_distance_m + width_offset;
    const auto y2 = vehicle.lat_distance_m + width_offset;
    const auto y3 = vehicle.lat_distance_m - width_offset;
    const auto y4 = vehicle.lat_distance_m - width_offset;

    ImPlot::SetNextFillStyle(color);
    plot_shaded_rect(x1, x2, y1, y2, y3, y4, label);
}

void plot_lanes_straight_solid_line(const Polynomial3rdDegreeType &polynomial,
                                    const float start_m,
                                    const float end_m)
{
    const auto num_rear_points = std::size_t{2};

    const auto x_rear = std::array<float, num_rear_points>{start_m, end_m};
    const auto y_rear = std::array<float, num_rear_points>{polynomial.d, polynomial.d};
    ImPlot::SetNextLineStyle(WHITE_MARKER, REAR_LINE_WIDTH);
    ImPlot::PlotLine("straight_solid_line", x_rear.data(), y_rear.data(), num_rear_points);
}

void plot_lanes_polynomial_solid_line(const Polynomial3rdDegreeType &polynomial,
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

    ImPlot::SetNextLineStyle(WHITE_MARKER, LINE_WIDTH);
    ImPlot::PlotLine("###polynomial_solid_line", xs.data(), ys.data(), num_front_points);
}

void plot_lanes_polynomial_dashed_line(const Polynomial3rdDegreeType &polynomial,
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

        ImPlot::SetNextLineStyle(WHITE_MARKER, LINE_WIDTH);
        ImPlot::PlotLine("###polynomial_dashed_line", xs.data(), ys.data(), num_points);
    }
}

void plot_lane_boundary(const Polynomial3rdDegreeType &polynomial,
                        const LaneBoundaryType boundary_type,
                        const float view_range_m,
                        const LaneClassType lane_class)
{
    if (LaneClassType::NONE == lane_class)
    {
        return;
    }

    plot_lanes_straight_solid_line(polynomial, -VIEW_RANGE_M, 0.0F);

    switch (boundary_type)
    {
    case LaneBoundaryType::DASHED:
    {
        plot_lanes_polynomial_dashed_line(polynomial, 0.0F, view_range_m);
        break;
    }
    case LaneBoundaryType::SOLID:
    {
        plot_lanes_polynomial_solid_line(polynomial, 0.0F, view_range_m);
        break;
    }
    default:
    {
        return;
    }
    }
}

void plot_lane_class(const LaneInformationType &lane)
{
    auto color = ImVec4{};

    switch (lane.lane_class)
    {
    case LaneClassType::NORMAL:
    {
        color = GREEN_BACKGROUND;
        break;
    }
    case LaneClassType::ACCELERATION:
    case LaneClassType::DECELERATION:
    {
        color = BLUE_BACKGROUND;
        break;
    }
    case LaneClassType::HARD_SHOULDER:
    {
        color = RED_BACKGROUND;
        break;
    }
    default:
    {
        return;
    }
    }

    const auto min_view_range = std::min(lane.left_view_range_m, lane.right_view_range_m);

    const auto x1 = 0.0F;
    const auto x2 = min_view_range;
    const auto y1 = lane.right_polynomial.d;
    const auto y2 = lane.right_polynomial.d;
    const auto y3 = lane.left_polynomial.d;
    const auto y4 = lane.left_polynomial.d;

    ImPlot::SetNextFillStyle(color);
    plot_shaded_rect(x1, x2, y1, y2, y3, y4, "###lane");
}

void plot_lanes_vehicles(const std::array<VehicleInformationType, MAX_NUM_VEHICLES> &vehicles)
{
    for (std::size_t i = 0; i < MAX_NUM_VEHICLES; i++)
    {
        const auto xs = vehicles[i].long_distance_m;
        const auto ys = vehicles[i].lat_distance_m;

        auto color = ImVec4{};

        switch (vehicles[i].object_class)
        {
        case ObjectClassType::CAR:
        {
            color = BLUE_MARKER;
            break;
        }
        case ObjectClassType::TRUCK:
        {
            color = RED_MARKER;
            break;
        }
        case ObjectClassType::MOTORBIKE:
        {
            color = GREEN_MARKER;
            break;
        }
        case ObjectClassType::NONE:
        default:
        {
            continue;
        }
        }

        const auto label = std::string{"vehicle"} + std::to_string(i);
        plot_vehicle_marker(vehicles[i], color, label);

        const auto text = std::to_string(vehicles[i].id);
        ImPlot::PlotText(text.data(), xs, ys);
    }
}

void plot_lanes_ego_vehicle(const VehicleInformationType &ego_vehicle,
                            const bool long_request,
                            const LaneAssociationType lat_request)
{
    ImPlot::SetNextMarkerStyle(VEHICLE_MARKER, VEHICLE_SCATTER_SIZE, WHITE_MARKER);
    ImPlot::PlotScatter("ego", &ego_vehicle.long_distance_m, &ego_vehicle.lat_distance_m, 1);

    if (true == long_request)
    {
        const auto long_req_pos = ego_vehicle.long_distance_m - 2.0F;

        ImPlot::SetNextMarkerStyle(ImPlotMarker_Left, VEHICLE_SCATTER_SIZE / 1.5F, RED_MARKER);
        ImPlot::PlotScatter("longReq", &long_req_pos, &ego_vehicle.lat_distance_m, 1);
    }

    if ((LaneAssociationType::NONE == lat_request) || (lat_request == ego_vehicle.lane))
    {
        return;
    }

    const auto lat_request_int = static_cast<std::int32_t>(lat_request);
    const auto ego_lane_int = static_cast<std::int32_t>(ego_vehicle.lane);

    if (lat_request_int == ego_lane_int - 1)
    {
        const auto lat_req_pos = ego_vehicle.lat_distance_m - 0.5F;

        ImPlot::SetNextMarkerStyle(ImPlotMarker_Up, VEHICLE_SCATTER_SIZE / 1.5F, RED_MARKER);
        ImPlot::PlotScatter("latReq", &ego_vehicle.long_distance_m, &lat_req_pos, 1);
    }
    else if (lat_request_int == ego_lane_int + 1)
    {
        const auto lat_req_pos = ego_vehicle.lat_distance_m + 0.5F;

        ImPlot::SetNextMarkerStyle(ImPlotMarker_Down, VEHICLE_SCATTER_SIZE / 1.5F, RED_MARKER);
        ImPlot::PlotScatter("latReq", &ego_vehicle.long_distance_m, &lat_req_pos, 1);
    }
}

void plot_lanes(const VehicleInformationType &ego_vehicle,
                const NeighborVehiclesType &vehicles,
                const LanesInformationType &lanes,
                const bool long_request,
                const LaneAssociationType lat_request)
{
    if (ImPlot::BeginPlot("Lanes", PLOT_DIM, PLOT_FLAGS))
    {
        ImPlot::SetupAxes("Rel. LongDist. (m)", "Rel. LatDist. (m)", ImPlotAxisFlags_Lock, AXES_FLAGS);
        ImPlot::SetupAxisLimits(ImAxis_X1, -VIEW_RANGE_M, VIEW_RANGE_M, ImGuiCond_Always);
        ImPlot::SetupAxisLimits(ImAxis_Y1, -LATERAL_RANGE_M, LATERAL_RANGE_M, ImGuiCond_Always);

        plot_lane_class(lanes.left_lane);
        plot_lane_class(lanes.center_lane);
        plot_lane_class(lanes.right_lane);

        plot_lane_boundary(lanes.left_lane.left_polynomial,
                           lanes.left_lane.left_boundary_type,
                           lanes.left_lane.left_view_range_m,
                           lanes.left_lane.lane_class);
        plot_lane_boundary(lanes.center_lane.left_polynomial,
                           lanes.center_lane.left_boundary_type,
                           lanes.center_lane.left_view_range_m,
                           lanes.center_lane.lane_class);
        plot_lane_boundary(lanes.center_lane.right_polynomial,
                           lanes.center_lane.right_boundary_type,
                           lanes.center_lane.right_view_range_m,
                           lanes.center_lane.lane_class);
        plot_lane_boundary(lanes.right_lane.right_polynomial,
                           lanes.right_lane.right_boundary_type,
                           lanes.right_lane.right_view_range_m,
                           lanes.right_lane.lane_class);

        plot_lanes_vehicles(vehicles);
        plot_lanes_ego_vehicle(ego_vehicle, long_request, lat_request);

        ImPlot::EndPlot();
    }
}

void plot_vehicle_in_table(const VehicleInformationType &vehicle)
{
    if (ObjectClassType::NONE == vehicle.object_class)
    {
        return;
    }

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("%d", vehicle.id);
    ImGui::TableNextColumn();
    ImGui::Text("%s", OBJECT_NAMES[static_cast<std::uint32_t>(vehicle.object_class)]);
    ImGui::TableNextColumn();
    ImGui::Text("%s", LANE_NAMES[static_cast<std::int32_t>(vehicle.lane)]);
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.long_distance_m);
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.lat_distance_m);
    ImGui::TableNextColumn();
    ImGui::Text("%f", vehicle.velocity_mps);
}

void plot_table(const VehicleInformationType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    const auto num_cols = std::size_t{6};

    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES));
    ImGui::SetNextWindowSize(ImVec2(VEHICLE_TABLE_WIDTH, VEHICLE_TABLE_HEIGHT));

    if (ImGui::Begin("TableWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        if (ImGui::BeginTable("Table", num_cols, TABLE_FLAGS))
        {
            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            ImGui::TableNextColumn();
            ImGui::Text("ID:");
            ImGui::TableNextColumn();
            ImGui::Text("Type:");
            ImGui::TableNextColumn();
            ImGui::Text("Lane:");
            ImGui::TableNextColumn();
            ImGui::Text("Long. Dist.:");
            ImGui::TableNextColumn();
            ImGui::Text("Lat. Dist.:");
            ImGui::TableNextColumn();
            ImGui::Text("Speed:");

            plot_vehicle_in_table(ego_vehicle);

            for (std::uint32_t idx = 0; idx < MAX_NUM_VEHICLES; ++idx)
            {
                plot_vehicle_in_table(vehicles[idx]);
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }
}
