#include "model.h"
#include "tensor.h"
#include<typeinfo>
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream> // for testing, should be removed when delivered
#include<utility> // for testing, should be removed when delivered
using namespace std;

using keras2cpp::Model;
using keras2cpp::Tensor;

std::vector<float> read_txt(std::string filename) {
	std::vector<float> contianer;
	string line;

	ifstream myfile(fname_scale);
	if (myfile.is_open())
	{
		while ( getline(myfile, line) )
		{
			cout << line << '\n';
			contianer.push_back(float(line));
		}
		myfile.close();
	}

	return container;

}

// this function should be removed when delievered
std::vector<std::vector<int>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::vector<int>> result;
    std::vector<std::vector<string>> head;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    float val;


    // Read the column names
    if(myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
            
            cout << colname<< "\n";
            // Initialize and add <colname, int vector> pairs to result
            head.push_back(colname);
            // content.push_back(std::vector<float> {});
        }
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
        while(ss >> val){
            
            cout << val<< "\n";

            // Add the current integer to the 'colIdx' column's values vector
            content.push_back(val);
            
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            // colIdx++;
        }
        contents.push_back(content);
    }

    // Close file
    myFile.close();

    return contents;
}


int main() {
    // Initialize model.
    string target = "time_";
    string solver = "sparse_";
    string fname;
    fname = string("../models/") + target + string("predictor_") + solver + string("solver.model");

    Model model = Model::load(fname);

    int test_samples = 10;

    // preprocess preparation
    string fname_scale = string("../data/") + target + solver + string("scale.txt");
    std::vector<float> scale = read_txt(fname_scale);

    string fname_mean = string("../data/") + target + solver + string("mean.txt");
    std::vector<float> mean = read_txt(fname_scale);

	// load data
	string fname_test_data = string("../data/") + target + solver + string("test_data.csv");
	std::vector<std::vector<float>> test_data = read_csv(fname_test_data);

	// inference
	std::vector<float> results;
	for (int i = 0; i < test_data.size(); ++i)
	{	
		int size = contents.at(i).size();
		Tensor in{size};
		
		// preprocess
		for (j = 0; j < size; ++j)
		{
			contents.at(i).at(j) = (contents.at(i).at(j) - mean.at(j))/scale.at(j);
		}

		// run the model
		in.data_ = contents.at(i);
		Tensor out = model(in);

		//get the class
		int max_cls = 0;
		int max_score = 0;
		for (k = 0; k < 5; ++k)
		{
			cout << out.data_[k] << " ";
			if (out.data_[k] > max_score)
			{
				max_score = out.data[k];
				max_cls = i;
			}
		}
		cout << "\n";
		results.push_back(max_cls);
	}

	// write the output
    std::ofstream output_file("results/test_results.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(example.begin(), example.end(), output_iterator);

	// std::vector<float> results
	// for (int j = 0; j < test_data)
 //    for (int j=0; j<test_samples; j++){
	// Tensor in{2};
	// srand(time(0));
	// std::vector<float> vect;	
	// for (int i=0; i<2; i++){
	// 	float rd = 2.0*(rand())/(RAND_MAX) - 1.0;
	// 	vect.push_back(rd);
	// }
	// in.data_ = vect;
	// float ground_truth = pow(in.data_[0], 2.0) + pow(in.data_[1], 2.0);

	// Tensor out = model(in);

	// std::cout << "Test sample:" << j+1 << ", Input 1:" << in.data_[0] << ", Input 2:" << in.data_[1] << ", Prediction:" << out.data_[0] << ", Ground truth:"<< ground_truth <<std::endl; 


 //    }

   return 0;
}
