#include "time_tester.h"

#define N_max 20000
long long arr[N_max];

void swap(long long i1, long long i2){
    long long temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

void bubbleSort1(long long N){
    for(long long i=1; i<N; i++){
        for(long long j=0; j<i; j++){
            if(arr[j]<arr[j+1]) swap(j, j+1);
        }
    }
}

void bubbleSort2(long long N){
    for(long long i=1; i<N; i++){
        for(long long j=i; j>0; j--){
            if(arr[j]<arr[j-1]) swap(j, j-1);
        }
    }
}

void bubbleSort3(long long N){
    for(long long i=0; i<N-1; i++){
        for(long long j=i; j<N; j++){
            if(arr[j]<arr[j+1]) swap(j, j+1);
        }
    }
}

void preamb(long long N){
    for(long long i=1; i<=N; i++) arr[i] = rand() % N;
}

int main(){
    func_test(1000, 10, 1000, {bubbleSort1, bubbleSort2, bubbleSort3}, preamb);
}
