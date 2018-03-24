
cmake_minimum_required(VERSION 2.8)
project( IOSB_TASK C CXX )

# Cmake output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

# Add the executable
add_executable(task src/task.cpp)

# Set header search path
include_directories(./include/)

# Add OpenCV .so
find_package( OpenCV REQUIRED )
target_link_libraries(task ${OpenCV_LIBS})
