#include "time_tester.h"

void log(long long N){
    int l = 0;
    int r = N-1;
    while(l<r){
        int m = (l+r)/2;
        if(m*m<N)       l = m+1;
        else if(m*m>=N)  r = m-1;
        // else return;
    }
}

void log_ret(long long N){
    int l = 0;
    int r = N-1;
    while(l<r){
        int m = (l+r)/2;
        if(m*m<N)       l = m+1;
        else if(m*m>N)  r = m-1;
        else return;
    }
}

int main(){
    func_test(1000000, 20, 1000000, {log_ret, log});
}