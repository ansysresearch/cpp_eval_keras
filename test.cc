#include "model.h"
#include "tensor.h"
#include<typeinfo>
#include<iostream>
#include<vector>
#include<ctime>
#include <math.h>

using namespace std;

using keras2cpp::Model;
using keras2cpp::Tensor;


std::vector<float> read_txt(std::string fname_scale) {
    std::vector<float> container;
    string line;

    ifstream myfile(fname_scale);
    if (myfile.is_open())
    {   
        int i = 0;
        while ( getline(myfile, line) )
        {
            cout << line << "\n";
            container.push_back(std::stof(line));
        }
        myfile.close();
        i += 1;
    }
    else
    {
        cout << "FILE NOT FOUND" << "\n";
    }

    return container;

}


std::vector<float> preprocess_to_standardize(std::vector<float> sample, std::vector<float> mean, std::vector<float> scale)
{   

    for (int j = 0; j < sample.size(); ++j)
    {   
        sample.at(j) = (sample.at(j) - mean.at(j))/scale.at(j);
        cout << sample.at(j) << " ";
    }
    cout << " " << "\n";

    return sample;
}


std::vector<float> preprocess_to_log10_scale(std::vector<float> sample, std::vector<int> feature_idx)
{
    for (int j = 0; j < sample.size(); ++j)
    {   
        for (int m = 0; m < feature_idx.size(); ++m)
        {
            if(j == feature_idx.at(m))
            {               
                sample.at(j) = log10(sample.at(j) + 1);
            }
        }
        cout << sample.at(j) << " ";
    }
    cout << " " << "\n";

    return sample;
}


std::vector<float> evaluate_time(std::string solver, std::vector<std::vector<float>> test_data)
{   
    std::vector<float> results;
    std::vector<int> large_feature;

    if (solver == "_modal_")
    {
        large_feature = {1, 2, 3, 5, 9, 10, 11};
    }
    else {
        large_feature = {1, 2, 4, 5, 9, 10, 11};
    }

    // "time_predictor_sparse_solver_standardize.model"
    // string fname = string("./models/time_predictor") + solver + string("solver.model"); 

    // cout << fname << "\n";
    string fname = string("./models/time_predictor") + solver + string("solver.model"); 

    Model model = Model::load(fname);


    for (int i = 0; i < test_data.size(); ++i)
    {   
        cout << i << "\n";

        int size = test_data.at(i).size();
        Tensor in{size};
        
        // preprocess
        std::vector<float> vector_data;
        vector_data = preprocess_to_log10_scale(test_data.at(i), large_feature);

        // inference
        in.data_ = vector_data;
        Tensor out = model(in);

        float output = out.data_.at(0);
        results.push_back(output);
        cout << "Time predicted: " << output << "\n";

    }

    return results;
}


std::vector<int> evaluate_memory(std::string solver, std::vector<std::vector<float>> test_data)
{   
    std::vector<int> results;
    std::vector<float> mean;
    std::vector<float> scale;
    int class_size = 9;

    string fname_scale = string("./data/memory_predictor") + solver + string("normal.txt"); // "time_predictor_sparse_normal.txt"
    scale = read_txt(fname_scale);

    string fname_mean = string("./data/memory_predictor") + solver + string("mean.txt");
    mean = read_txt(fname_mean);

    // "time_predictor_sparse_solver_standardize.model"
    string fname = string("./models/memory_predictor") + solver + string("solver.model"); 

    Model model = Model::load(fname);

    for (int i = 0; i < test_data.size(); ++i)
    {

        int size = test_data.at(i).size();

        Tensor in{size};
        
        // preprocess
        std::vector<float> vector_data;
        vector_data = preprocess_to_standardize(test_data.at(i), mean, scale);

        // inference
        in.data_ = vector_data;
        Tensor out = model(in);

        int max_cls = 0;
        float max_score = numeric_limits<float>::min();
        for (int k = 0; k < class_size; ++k)
        {
            if (out.data_[k] > max_score)
            {   
                max_score = out.data_[k];
                max_cls = k;
            }
        }
        results.push_back(max_cls);
        cout << "Memory class predicted: " << max_cls << "\n";
        
    }

    return results;
}


int main() {
    // Use case
    // string ml_model_name = "time_predictor"; // ["time_predictor", "memory_predictor"] 
    string solver = "_sparse_"; // this should be the input from MAPDL, ["_sparse_", "_modal_", "_PCG_"]

    // load data
    std::vector<std::vector<float>> test_data = {{4.0, 636978, 319378, 6, 97, 153367, 0.240773, 1, 0, 472, 213458, 269659, 0, 0, 0.423341}}; // this should be the input from outside
    cout << "DATA LOADED" << "\n";

    // evaluate
    std::vector<float> time_results;
    std::vector<int> memory_results;

    time_results = evaluate_time(solver, test_data);
    memory_results = evaluate_memory(solver, test_data);
    
    return 0;
}



