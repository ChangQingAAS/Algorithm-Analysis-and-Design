/**
 * 数据集读取函数
 */

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
using namespace std;

#define NONE 0x0
#define C 0x1
#define P 0x2
#define W 0x3
#define S 0x4
#define KNAPSACK_01 0x5
#define KNAPSACK_02 0x6

typedef int input_type;
typedef int file_dir;

#include "knapsack.h"

string make_path(input_type t, file_dir d, int i);
void read_c(string file);
void read_data_01(string file, long_d *data);
void read_data_02(string file);


/*读取数据*/
void Read_data_01(file_dir d, int i){
        file_count++;
        read_c(make_path(C, d, i));
        read_data_01(make_path(P, d, i), p);
        read_data_01(make_path(W, d, i), w);
        read_data_01(make_path(S, d, i), s);
}
void Read_data_02(file_dir d, int i){
        file_count++;
        read_data_02(make_path(NONE, d, i));
}

/*数据集路径字符串制作*/
string make_path(input_type t, file_dir d, int i){
        string path, file;
        if(d == KNAPSACK_01){
                path = "data_sets/KNAPSACK_01/";
                file = "p**_*.txt";
                switch(t){
                        case C: file[4] = 'c'; break;
                        case P: file[4] = 'p'; break;
                        case W: file[4] = 'w'; break;
                        case S: file[4] = 's'; break;
                }
                if(i < 10){
                        file[1] = '0';
                        char index = (char)(i + '0');
                        file[2] = index;
                }
                if(i >= 10){
                        int i1 = i / 10;
                        int i2 = i % 10;
                        char index1 = (char)(i1 + '0');
                        char index2 = (char)(i2 + '0');
                        file[1] = index1;
                        file[2] = index2;
                }
        }
        else if(d == KNAPSACK_02){
                path = "data_sets/KNAPSACK_02/data/";
                file = "f";
                string index = "";
                if(i < 10) index = (char)(i + '0');
                if(i >= 10){
                        index = "**";
                        int i1 = i / 10;
                        int i2 = i % 10;
                        char index1 = (char)(i1 + '0');
                        char index2 = (char)(i2 + '0');
                        index[0] = index1;
                        index[1] = index2;
                }
                file.append(index);
        }
        path.append(file);
        return path;
}

void read_c(string file){
    ifstream infile;
    infile.open(file);
    assert(infile.is_open());

    while(!infile.eof()) infile >> c;
    infile.close();
}

void read_data_01(string file, long_d *data){
    ifstream infile;
    infile.open(file);
    assert(infile.is_open());

    int i = 1;
    while(!infile.eof()){
        infile >> data[i++];
    }
    n = --i;
    infile.close();
}

void read_data_02(string file){
        ifstream infile;
        infile.open(file);
        assert(infile.is_open());

        infile >> n; infile >> c;
        int i = 1;
        while(i <= n){
                infile >> p[i] >> w[i];
                i++;
        }
        infile.close();

        string path = "data_sets/KNAPSACK_02/optimum_value/";
        path.append(file.substr(27, 2));
        infile.open(path);
        assert(infile.is_open());
        infile >> optimum[file_index];
}