/**
 * 背包问题全局变量，宏，以及一些常用函数
 */

#ifndef _READ_DATA_H_
#define _READ_DATA_H_

#include <iomanip>
#include <fstream>
using namespace std;

#define MAX 100
#define long_d long long

#define recursion 0x10
#define iteration 0x20

typedef int method_type;

int n;
long_d c;
long_d p[MAX];
long_d w[MAX];
long_d s[MAX];
long_d optimum[100];
int file_count = 0;

int res[MAX];
long_d res_optimum[100];

int file_index = 0;

clock_t start_time;
clock_t end_time;

int total_recurse_time = 0;

ofstream output_file_1, output_file_2, output_file_3, output_file_4;

bool compare_results(file_dir d);

void Init_all(){
    for(int i = 0; i < MAX; i++){
        p[i] = 0;
        w[i] = 0;
        s[i] = 0;
        res[i] = 0;
        res_optimum[i] = 0;
    }
    total_recurse_time = 0;
}

bool compare_results(file_dir d){
    if(d == KNAPSACK_01){
        for(int i = 1; i <= n; i++)
            if(res[i] != s[i]) return false;
        return true;
    }
    else if(d == KNAPSACK_02){
        if(optimum[file_index] == res_optimum[file_index]) return true;
        return false;
    }
    return false;
}

#endif