# C Inference for Keras

This is a library to run Keras models within C++ without any dependencies. It uses the 
keras2CPP project (https://github.com/gosha20777/keras2cpp).

How to run: The test.cpp in th emain directory shows an example of how to load the model and evaluate the same in C++. Follow the steps below:

1) Run make in build/ to compile the libml library

2) Modify test.cpp

3) Compile test.cpp and link the precompiled libml library

