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
#include "RenderTypes.hpp"
#include "Units.hpp"

namespace
{
constexpr auto NUM_LANES = std::size_t{4};
static constexpr auto LANE_NAMES = std::array<const char *, NUM_LANES>{
    "Left",
    "Center",
    "Right",
    "None",
};

constexpr auto NUM_OBJECT_NAMES = std::size_t{4};
static constexpr auto OBJECT_NAMES = std::array<const char *, NUM_OBJECT_NAMES>{
    "Car",
    "Truck",
    "Motorbike",
    "None",
};

constexpr auto NUM_VALUES = std::size_t{7};
static constexpr auto VALUE_NAMES = std::array<const char *, NUM_VALUES>{
    "long_velocity_mps",
    "lat_velocity_mps",
    "velocity_mps",
    "acceleration_mps2",
    "heading_deg",
    "rel_velocity_mps",
    "rel_acceleration_mps2",
};

static constexpr auto TABLE_ROWS = MAX_NUM_VEHICLES + 1U;
static auto PLOT_VEHICLE_FLAGS = std::array<bool, TABLE_ROWS>{true, true, true, true, true, true, true};

static constexpr auto NUM_VEHICLE_CLASSES = std::size_t{3};
static const auto VEHICLE_COLORS =
    std::array<ImVec4, NUM_VEHICLE_CLASSES>{BLUE_MARKER, RED_MARKER, GREEN_MARKER};

static constexpr auto NUM_LANE_CLASSES = std::size_t{4};
static const auto LANE_CLASS_COLORS =
    std::array<ImVec4, NUM_LANE_CLASSES>{GREEN_BACKGROUND, BLUE_BACKGROUND, BLUE_BACKGROUND, RED_BACKGROUND};
} // namespace

void plot_vehicle_marker(const VehicleInformationType &vehicle, const ImVec4 &color, std::string_view label)
{
    constexpr auto num_points = size_t{2};
    constexpr auto scaling = ((2.0F * VIEW_RANGE_M) / (2.0F * LATERAL_RANGE_M));

    const auto height_offset = (vehicle.height_m / 2.0F);
    const auto width_offset = (vehicle.width_m / 4.0F);

    auto xs = std::array<float, num_points>{vehicle.long_distance_m - height_offset,
                                            vehicle.long_distance_m + height_offset};
    auto ys1 = std::array<float, num_points>{vehicle.lat_distance_m + width_offset,
                                             vehicle.lat_distance_m + width_offset};
    auto ys2 = std::array<float, num_points>{vehicle.lat_distance_m - width_offset,
                                             vehicle.lat_distance_m - width_offset};

    const auto rad = (vehicle.heading_deg / scaling) * deg_to_rad(vehicle.heading_deg);
    const auto cx = (xs[0] + xs[1]) / 2.0F;
    const auto cy = (ys1[0] + ys2[0]) / 2.0F;

    const auto p1 = rotate_point(rad, cx, cy, xs[0], ys1[0]);
    const auto p2 = rotate_point(rad, cx, cy, xs[1], ys1[1]);
    const auto p3 = rotate_point(rad, cx, cy, xs[0], ys2[0]);
    const auto p4 = rotate_point(rad, cx, cy, xs[1], ys2[1]);

    xs[0] = p1.first;
    xs[1] = p2.first;
    ys1[0] = p1.second;
    ys1[1] = p2.second;
    ys2[0] = p3.second;
    ys2[1] = p4.second;

    ImPlot::SetNextFillStyle(color);
    ImPlot::PlotShaded(label.data(), xs.data(), ys1.data(), ys2.data(), num_points);
}

void plot_lanes_straight_solid_line(const Polynomial3rdDegreeType &polynomial,
                                    const float start_m,
                                    const float end_m)
{
    constexpr auto num_rear_points = std::size_t{2};

    const auto x_rear = std::array<float, num_rear_points>{start_m, end_m};
    const auto y_rear = std::array<float, num_rear_points>{polynomial.d, polynomial.d};
    ImPlot::SetNextLineStyle(WHITE_MARKER, REAR_LINE_WIDTH);
    ImPlot::PlotLine("straight_solid_line", x_rear.data(), y_rear.data(), num_rear_points);
}

void plot_lanes_polynomial_solid_line(const Polynomial3rdDegreeType &polynomial,
                                      const float start_m,
                                      const float end_m)
{
    constexpr auto num_front_points = std::size_t{100};
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
    constexpr auto num_points = std::size_t{2};
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
    if (LaneClassType::NONE == lane.lane_class)
    {
        return;
    }

    constexpr auto num_points = size_t{2};
    const auto color = LANE_CLASS_COLORS[static_cast<std::int32_t>(lane.lane_class)];

    const auto offset_m = lane.right_polynomial.d;
    const auto min_view_range = std::min(lane.left_view_range_m, lane.right_view_range_m);

    const auto xs = std::array<float, num_points>{0.0F, min_view_range};
    const auto ys = std::array<float, num_points>{lane.left_polynomial.d, lane.left_polynomial.d};

    ImPlot::SetNextFillStyle(color);
    ImPlot::PlotShaded("label", xs.data(), ys.data(), num_points, offset_m);
}

void plot_lanes_vehicles(const std::array<VehicleInformationType, MAX_NUM_VEHICLES> &vehicles)
{
    for (std::size_t i = 0; i < MAX_NUM_VEHICLES; i++)
    {
        if (false == PLOT_VEHICLE_FLAGS[i + 1U])
        {
            continue;
        }

        const auto xs = vehicles[i].long_distance_m;
        const auto ys = vehicles[i].lat_distance_m;

        if (ObjectClassType::NONE == vehicles[i].object_class)
        {
            return;
        }

        const auto color = VEHICLE_COLORS[static_cast<std::int32_t>(vehicles[i].object_class)];

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
    if (false == PLOT_VEHICLE_FLAGS[0])
    {
        return;
    }

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
        ImPlot::SetupAxes("Rel-LongDist-(m)", "Rel-LatDist-(m)", ImPlotAxisFlags_Lock, AXES_FLAGS);
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

template <typename T>
void plot_table_cell_value(std::string_view formatter, const T &value)
{
    ImGui::TableNextColumn();
    ImGui::Text(formatter.data(), value);
}

void plot_vehicle_in_table(const VehicleInformationType &vehicle, bool &plot_vehicle)
{
    if (ObjectClassType::NONE == vehicle.object_class)
    {
        return;
    }

    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    const auto label = std::string{"###"} + std::to_string(vehicle.id);
    ImGui::Checkbox(label.data(), &plot_vehicle);

    plot_table_cell_value("%d", vehicle.id);
    plot_table_cell_value("%s", OBJECT_NAMES[static_cast<std::int32_t>(vehicle.object_class)]);
    plot_table_cell_value("%s", LANE_NAMES[static_cast<std::int32_t>(vehicle.lane)]);
    plot_table_cell_value("%.4f", vehicle.long_distance_m);
    plot_table_cell_value("%.4f", vehicle.lat_distance_m);
    plot_table_cell_value("%.4f", vehicle.velocity_mps);
    plot_table_cell_value("%.4f", vehicle.long_velocity_mps);
    plot_table_cell_value("%.4f", vehicle.lat_velocity_mps);
    plot_table_cell_value("%.4f", vehicle.heading_deg);
    plot_table_cell_value("%.4f", vehicle.acceleration_mps2);
    plot_table_cell_value("%.4f", vehicle.rel_velocity_mps);
    plot_table_cell_value("%.4f", vehicle.rel_acceleration_mps2);
}

void plot_table(const VehicleInformationType &ego_vehicle, const NeighborVehiclesType &vehicles)
{
    constexpr auto num_cols = std::size_t{13};

    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES));
    ImGui::SetNextWindowSize(ImVec2(VEHICLE_TABLE_WIDTH, VEHICLE_TABLE_HEIGHT));

    if (ImGui::Begin("TableWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        if (ImGui::BeginTable("Table", num_cols, TABLE_FLAGS))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 50.0F);
            ImGui::TableSetupColumn("ID:", ImGuiTableColumnFlags_WidthFixed, 50.0F);
            ImGui::TableSetupColumn("Type:", ImGuiTableColumnFlags_WidthFixed, 100.0F);
            ImGui::TableSetupColumn("Lane:", ImGuiTableColumnFlags_WidthFixed, 100.0F);
            ImGui::TableSetupColumn("LongDist:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("LatDist:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("Velocity:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("LongVel:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("LatVel:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("HeadingDeg:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("Accel:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("RelVel:", ImGuiTableColumnFlags_WidthFixed, 145.0F);
            ImGui::TableSetupColumn("RelAccel:", ImGuiTableColumnFlags_WidthFixed, 145.0F);

            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            plot_table_cell_value("%s", "");
            plot_table_cell_value("%s", "ID:");
            plot_table_cell_value("%s", "Type:");
            plot_table_cell_value("%s", "Lane:");
            plot_table_cell_value("%s", "LongDist:");
            plot_table_cell_value("%s", "LatDist:");
            plot_table_cell_value("%s", "Velocity:");
            plot_table_cell_value("%s", "LongVel:");
            plot_table_cell_value("%s", "LatVel:");
            plot_table_cell_value("%s", "HeadingDeg:");
            plot_table_cell_value("%s", "Accel:");
            plot_table_cell_value("%s", "RelVel:");
            plot_table_cell_value("%s", "RelAccel:");

            plot_vehicle_in_table(ego_vehicle, PLOT_VEHICLE_FLAGS[0]);

            for (std::uint32_t idx = 0; idx < MAX_NUM_VEHICLES; ++idx)
            {
                plot_vehicle_in_table(vehicles[idx], PLOT_VEHICLE_FLAGS[idx + 1U]);
            }

            ImGui::EndTable();
        }

        ImGui::End();
    }
}

void plot_ego_values(const VehicleInformationType &ego_vehicle, const std::uint32_t cycle_idx)
{
    static auto num_points = std::int32_t{200};
    static ScrollingBuffer<float> data(NUM_ITERATIONS);
    static auto item_current_idx = std::size_t{0};
    const auto combo_preview_value = VALUE_NAMES[item_current_idx];
    float curr_value = 0.0F;

    ImGui::SetNextWindowPos(ImVec2(LEFT_WIDTH, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(SIDE_PLOT_WIDTH, SELECTABLE_HEIGHT));

    if (ImGui::Begin("ComboWindow", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        ImGui::SetNextItemWidth(SIDE_PLOT_WIDTH);
        if (ImGui::BeginCombo("###combo", combo_preview_value))
        {
            for (std::size_t n = 0; n < NUM_VALUES; n++)
            {
                const auto is_selected = (item_current_idx == n);
                if (ImGui::Selectable(VALUE_NAMES[n], is_selected))
                {
                    data.Erase();
                    item_current_idx = n;
                }

                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        const auto values = std::array<float, NUM_VALUES>{ego_vehicle.long_velocity_mps,
                                                          ego_vehicle.lat_velocity_mps,
                                                          ego_vehicle.velocity_mps,
                                                          ego_vehicle.acceleration_mps2,
                                                          ego_vehicle.heading_deg,
                                                          ego_vehicle.rel_velocity_mps,
                                                          ego_vehicle.rel_acceleration_mps2};
        curr_value = values[item_current_idx];

        ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(LEFT_WIDTH, SELECTABLE_HEIGHT));
    ImGui::SetNextWindowSize(ImVec2(SIDE_PLOT_WIDTH, SIDE_PLOT_HEIGHT));

    if (ImGui::Begin("PlottingWindow", nullptr, ImGuiWindowFlags_NoDecoration))
    {
        if (data.data_x.size() > 0)
        {
            if ((data.data_x.size() < static_cast<std::uint32_t>(num_points)) ||
                (data.data_x[data.last_offset] != static_cast<float>(cycle_idx)))
            {
                data.AddPoint(static_cast<float>(cycle_idx), curr_value);
            }
        }
        else
        {
            data.AddPoint(static_cast<float>(cycle_idx), curr_value);
        }

        if (ImPlot::BeginPlot(
                "Plotting",
                ImVec2{SIDE_PLOT_WIDTH, SIDE_PLOT_HEIGHT},
                (ImPlotFlags_NoTitle | ImPlotFlags_NoLegend | ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect)))
        {
            const auto start_cycle = cycle_idx > static_cast<std::uint32_t>(num_points)
                                         ? static_cast<double>(cycle_idx) - static_cast<double>(num_points)
                                         : 0.0;
            const auto end_cycle = cycle_idx < NUM_ITERATIONS ? static_cast<double>(cycle_idx)
                                                              : static_cast<double>(NUM_ITERATIONS);

            ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_None, ImPlotAxisFlags_AutoFit);
            ImPlot::SetupAxisLimits(ImAxis_X1, start_cycle, end_cycle, ImGuiCond_Always);
            ImPlot::SetupAxisLimits(ImAxis_Y1, 0.0, 100.0, ImGuiCond_Once);

            if (data.data_x.size() > 0)
            {
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 1.0F, WHITE_MARKER, 0.0F);
                ImPlot::SetNextLineStyle(ORANGE_LINE, 1.0F);
                ImPlot::PlotLine("scatterData1",
                                 data.data_x.data(),
                                 data.data_y.data(),
                                 static_cast<std::int32_t>(data.offset));
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 1.0F, WHITE_MARKER, 0.0F);
                ImPlot::SetNextLineStyle(ORANGE_LINE, 1.0F);
                ImPlot::PlotLine("scatterData2",
                                 data.data_x.data() + data.offset,
                                 data.data_y.data() + data.offset,
                                 static_cast<std::int32_t>(data.data_x.size() - data.offset));
            }

            ImPlot::EndPlot();
        }

        ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(LEFT_WIDTH, WINDOWS_HEIGHT - SLIDER_HEIGHT));
    ImGui::SetNextWindowSize(ImVec2(SIDE_PLOT_WIDTH, SLIDER_HEIGHT));

    if (ImGui::Begin("SliderWindow", nullptr, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration))
    {
        ImGui::SetNextItemWidth(SIDE_PLOT_WIDTH);
        ImGui::SliderInt("###sliderWidth",
                         &num_points,
                         2,
                         static_cast<std::int32_t>(cycle_idx),
                         nullptr,
                         ImGuiSliderFlags_AlwaysClamp);

        ImGui::End();
    }
}


void render_cycle(const VehicleInformationType &ego_vehicle,
                  const NeighborVehiclesType &vehicles,
                  const LanesInformationType &lanes,
                  const bool long_request,
                  const LaneAssociationType lat_request,
                  const std::uint32_t cycle_idx)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));

    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();

        plot_lanes(ego_vehicle, vehicles, lanes, long_request, lat_request);
        plot_table(ego_vehicle, vehicles);
        plot_ego_values(ego_vehicle, cycle_idx);

        ImGui::End();
    }
}
