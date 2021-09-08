#include "model.h"
#include "tensor.h"
#include<typeinfo>
#include<iostream>
#include<vector>
#include<ctime>
#include <math.h>
#include<sstream> // for testing, should be removed when delivered
#include<utility> // for testing, should be removed when delivered

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

// this function should be removed when delievered
std::vector<std::vector<float>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<string> head;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    float val;
    // float fl;

    cout << "reading_test_data" << "\n";

    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){

            cout << colname<< " ";
            // Initialize and add <colname, int vector> pairs to result
            head.push_back(colname);
            // content.push_back(std::vector<float> {});
        }
        cout << " " << "\n";
    }

    std::vector<std::vector<float>> contents;

    // Read data, line by line
    while(std::getline(myFile, line))
    {	
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
       // int colIdx = 0;

    	std::vector<float> content;

        // Extract each integer
        // First get rid of the row idx
        while(ss >> val){
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') break;
        }
        ss.ignore();

        if(ss.peek() == ',') ss.ignore();
        while(ss >> val){

            cout << val<< " ";

            // Add the current integer to the 'colIdx' column's values vector
            content.push_back(val);

            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();

            // Increment the column index
            // colIdx++;
        }
        cout << " " << "\n";
        contents.push_back(content);
    }

    // Close file
    myFile.close();

    return contents;
}


std::vector<float> preprocess_to_standardize(std::vector<float> sample, std::vector<float> mean, std::vector<float> scale)
{	
	for (int j = 0; j < sample.size(); ++j)
	{	
		sample.at(j) = (sample.at(j) - mean.at(j))/scale.at(j);
		cout << vector_sample << " ";
	}
	cout << " " << "\n";

	return sample
}


std::vector<float> preprocess_to_log10_scale(std::vector<float> sample, std::vector<int> feature_idx)
{
	for (int j = 0; j < sample.size(); ++j)
	{	
		for (int m = 0; m < feature_idx.size(); ++m)
		{
			if(j == large_feature.at(m))
			{				
				sample.at(j) = log10(sample.at(j) + 1);
			}
		}
		cout << sample.at(j) << " ";
	}
	cout << " " << "\n";

	return sample
}


int main() {
    // Use case
    string ml_model_name = "time_predictor" // ["time_predictor", "memory_predictor"] 
    string solver = "_sparse_"; // this should be the input from MAPDL, ["sparse_", "model_", "PCG_"]
    string preprocess = "standardize"; // this can be changed based on what we want, ["standardize", "log10"]

    std::vector<float> mean;
    std::vector<float> scale;
    std::vector<float> large_feature;

    // preprocess preparation
    if (preprocess == "standardize")
    {
	    string fname_scale = string("./data/") + ml_model_name + solver + string("scale.txt"); //change the path for your purpose
	    scale = read_txt(fname_scale);

	    string fname_mean = string("./data/") + ml_model_name + solver + string("mean.txt"); //change the path for your purpose
	    mean = read_txt(fname_mean);
    }

	if(preprocess == "log10")
	{  	
	    if (solver == "_model_")
	    {
	    	large_feature = {1, 2, 3, 5, 9, 10, 11};
	    }
	    else {
	    	large_feature = {1, 2, 4, 5, 9, 10, 11};
	    }
    }

    string fname;
    fname = string("../models/") + ml_model_name + solver + string("solver_") + preprocess + string(".model");
    // fname = "./models/example.model";

    Model model = Model::load(fname);

	// load data
	// std::vector<std::vector<float>> test_data = {{4.0, 636978, 319378, 6, 97, 153367, 0.240773, 1, 0, 472, 213458, 269659, 0, 0, 0.423341}}; // this should be the input from MAPDL
    string fname_test_data = string("/home/ansysai/hjiang/projects/cpp_eval_keras/data/") + ml_model_name + string("_") + solver + string("test_data.csv");
    std::vector<std::vector<float>> test_data = read_csv(fname_test_data);

	
	// initalize results;
	if (ml_model_name == "time_predictor")
	{
		std::vector<float> results;
	}

	if (ml_model_name == "memory_predictor")
	{
		std::vector<int> results;
	}

	for (int i = 0; i < test_data.size(); ++i)
	{	
		cout << i << "\n";

		int size = test_data.at(i).size();
		Tensor in{size};
		
		// preprocess
		if (preprocess == "standardize")
		{
			std::vector<float> vector_data = preprocess_to_standardize(test_data.at(i), mean, scale)
		}

		if (preprocess == "log10")
		{
			std::vector<float> vector_data = preprocess_to_log10_scale(test_data.at(i), large_feature)
		}

		// inference
		in.data_ = vector_data;
		Tensor out = model(in);

		// time regression
		if (ml_model_name == "time_predictor")
		{	
			float output = out.data_.at(0);
			results.push_back(output);
			cout << output << "\n";
		}
		
		// memory classification
		if (ml_model_name == "memory_predictor")
		{
			int max_cls = 0;
			int max_score = 0;
			for (int k = 0; k < 6; ++k)
			{
				if (out.data_[k] > max_score)
				{
					max_score = out.data_[k];
					max_cls = k;
				}
			}
			results.push_back(output);
			cout << max_cls << "\n";
		}
	}

	// save results
	result_fname = string("results/") + ml_model_name + solver + string("solver_") + preprocess + string("_test_results.txt")
    std::ofstream outFile(result_fname);
    for (const auto &e : results) outFile << e << "\n";
    return 0;
}
