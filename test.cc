#include "model.h"
#include "tensor.h"
#include<typeinfo>
#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

using keras2cpp::Model;
using keras2cpp::Tensor;


std::vector<float> read_txt(std::string fname_scale) {
	std::vector<float> contianer;
	string line;

	ifstream myfile(fname_scale);
	if (myfile.is_open())
	{	
		int i = 0;
		while ( getline(myfile, line) )
		{
			contianer.push_back(std::stof(line));
		}
		myfile.close();
		i += 1;
	}

	return contianer;

}


int main() {
    // Initialize model.
    string target = "time_";
    string solver = "sparse_";
    string fname;
    // fname = string("../models/") + target + string("predictor_") + solver + string("solver.model");
    fname = "./models/example.model";

    Model model = Model::load(fname);

    // preprocess preparation
    string fname_scale = string("./data/") + target + solver + string("scale.txt"); //change the path for your purpose
    std::vector<float> scale = read_txt(fname_scale);

    string fname_mean = string("./data/") + target + solver + string("mean.txt"); //change the path for your purpose
    std::vector<float> mean = read_txt(fname_mean);

	// load data
	std::vector<std::vector<float>> test_data = {{4.0, 636978, 319378, 6, 97, 153367, 0.240773, 1, 0, 472, 213458, 269659, 0, 0, 0.423341}};

	// inference
	std::vector<int> results;
	for (int i = 0; i < test_data.size(); ++i)
	{	
		int size = test_data.at(i).size();
		Tensor in{size};
		
		// preprocess
		for (int j = 0; j < size; ++j)
		{	
			test_data.at(i).at(j) = (test_data.at(i).at(j) - mean.at(j))/scale.at(j);
			cout << test_data.at(i).at(j) << " ";
		}
		cout << " " << "\n";

		// run the model
		in.data_ = test_data.at(i);
		Tensor out = model(in);

		//get the class
		int max_cls = 0;
		int max_score = 0;
		for (int k = 0; k < 5; ++k)
		{
			if (out.data_[k] > max_score)
			{
				max_score = out.data_[k];
				max_cls = k;
			}
		}
		results.push_back(max_cls);

		cout << max_cls << "\n";
	}

   return 0;
}
