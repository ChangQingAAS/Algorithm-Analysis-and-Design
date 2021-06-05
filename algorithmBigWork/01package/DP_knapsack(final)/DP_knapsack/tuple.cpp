#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <map>
#include "read_data.cpp"

using namespace std;

class Tuple{
public:
    long_d a;
    long_d b;
    Tuple(){}
    Tuple(int a, int b){
        this->a = a;
        this->b = b;
    }
};

map<int, Tuple> PF[30];
map<int, Tuple> QF;
map<int, Tuple>::iterator it;
map<int, Tuple>::iterator jt;

void organize(int index);
void Init_map();

void calculate(){

    Init_map();

    PF[n].insert(pair<int, Tuple>(0, Tuple(0, 0)));
    PF[n].insert(pair<int, Tuple>(1, Tuple(w[n], p[n])));
    QF.insert(pair<int, Tuple>(0, Tuple(PF[n].at(0).a + w[n - 1], PF[n].at(0).b + p[n - 1])));
    QF.insert(pair<int, Tuple>(1, Tuple(PF[n].at(1).a + w[n - 1], PF[n].at(1).b + p[n - 1])));

    for(int i = n - 1; i > 1; i--){
        int k = 0;
        it = PF[i + 1].begin();
        while(it != PF[i + 1].end()){
            PF[i].insert(pair<int, Tuple>(k++, it->second));
            ++it;
        }
        jt = QF.begin();
        while(jt != QF.end()){
            PF[i].insert(pair<int, Tuple>(k++, jt->second));
            ++jt;
        }
        organize(i);
        QF.clear();
        it = PF[i].begin();
        k = 0;
        while(it != PF[i].end()){
            int a = it->second.a + w[i - 1];
            int b = it->second.b + p[i - 1];
            if(a <= c) QF.insert(pair<int, Tuple>(k++, Tuple(a, b)));
            ++it;
        }
    }
}

void organize(int index){

    it = PF[index].begin();
    int will_be_deleted[MAX] = {0};
    int count = 0;
    while(it != PF[index].end()){
        int a1 = it->second.a;
        int b1 = it->second.b;
        if(a1 > c){
            will_be_deleted[count++] = it->first;
            ++it;
            continue;
        }
        jt = ++it;
        --it;
        while(jt != PF[index].end()){
            int a2 = jt->second.a;
            int b2 = jt->second.b;
            if(a1 <= a2 && b1 >= b2){
                will_be_deleted[count++] = it->first;
                break;
            }
            ++jt;
        }
        ++it;
    }
    for(int i = 0; i < count; i++){
        PF[index].erase(will_be_deleted[i]);
    }
}

long_d f(int i, long_d y){
    it = PF[i].begin();
    jt = PF[i].begin();
    while(it != PF[i].end()){
        int a = it->second.a;
        if(a <= y && a >= jt->second.a){
            jt = it;
        }
        ++it;
    }
    return jt->second.b;
}

void result(){
    long_d y = c;
    int optimum = max(f(2, y), f(2, y - w[1]) + p[1]);
    if(optimum == f(2, y)) res[1] = 0;
    else {
        res[1] = 1;
        y -= w[1];
    }
    for(int i = 2; i < n; i++){
        if(f(i, y) == f(i + 1, y)) res[i] = 0;
        else{
            res[i] = 1;
            y -= w[i];
        }
    }
    if(f(n, y)) res[n] = 1;
    else res[n] = 0;
}

void Init_map(){
    for(int i = 0; i <= n; i++){
        PF[i].clear();
    }
    QF.clear();
}