#pragma once

#include <filesystem>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#include "AdTypes.hpp"
#include "DataLoaderTypes.hpp"
#include "Render.hpp"

namespace fs = std::filesystem;

void cycle_function(const fs::path &ego_filepath,
                    const fs::path &vehicle_filepath,
                    const fs::path &lane_filepath,
                    GLFWwindow *const window);
