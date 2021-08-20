#include "src/model.h"
#include "src/tensor.h"
#include<typeinfo>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

using keras2cpp::Model;
using keras2cpp::Tensor;

int main() {
    // Initialize model.
    Model model = Model::load("../models/time_predictor.model");

    int test_samples = 10;

    for (int j=0; j<test_samples; j++){
	Tensor in{2};
	srand(time(0));
	std::vector<float> vect;	
	for (int i=0; i<2; i++){
		float rd = 2.0*(rand())/(RAND_MAX) - 1.0;
		vect.push_back(rd);
	}
	in.data_ = vect;
	float ground_truth = pow(in.data_[0], 2.0) + pow(in.data_[1], 2.0);

	Tensor out = model(in);

	std::cout << "Test sample:" << j+1 << ", Input 1:" << in.data_[0] << ", Input 2:" << in.data_[1] << ", Prediction:" << out.data_[0] << ", Ground truth:"<< ground_truth <<std::endl; 


    }

   return 0;
}
