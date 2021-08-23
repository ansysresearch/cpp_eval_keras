# cpp_eval_keras
This project contains two parts:
1. A C++ CPU Library for evalution and deployment of ML models
2. An exe testing the above library in a client code

Assumptions:
1. C++ 17 features are used, if not using this reach out we also have a VS studio version without C++ 17
2. Model folder at the top level is expected to have the keras model archived, there is a relative reference to this folder in test.cc 
For Building on windows or Linux just use the top level cmake file which first builds the library and shows how to use it in the exe.
