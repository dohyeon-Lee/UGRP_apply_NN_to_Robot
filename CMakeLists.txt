cmake_minimum_required(VERSION 3.10)
set(CMAKE_PREFIX_PATH ./libtorch) #./libtorch
set(CMAKE_CXX_COMPILER g++-11)
set(CMAKE_C_COMPILER gcc-11)
# Set the project name
project(SerialReader)

# Find Boost libraries
find_package(Boost 1.66 REQUIRED COMPONENTS system thread chrono)
find_package(Torch REQUIRED)
find_package(Eigen3 REQUIRED) #
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})

# Add an executable
add_executable(serial_reader read.cpp)

# Include Boost headers
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Eigen3_INCLUDE_DIRS})

# Link Boost libraries
target_link_libraries(serial_reader ${Boost_LIBRARIES} ${Eigen3_LIBS} ${TORCH_LIBRARIES})