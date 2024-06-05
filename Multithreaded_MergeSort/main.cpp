#include<iostream>
#include<fstream>
#include<thread>
#include<queue>
#include<algorithm>

using namespace std;
using namespace std::chrono;

#define maxi 3000000000

FILE* in, *out;

int *input=(int*)malloc(maxi*sizeof(int));

//most significant bit
int MSB(int x){
    int msb=1;
    while(x>1){
        msb*=2;
        x/=2;
    }
    return msb;
}

//combine 2 sorted arrays
void Merge(int* v,int st,int mid,int dr){
    int a_length=mid-st+1;
    int b_length=dr-mid;

    int* a=(int*)malloc(sizeof(int)*(a_length));
    for(int i=0;i<a_length;i++)a[i]=v[i+st];

    int* b=(int*)malloc(sizeof(int)*(b_length));
    for(int j=0;j<b_length;j++)b[j]=v[mid+j+1];
    
    int i=0,j=0,k=st;
    while(i<a_length && j<b_length){
        if(a[i]<b[j]){
            v[k++]=a[i++];
        }else{
            v[k++]=b[j++];
        }
    }
    while(i<a_length){
        v[k++]=a[i++];
    }
    while(j<b_length){
        v[k++]=b[j++];
    }
    free(a);
    free(b);
}
void MergeSort(int* v,int st, int dr){
    if(st<dr){
        int mid=(st+dr)/2;
        MergeSort(v,st,mid);
        MergeSort(v,mid+1,dr);

        Merge(v,st,mid,dr);
    }
}

//std implementation
void QuickSort(int*v,int st,int dr){
    sort(v+st,v+dr);
}

//must be power of 2 for ease of merge 
int thread_num= 128;

int main(int argc, char **argv){
    //file initialization
    in=fopen(argv[1],"r");
    out=fopen(argv[2],"w");

    //threads 
    queue<thread> threads;

    //data reading
    int n;
    fscanf(in,"%d",&n);
    thread_num=min(thread_num,MSB(n));
    for(int i=0;i<n;i++){
        fscanf(in,"%d",&input[i]);
    }
    
    auto start = high_resolution_clock::now();

    queue<pair<int,int>> intervals;

    //separate array in equal parts that are picked up by threads
    int period=n/thread_num;
    int rest=n-period*thread_num;
    for(int st=0;st<n;st+=period){
        int dr=st+period-1+(rest>0);
        threads.push(thread(MergeSort,input,st,dr));
        intervals.push(make_pair(st,dr));
        st+=rest>0;
        rest--;
    }
    
    //merging sorted arrays
    int length=thread_num;
    while(length>1){
        for(int i=0;i<length;i+=2){
            //wait for the 2 threads to finish
            threads.front().join();
            threads.pop();
            threads.front().join();
            threads.pop();
            //get interval values
            int st=intervals.front().first;
            int mid=intervals.front().second;
            intervals.pop();
            int dr=intervals.front().second;
            intervals.pop();

            //push new data back into queue
            intervals.push(make_pair(st,dr));
            threads.push(thread(Merge,input,st,mid,dr));
        }
        length/=2;
    }
    threads.front().join();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Sort: " << duration.count() << '\n';

    //output
    for(int i=0;i<n;i++){
        fprintf(out,"%d ",input[i]);
    }
    free(input);
}