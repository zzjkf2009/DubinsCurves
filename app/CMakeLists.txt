add_executable(shell-app main.cpp 2D_Map_Build.cpp grid_map_build.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries( shell-app ${OpenCV_LIBS})
