#include <fstream>
#include <string>
#include <iomanip>

#include "read_data.cpp"

using namespace std;

string path_01 = "answers/KNAPSACK_01/recursion_test/result.txt";
string path_02 = "answers/KNAPSACK_01/iteration_test/result.txt";
string path_03 = "answers/KNAPSACK_02/recursion_test/result.txt";
string path_04 = "answers/KNAPSACK_02/iteration_test/result.txt";

void open_output_files(){

    output_file_1.open(path_01);
    output_file_2.open(path_02);
    output_file_3.open(path_03);
    output_file_4.open(path_04);

    output_file_1 << "-----------------KNAPSACK_01----"
            << "--------recursion----------\n\n";
    output_file_2 << "-----------------KNAPSACK_01----"
            << "--------iteration----------\n\n";
    output_file_3 << "-----------------KNAPSACK_02----"
            << "--------recursion----------\n\n";
    output_file_4 << "-----------------KNAPSACK_02----"
            << "--------iteration----------\n\n";
    output_file_1 << "FileIndex\t" << "n\t" << "c\t" 
        << "Answer\t" << "TimeSpent\t" << "TotalRecurseTime\n";
    output_file_2 << "FileIndex\t" << "n\t" << "c\t" 
        << "Answer\t" << "TimeSpent\n";
    output_file_3 << "FileIndex\t" << "n\t" << "c\t" 
        << "Answer\t" << "TimeSpent\t" << "TotalRecurseTime\n";
    output_file_4 << "FileIndex\t" << "n\t" << "c\t" 
        << "Answer\t" << "TimeSpent\n";

}

/*for recursion test*/
void output_recursion(file_dir d){

    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    spent_time *= 1000;

    if(d == KNAPSACK_01){
        output_file_1 << "    " << file_index << "    \t" << n << "   " 
            << c << "   " << (compare_results(d) ? "correct" : "wrong") << fixed 
            << setprecision(5) << "   " << spent_time << "ms\t" << "    " 
            << total_recurse_time << '\n';
    }
    else if(d == KNAPSACK_02){
        output_file_3 << "    " << file_index << "    \t" << n << "   " 
            << c << "   " << (compare_results(d) ? "correct" : "wrong") << fixed 
            << setprecision(5) << "   " << spent_time << "ms\t" << "    " 
            << total_recurse_time << '\n';
    }

}

void output_iteration(file_dir d){

    double spent_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    spent_time *= 100;

    if(d == KNAPSACK_01){
        output_file_2 << "    " << file_index << "    \t" << n << "   " 
            << c << "   " << (compare_results(d) ? "correct" : "wrong") << fixed 
            << setprecision(5) << "   " << spent_time << "ms\n";
    }
    else if(d == KNAPSACK_02){
        output_file_4 << "    " << file_index << "    \t" << n << "   " 
            << c << "   " << (compare_results(d) ? "correct" : "wrong") << fixed 
            << setprecision(5) << "   " << spent_time << "ms\n";
    }

}

void close_output_files(){
    output_file_1.close();
    output_file_2.close();
    output_file_3.close();
    output_file_4.close();
}