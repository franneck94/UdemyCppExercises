#pragma once

#include "imgui.h"
#include "implot.h"

/* FLAGS */
constexpr auto WINDOW_FLAGS_CLEAN = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;
constexpr auto PLOT_FLAGS = ImPlotFlags_NoTitle | ImPlotFlags_NoLegend;
constexpr auto AXES_FLAGS = ImPlotAxisFlags_Lock | ImPlotAxisFlags_Invert;
constexpr auto TABLE_FLAGS = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuter;

/* GENERAL WINDOW SETTINGS */
constexpr auto WINDOWS_HEIGHT{900.0F};
constexpr auto WINDOWS_WIDTH{1700.0F};

/* LANE PLOT SETTINGS */
constexpr auto LANE_PLOT_HEIGHT{3.0F * 200.0F};
constexpr auto LANE_PLOT_WIDTH{WINDOWS_WIDTH - 15.0F};
const auto PLOT_DIM = ImVec2(LANE_PLOT_WIDTH, LANE_PLOT_HEIGHT);
constexpr auto LANE_PLOT_TOTAL_HEIGHT{LANE_PLOT_HEIGHT + 10.0F};
constexpr auto BELOW_LANES{LANE_PLOT_TOTAL_HEIGHT + 10.0F};
const auto LINE_COLOR = ImVec4(1.0F, 1.0F, 1.0F, 1.0F);
constexpr auto LINE_WIDTH = 3.0F;
constexpr auto VEHICLE_MARKER = ImPlotMarker_Square;
constexpr auto VEHICLE_SCATTER_SIZE{15.0F};
constexpr auto LEFT_LANE_OFFSET_M{-3.0F};
constexpr auto CENTER_LANE_OFFSET_M{0.0F};
constexpr auto RIGHT_LANE_OFFSET_M{3.0F};

/* TABULAR SETTINGS */
constexpr auto VEHICLE_TABLE_HEIGHT = WINDOWS_HEIGHT - LANE_PLOT_HEIGHT - 100.0F;
constexpr auto VEHICLE_TABLE_WIDTH = WINDOWS_WIDTH;

/* CYCLE NUMBER SETTINGS */
constexpr auto CYCLE_NUMBER_WIDTH{200.0F};
constexpr auto CYCLE_NUMBER_HEIGHT{50.0F};
constexpr auto CYCLE_OFFSET{250.0F};

/* BUTTON SETTINGS */
constexpr auto BUTTON_WIDTH{100.0F};
constexpr auto BUTTON_HEIGHT{50.0F};
constexpr auto BUTTON_LINE_SHIFT{200.0F};
constexpr auto BUTTON_OFFSET1{250.0F};
constexpr auto BUTTON_OFFSET2{50.0F};
