/*
* 测试代码
*/

#include <iostream>
#include "output.cpp"
#include "recursion.cpp"
#include "iteration.cpp"


int main(){

    open_output_files();        // 打开要输出结果的文件
    
    // 'KNAPSACK_01' 文件夹中数据集的处理
    for(file_index = 1; file_index < 5; file_index++){

        Init_all();             // 初始化所有全局变量
        Init_f();               // 初始化f矩阵

        Read_data_01(KNAPSACK_01, file_index);  // 从 KNAPSACK_01 文件夹中读取数据
        // 读取的数据赋值给 'knapsack.h' 中定义的全局变量

        start_time = clock();
        result();               // 递归计算并计时
        end_time = clock();
        output_recursion(KNAPSACK_01);      // 输出结果

        start_time = clock();
        Knapsack();             // 迭代计算并计时
        Traceback();
        end_time = clock();
        output_iteration(KNAPSACK_01);      //输出结果

    }

    // 'KNAPSACK_02' 文件夹中数据集的处理
    for(file_index = 1; file_index < 6; file_index++){

        Init_all();
        Init_f();

        Read_data_02(KNAPSACK_02, file_index);

        start_time = clock();
        result();
        end_time = clock();
        output_recursion(KNAPSACK_02);

        start_time = clock();
        Knapsack();
        Traceback();
        end_time = clock();
        output_iteration(KNAPSACK_02);
        
    }

    close_output_files();       // 关闭打开的所有文件

    cout << "Program executed succesfully!\n";
    cout << "Please open 'answers' folder where all the results are stored!\n";


    return 0;
}