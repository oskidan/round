find_package(Catch2 REQUIRED)

include(CTest)
include(Catch)

add_library(catch_main OBJECT catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(jam_math_tests)
target_sources(jam_math_tests
  PRIVATE
    "./jam/math/point-test.cpp"
    "./jam/math/scalar-test.cpp"
    "./jam/math/vector-test.cpp")
target_link_libraries(jam_math_tests
  PRIVATE
    catch_main
    jam_math)

catch_discover_tests(jam_math_tests
  TEST_PREFIX   "jam_math."
  REPORTER      "xml"
  OUTPUT_DIR    "."
  OUTPUT_PREFIX "jam_math."
  OUTPUT_SUFFIX ".xml")

add_executable(jam_physics_tests)
target_sources(jam_physics_tests
  PRIVATE
    "./jam/physics/acceleration-test.cpp"
    "./jam/physics/force-test.cpp"
    "./jam/physics/mass-test.cpp"
    "./jam/physics/time-test.cpp"
    "./jam/physics/velocity-test.cpp")
target_link_libraries(jam_physics_tests
  PRIVATE
    catch_main
    jam_physics)

catch_discover_tests(jam_physics_tests
  TEST_PREFIX   "jam_physics."
  REPORTER      "xml"
  OUTPUT_DIR    "."
  OUTPUT_PREFIX "jam_physics."
  OUTPUT_SUFFIX ".xml")