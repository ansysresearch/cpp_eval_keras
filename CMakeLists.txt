cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(KerascppCpuLib 
		VERSION 0.1 
		DESCRIPTION "A C++ CPU Library for evalution and deployment" 
		LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)   


#set(BOOST_URL "https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.zip" CACHE STRING "Boost download URL")

# If we add a library a to be built from the source files listed with other proj dependency 
#add_library(a b.h b.cpp)
#add_dependencies(a c)

# create a lib or exe with source files
add_library(KerascppCpuLib "")
target_sources(KerascppCpuLib
    PRIVATE
        src/utils.cc
        src/tensor.cc
        src/model.cc
	src/baseLayer.cc
	src/activation.cc
	src/batchNormalization.cc
	src/flatten.cc
	src/conv1d.cc
	src/conv2d.cc
	src/dense.cc
	src/elu.cc
	src/embedding.cc
	src/locally1d.cc
	src/locally2d.cc
	src/lstm.cc
) 
 
# express includes, see src folder specified to pickup the includes, -I
target_include_directories(KerascppCpuLib PUBLIC "${PROJECT_SOURCE_DIR}/src")

# include boost headers only as PRIVATE includes, -I
# target_include_directories(KerascppCpuLib PRIVATE ${BOOST_SOURCE})						  					  

# express linking libs
#target_link_libraries(NeuralNetsCpu PUBLIC ${Boost_LIBRARIES})

# Tell cmake to install our binary into the bin directory of the install.
install(TARGETS KerascppCpuLib DESTINATION bin)