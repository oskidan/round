add_library(jam_core INTERFACE)
target_link_libraries(jam_core
  INTERFACE
    project_options
    project_warnings)
target_include_directories(jam_core 
  INTERFACE
    "${CMAKE_SOURCE_DIR}/include")

add_library(jam_physics INTERFACE)
target_link_libraries(jam_physics
  INTERFACE
    jam_core)

add_executable(round)
target_sources(round
  PRIVATE
    main.cpp)
target_link_libraries(round
  PRIVATE
    jam_physics)
