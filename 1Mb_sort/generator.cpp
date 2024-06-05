#include <iostream>
#include<fstream>
using namespace std;
FILE* fout;
int main(int argc, char **argv){
    fout=fopen(argv[1],"w");
    srand(time(0));

    long long n=atoi(argv[2]),limit=atoi(argv[3]);
    long long period=n/100;
    fprintf(fout,"%lld\n",n);
    for(long long i=1;i<=n;i++){
        fprintf(fout,"%lld ",rand()%limit+1);
        if(period!=0 && i%period==0 && i/period<=100){cout<<i/period<<"%\n";}
    }
    fclose(fout);
}