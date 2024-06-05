#include<iostream>
#include<cmath>
#include<iomanip>
#include<climits>

double limit_expansion(){
    long long n=pow(2,52);
    return pow(1+(double)(1.0/n),n);
}
double factorial_expansion(){
    double e=1;
    int precision=20;
    long long factorial=1;
    for(int i=1;i<=precision;i++){
        factorial*=i;
        e+=1.0/factorial;
    }
    return e;
}
int main(){
    std::cout<<std::fixed<<std::setprecision(32);
    std::cout<<"Factorial expansion:"<<factorial_expansion()<<std::endl;
    std::cout<<"Limit expansion: "<<limit_expansion()<<std::endl;
    std::cout<<"Standard Library: "<<exp(1);
}