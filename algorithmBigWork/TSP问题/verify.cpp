#include <string>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <cassert>
using namespace std;

#include "global.h"
#include "path.h"

int num = 0;

void VerifyMyAnswers(string MyAnswersPath, string StandardAnswersPath)
{

    ifstream infile;
    infile.open(MyAnswersPath);
    assert(infile.is_open());

    double MyAnswers[MAX_NUM];
    int i = 0;
    while(!infile.eof()){
        infile >> MyAnswers[i++];
    }
    infile.close();

    infile.open(StandardAnswersPath);
    assert(infile.is_open());

    double StandardAnswers[MAX_NUM];
    i = 0;
    while(!infile.eof()){
        infile >> StandardAnswers[i++];
    }
    infile.close();
    
    for(int k = 0; k < i; k++)
    {
        if(MyAnswers[k] != StandardAnswers[k])
        {
            cout<<"Wrong Answers!\n";
            cout<<"The position of wrong answers is "<< k <<" ";
            cout<<",where myanswer is " << MyAnswers[k];
            cout<<", standardanswers is "<<StandardAnswers[k]<<endl;
            return;
        }
    }
    num++;
    cout<<"Right Answers!\n";

    return;
}

int main()
{
    for(int j = 0; j < DataSetNum; j++)
        VerifyMyAnswers(answers_path[j], standard_answers_path[j]);
    return 0;
}