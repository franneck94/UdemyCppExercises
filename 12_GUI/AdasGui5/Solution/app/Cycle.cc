#include <thread>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "Cycle.hpp"
#include "DataLoader.hpp"
#include "RenderConstants.hpp"

namespace fs = std::filesystem;

namespace
{
static auto is_playing = false;
static auto pressed_play = false;
static auto pressed_pause = false;
static auto pressed_replay = false;
static auto pressed_next = false;
static auto pressed_prev = false;
static auto pressed_load = false;
static auto input_cycle = int32_t{0};
} // namespace


void cycle_function(const fs::path &ego_filepath,
                    const fs::path &vehicle_filepath,
                    const fs::path &lane_filepath,
                    GLFWwindow *const window)
{
    auto cycle = std::size_t{0};
    auto ego_vehicle = VehicleInformationType{};
    auto vehicles = NeighborVehiclesType{};
    auto lanes = LanesInformationType{};

    init_ego_vehicle(ego_filepath.string(), ego_vehicle);
    init_vehicles(vehicle_filepath.string(), vehicles);
    init_lanes(lane_filepath.string(), lanes);

    while (!glfwWindowShouldClose(window))
    {
        pressed_next = false;
        pressed_prev = false;
        pressed_load = false;

        start_cycle();
        ImGui::NewFrame();

        plot_buttons();

        if (pressed_play)
        {
            if (cycle == 0 && cycle >= NUM_ITERATIONS)
            {
                reset_state(ego_filepath,
                            vehicle_filepath,
                            lane_filepath,
                            cycle,
                            ego_vehicle,
                            vehicles,
                            lanes);
            }

            pressed_pause = false;
            pressed_play = false;
            is_playing = true;
        }

        if (pressed_replay)
        {
            reset_state(ego_filepath, vehicle_filepath, lane_filepath, cycle, ego_vehicle, vehicles, lanes);

            pressed_replay = false;
            is_playing = true;
        }

        if (!pressed_pause && is_playing && cycle < NUM_ITERATIONS)
        {
            execute_cycle(cycle, ego_vehicle, vehicles, lanes);
        }
        else if (pressed_next)
        {
            if (cycle < NUM_ITERATIONS - 1U)
            {
                cycle++;
            }

            execute_cycle(cycle, ego_vehicle, vehicles, lanes);
        }
        else if (pressed_prev)
        {
            if (cycle > 0)
            {
                cycle--;
            }

            execute_cycle(cycle, ego_vehicle, vehicles, lanes);
        }
        else if (pressed_load)
        {
            if ((input_cycle > 0) && (input_cycle < NUM_ITERATIONS))
            {
                cycle = input_cycle;
                execute_cycle(cycle, ego_vehicle, vehicles, lanes);
            }
        }
        else if (pressed_pause)
        {
            render_cycle(ego_vehicle, vehicles, lanes, false, LaneAssociationType::NONE);
            is_playing = false;
        }
        else if (!is_playing)
        {
            render_cycle(ego_vehicle, vehicles, lanes, false, LaneAssociationType::NONE);
        }
        else if (cycle >= NUM_ITERATIONS)
        {
            is_playing = false;
        }

        plot_cycle_number(cycle);

        ImGui::Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_TIME_MS));
        ImGui::GetIO().DeltaTime = static_cast<float>(CYCLE_TIME_MS) / 1000.0F;

        end_cycle(window);

        if (is_playing)
        {
            cycle++;
        }
    }
}

void execute_cycle(const std::size_t cycle,
                   VehicleInformationType &ego_vehicle,
                   NeighborVehiclesType &vehicles,
                   LanesInformationType &lanes)
{
    const auto ego_lane_vehicles = get_vehicles_on_lane(ego_vehicle.lane, vehicles);
    const auto front_vehicle = get_impeding_vehicle(ego_lane_vehicles);
    const auto long_request = get_longitudinal_request(front_vehicle, ego_vehicle);
    const auto lat_request = get_lat_request(ego_vehicle, vehicles);

    load_cycle(cycle, vehicles, ego_vehicle, lanes);
    render_cycle(ego_vehicle, vehicles, lanes, long_request, lat_request);
}

void reset_state(const fs::path &ego_filepath,
                 const fs::path &vehicle_filepath,
                 const fs::path &lanes_filepath,
                 std::size_t &cycle,
                 VehicleInformationType &ego_vehicle,
                 NeighborVehiclesType &vehicles,
                 LanesInformationType &lanes)
{
    cycle = 0;
    init_ego_vehicle(ego_filepath.string(), ego_vehicle);
    init_vehicles(vehicle_filepath.string(), vehicles);
    init_lanes(lanes_filepath.string(), lanes);
}

void start_cycle()
{
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void end_cycle(GLFWwindow *const window)
{
    ImVec4 clear_color = ImVec4(30.0F / 255.0F, 30.0F / 255.0F, 30.0F / 255.0F, 1.00f);
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w,
                 clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void plot_buttons()
{
    auto const offset_x = (WINDOWS_WIDTH - (6.0F * BUTTON_LINE_SHIFT)) * 0.5F;

    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_TABLE));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, BUTTON_HEIGHT));

    const auto button_flags =
        (ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    if (ImGui::Begin("ButtonWindow", nullptr, button_flags))
    {
        ImGui::SameLine(offset_x);

        if (ImGui::Button("Play", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_play = true;
        }
        ImGui::SameLine(1 * BUTTON_LINE_SHIFT + offset_x);
        if (ImGui::Button("Pause", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_pause = true;
        }
        ImGui::SameLine(2 * BUTTON_LINE_SHIFT + offset_x);
        if (ImGui::Button("Replay", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_replay = true;
        }
        ImGui::SameLine(3 * BUTTON_LINE_SHIFT + offset_x);
        if (ImGui::Button("Prev", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_prev = true;
            is_playing = false;
        }
        ImGui::SameLine(4 * BUTTON_LINE_SHIFT + offset_x);
        if (ImGui::Button("Next", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_next = true;
            is_playing = false;
        }
        ImGui::SameLine(5 * BUTTON_LINE_SHIFT + offset_x);
        if (ImGui::Button("Load", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
        {
            pressed_load = true;
            is_playing = false;
        }

        ImGui::End();
    }
}

void plot_cycle_number(const std::size_t cycle)
{
    auto const offset_x = (WINDOWS_WIDTH - (6.0F * BUTTON_LINE_SHIFT)) * 0.5F;

    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_BUTTON));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, CYCLE_HEIGHT));

    if (ImGui::Begin("CycleWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImGui::Text("Cycle: %d", static_cast<std::int32_t>(cycle));

        ImGui::SameLine(offset_x);
        ImGui::SliderInt("###sliderCycle",
                         &input_cycle,
                         0,
                         NUM_ITERATIONS - 1U,
                         nullptr,
                         ImGuiSliderFlags_AlwaysClamp);

        ImGui::End();
    }
}
