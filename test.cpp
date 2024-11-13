#include <ctime>
#include <array>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
int main(){
    time_t time_1;
    time_t time_2;
    int j = 0;
    int r;
    milliseconds ms1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    int dis = 20;
    while (j < 1000000000){
        r = 1 << dis;
        j++;
    }
    milliseconds ms2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout<<"Time Taken by A: "<< ms2.count() - ms1.count() <<" seconds"<<endl;

    ms1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    j = 0;
    dis = 1;
    while (j < 1000000000){
            r = 1 << dis;
        j++;
    }
    ms2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    cout<<"Time Taken by B: "<< ms2.count() - ms1.count() <<" seconds"<<endl;

}