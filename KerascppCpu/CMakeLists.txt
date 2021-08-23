cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(KerascppCpu 
		VERSION 0.1 
		DESCRIPTION "A C++ CPU Library for evalution and deployment" 
		LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# If we add a library a to be built from the source files listed with other proj dependency 
#add_library(a b.h b.cpp)
#add_dependencies(a c)

# create a lib or exe with source files
add_library(KerascppCpu "")
target_sources(KerascppCpu
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
	src/maxPooling2d.cc
    src/utils.h
    src/tensor.h
    src/model.h
	src/baseLayer.h
	src/activation.h
	src/batchNormalization.h
	src/flatten.h
	src/conv1d.h
	src/conv2d.h
	src/dense.h
	src/elu.h
	src/embedding.h
	src/locally1d.h
	src/locally2d.h
	src/lstm.h
	src/maxPooling2d.h
) 
 
# Tell cmake to install our binary into the bin directory of the install.
#install(TARGETS KerascppCpu DESTINATION ../bin)