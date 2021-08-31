# cpp_eval_keras

This repo provides a pure C++ based CPU library for evalution and deployment of Keras trained ML models as well as provides an example executable how to use the library. The code can build for both Linux/Windows using cmake tools. Details on how to build is provided as well. This Library is based on sources from keras2CPP project (https://github.com/gosha20777/keras2cpp). 

Assumptions:

1. The Keras ML model must be defined using sequential API and are limited to following operations:
  - Dense fully connected layers
  - Convolution 1D/Conv2D layers
  - Max Pooling 1D/2D layers
  - Flatten layers
  - Batch Normalization layers
  - LSTM
  - Activation: tanh, relu, linear, elu, sigmoid, softmax, softplus
  
2. Keras ML model is trained before archived in /Model folder. There is a relative reference to this folder in client executable.

Compatibility: The library is compatible with Keras 2.x (all versions) and C++ 17.

How to build?

For Building on windows or Linux just use the top level cmake file which first builds the library and shows how to use it in the exe.
If Cmake(3.1 or higher) is not installed, install it for Windows or Linux first.  On Ubuntu, you can simply run the following command. 
sudo apt-get install cmake

On Linux:
1) Clone this repo.
2) CD to the source directory which contains a CMakeList.txt file containing the build instructions.
3) Create CMake configuration files inside "build" folder: cmake -H. -Bbuild
4) Build the C++ library and executable: cmake --build build -- -j3
5) Run the Exe: ./build/TestingKerasCpuDeployment  

On Windows:
1) Clone this repo.
2) CD to the source directory which contains a CMakeList.txt file containing the build instructions.
3) Create CMake configuration files inside "build" folder: cmake -S <path-to-source> -B <path-to-build>
4) Build the C++ library and executable: Use VS to build from the project files created
5) Run the Exe  
