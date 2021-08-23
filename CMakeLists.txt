cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(TestingKerasCpuDeployment 
		VERSION 0.1 
		DESCRIPTION "An exe testing KerascppCpu Library for evalution and deployment" 
		LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# add the KerascppCpu library
add_subdirectory(KerascppCpu)

# add the executable
add_executable(TestingKerasCpuDeployment "")
target_sources(TestingKerasCpuDeployment
    PRIVATE test.cc)


target_link_libraries(TestingKerasCpuDeployment PUBLIC KerascppCpu)

# express includes, see src folder specified to pickup the includes, -I
target_include_directories(TestingKerasCpuDeployment PUBLIC
                          "${PROJECT_SOURCE_DIR}/KerascppCpu/src"
                          )


# Tell cmake to install our binary into the bin directory of the install.
#install(TARGETS TestingKerasCpuDeployment DESTINATION bin)