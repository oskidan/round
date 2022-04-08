find_package(fmt REQUIRED)

add_library(jam_core INTERFACE)
target_link_libraries(jam_core
  INTERFACE
    project_options
    project_warnings)
target_include_directories(jam_core 
  INTERFACE
    "${CMAKE_SOURCE_DIR}/include")

add_library(jam_math STATIC)
target_sources(jam_math
  PRIVATE
    "./jam/math/point_io.cpp"
    "./jam/math/scalar_io.cpp"
    "./jam/math/vector_io.cpp")
target_link_libraries(jam_math
  PUBLIC
    jam_core)

add_library(jam_physics STATIC)
target_sources(jam_physics
  PRIVATE
    "./jam/physics/acceleration_io.cpp"
    "./jam/physics/force_io.cpp"
    "./jam/physics/mass_io.cpp"
    "./jam/physics/time_io.cpp"
    "./jam/physics/velocity_io.cpp")
target_link_libraries(jam_physics
  PUBLIC
    jam_math)

add_executable(round)
target_sources(round
  PRIVATE
    "./main.cpp")
target_link_libraries(round
  PRIVATE
    jam_physics
    ftxui::screen
    ftxui::component
    fmt::fmt)
