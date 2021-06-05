
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define DataSetNum 3

string data_path[DataSetNum] = {
    "./DataSet/input_005.txt",
    "./DataSet/input_015.txt",
    "./DataSet/input_017.txt"
    // "./DataSet/input_026.txt",
    // "./DataSet/input_048.txt"
};

string answers_path[DataSetNum] = {
    "./Answers/output_005.txt",
    "./Answers/output_015.txt",
    "./Answers/output_017.txt"
    // "./Answers/output_026.txt",
    // "./Answers/output_048.txt"
};

string standard_answers_path[DataSetNum] = {
    "./Standard_Answers/standard_answers_input_005.txt",
    "./Standard_Answers/standard_answers_input_015.txt",
    "./Standard_Answers/standard_answers_input_017.txt"
    // "./Standard_Answers/standard_answers_input_026.txt",
    // "./Standard_Answers/standard_answers_input_048.txt"
};