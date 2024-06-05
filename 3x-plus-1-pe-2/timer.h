#include <time.h>
#include <stdio.h>

clock_t start=0;
clock_t timeCurrent=300;
clock_t timeAfis=300;
void start_counter(){
    if(start==0){
        start=clock();
        printf("Process started at time %f\n",(double)start/CLOCKS_PER_SEC);
    }
    else{
        printf("Timer already started");
    }
}
int check_counter(){
    if((clock()-start)/CLOCKS_PER_SEC>timeCurrent){
        timeCurrent+=timeAfis;
        return 1;
    }
    return 0;
}
void predicted_time(int limit){
    printf("Predicted time:\n");
    long long time=0;
    if(limit>=22){
        time=1;
    }

    for(int i=22;i<limit;i++){
        time*=2;
    }
    printf("%lld second/s or more\n",time);
    if(time>60){
        time/=60;
        printf("%lld minute/s or more\n",time);
    }
    if(time>60){
        time/=60;
        printf("%lld hour/s or more\n",time);
    }
    if(time>24){
        time/=24;
        printf("%lld day/s or more\n",time);
    }
    if(time>365){
        time/=365;
        printf("%lld year/s or more\n",time);
    }
}
void end_counter(){
    printf("Time used: %f",(double)(clock()-start)/CLOCKS_PER_SEC);
}