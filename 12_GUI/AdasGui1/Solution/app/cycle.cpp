#include <thread>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"

#include "AdConstants.hpp"
#include "AdFunctions.hpp"
#include "DataLoader.hpp"
#include "RenderConstants.hpp"
#include "cycle.hpp"

namespace fs = std::filesystem;

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

void reset_state(const fs::path &ego_filepath,
                 const fs::path &data_filepath,
                 std::size_t &cycle,
                 VehicleType &ego_vehicle,
                 NeighborVehiclesType &vehicles)
{
    cycle = 0;
    init_ego_vehicle(ego_filepath.string(), ego_vehicle);
    init_vehicles(data_filepath.string(), vehicles);
}


void plot_cycle_number(const std::size_t cycle)
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, BELOW_LANES + CYCLE_OFFSET));
    ImGui::SetNextWindowSize(ImVec2(CYCLE_NUMBER_WIDTH, CYCLE_NUMBER_HEIGHT));
    if (ImGui::Begin("CycleWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImGui::Text("Cycle: %d", static_cast<std::int32_t>(cycle));
        ImGui::End();
    }
}

void cycle_function(const fs::path &ego_filepath, const fs::path &data_filepath, GLFWwindow *const window)
{
    static bool is_playing = false;
    static bool pressed_play = false;
    static bool pressed_pause = false;
    static bool pressed_replay = false;

    constexpr std::int64_t sleep_time = 50;
    std::size_t cycle = 0;
    auto ego_vehicle = VehicleType{};
    auto vehicles = NeighborVehiclesType{};

    init_ego_vehicle(ego_filepath.string(), ego_vehicle);
    init_vehicles(data_filepath.string(), vehicles);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        start_cycle();

        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(200, BELOW_LANES + BUTTON_OFFSET1 - BUTTON_OFFSET2));
        ImGui::SetNextWindowSize(
            ImVec2(WINDOWS_WIDTH - BUTTON_OFFSET1, WINDOWS_HEIGHT - BELOW_LANES + BUTTON_OFFSET1));

        const auto button_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
                                  ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize |
                                  ImGuiWindowFlags_NoScrollbar;

        if (ImGui::Begin("ButtonWindow", nullptr, button_flags))
        {
            if (ImGui::Button("Play", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
            {
                pressed_play = true;
            }
            ImGui::SameLine(1 * BUTTON_LINE_SHIFT);
            if (ImGui::Button("Pause", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
            {
                pressed_pause = true;
            }
            ImGui::SameLine(2 * BUTTON_LINE_SHIFT);
            if (ImGui::Button("Replay", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
            {
                pressed_replay = true;
            }

            ImGui::End();
        }

        if (pressed_play)
        {
            if (cycle == 0 && cycle >= NUM_ITERATIONS)
            {
                reset_state(ego_filepath, data_filepath, cycle, ego_vehicle, vehicles);
            }

            pressed_pause = false;
            pressed_play = false;
            is_playing = true;
        }

        if (pressed_replay)
        {
            reset_state(ego_filepath, data_filepath, cycle, ego_vehicle, vehicles);

            pressed_replay = false;
            is_playing = true;
        }

        if (!pressed_pause && is_playing && cycle < NUM_ITERATIONS)
        {
            render_cycle(ego_vehicle, vehicles);
            compute_future_state(ego_vehicle, vehicles, 0.100F);

            const auto &ego_lane_vehicles = get_vehicle_array(ego_vehicle.lane, vehicles);
            longitudinal_control(ego_lane_vehicles[0], ego_vehicle);

            const auto lane_change_request = get_lane_change_request(ego_vehicle, vehicles);
            (void)lateral_control(lane_change_request, ego_vehicle);

            cycle++;
            load_cycle(cycle, vehicles);
        }
        else if (pressed_pause)
        {
            render_cycle(ego_vehicle, vehicles);
            is_playing = false;
        }
        else if (!is_playing)
        {
            render_cycle(ego_vehicle, vehicles);
        }
        else if (cycle >= NUM_ITERATIONS)
        {
            is_playing = false;
        }

        plot_cycle_number(cycle);

        ImGui::Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        ImGui::GetIO().DeltaTime = static_cast<float>(sleep_time) / 1000.0F;

        end_cycle(window);

        if (is_playing)
        {
            cycle++;
        }
    }
}
