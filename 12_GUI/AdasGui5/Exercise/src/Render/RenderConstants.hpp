#pragma once

#include "imgui.h"
#include "implot.h"

/* FLAGS */
constexpr auto WINDOW_FLAGS_CLEAN = (ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
                                     ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize);
constexpr auto PLOT_FLAGS = (ImPlotFlags_NoTitle | ImPlotFlags_NoLegend);
constexpr auto AXES_FLAGS = (ImPlotAxisFlags_Lock | ImPlotAxisFlags_Invert);
constexpr auto TABLE_FLAGS = (ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuter);

/* GENERAL WINDOW SETTINGS */
constexpr auto WINDOWS_HEIGHT{900.0F};
constexpr auto WINDOWS_WIDTH{1700.0F};

/* LANE PLOT SETTINGS */
constexpr auto LANE_PLOT_HEIGHT{3.0F * 200.0F};
constexpr auto LANE_PLOT_WIDTH{WINDOWS_WIDTH - 15.0F};
constexpr auto LANE_PLOT_TOTAL_HEIGHT{LANE_PLOT_HEIGHT};
constexpr auto BELOW_LANES{LANE_PLOT_TOTAL_HEIGHT};
constexpr auto LINE_WIDTH{3.0F};
constexpr auto REAR_LINE_WIDTH{1.0F};
constexpr auto VEHICLE_MARKER{ImPlotMarker_Square};
constexpr auto MOTORBIKE_SCATTER_SIZE{10.0F};
constexpr auto VEHICLE_SCATTER_SIZE{15.0F};
constexpr auto TRUCK_SCATTER_SIZE{25.0F};
constexpr auto LEFT_LANE_OFFSET_M{-3.0F};
constexpr auto CENTER_LANE_OFFSET_M{0.0F};
constexpr auto RIGHT_LANE_OFFSET_M{3.0F};
constexpr auto SLICE_LENGTH_M{5.0F};
constexpr auto DASHED_LENGTH_M{3.0F};
constexpr auto EMPTY_LENGTH_M{SLICE_LENGTH_M - DASHED_LENGTH_M};
constexpr auto VIEW_RANGE_M{100.0F};
constexpr auto LATERAL_RANGE_M{7.5F};

const auto PLOT_DIM = ImVec2(LANE_PLOT_WIDTH, LANE_PLOT_HEIGHT);
const auto WHITE_MARKER = ImVec4(1.0F, 1.0F, 1.0F, 1.0F);
const auto RED_MARKER = ImVec4(1.0F, 0.0F, 0.0F, 1.0F);
const auto GREEN_MARKER = ImVec4(0.0F, 1.0F, 0.0F, 1.0F);
const auto BLUE_MARKER = ImVec4(0.0F, 0.0F, 1.0F, 1.0F);
const auto RED_BACKGROUND = ImVec4(0.8F, 0.0F, 0.0F, 0.2F);
const auto GREEN_BACKGROUND = ImVec4(0.0F, 0.8F, 0.0F, 0.2F);
const auto BLUE_BACKGROUND = ImVec4(0.0F, 0.0F, 0.8F, 0.2F);

/* TABULAR SETTINGS */
constexpr auto VEHICLE_TABLE_HEIGHT{175.0F};
constexpr auto VEHICLE_TABLE_WIDTH{WINDOWS_WIDTH};
constexpr auto BELOW_TABLE{BELOW_LANES + VEHICLE_TABLE_HEIGHT};

/* BUTTON SETTINGS */
constexpr auto BUTTON_WIDTH{100.0F};
constexpr auto BUTTON_HEIGHT{50.0F};
constexpr auto BUTTON_LINE_SHIFT{200.0F};
constexpr auto BELOW_BUTTON{BELOW_TABLE + BUTTON_HEIGHT};

/* CYCLE NUMBER SETTINGS */
constexpr auto CYCLE_HEIGHT{100.0F};
constexpr auto BELOW_CYCLE{BELOW_BUTTON + BUTTON_HEIGHT};
