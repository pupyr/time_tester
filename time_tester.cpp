#include "time_tester.h"

int max(int i1, int i2){
    return i1>i2 ? i1 : i2; 
}

size_t* init_sizes(int n, int m, std::vector<std::vector<std::string>> data){
    size_t* sizes = (size_t*) malloc(sizeof(size_t) * m);
    int sum_size = 1;
    for(int j=0; j<m; j++){
        int size_max = 0;
        for(int i=0; i<n; i++)
            size_max = max(size_max, data[i][j].size()+2);
        sizes[j] = size_max;
        sum_size += size_max + 1;
    }
    return sizes;
}

void table_print(std::vector<std::vector<std::string>> data){
    int n = data.size(), m = data[0].size(); 
    size_t* sizes = init_sizes(n,m,data);

    for(int i=0; i<n; i++){
        if(i!=0) std::cout<<std::endl;
        if(i>=2) std::cout<<"++";
        else     std::cout<<"===";
        for(int s=0; s<m; s++){
            for(int ss=0; ss<sizes[s]; ss++) 
                if(i<2) std::cout<<"=";
                else    std::cout<<"-";
            if(i>=2) 
                if(s<1) std::cout<<"++";
                else    std::cout<<"+";
            else     std::cout<<"=";
        }
        std::cout<<"\n||";
        for(int j=0; j<m; j++){
            int space_l = (sizes[j] - data[i][j].size())/2;
            int space_r = sizes[j] - data[i][j].size() - space_l;
            for(int s=0; s<space_l; s++) std::cout<<" ";
            std::cout<<data[i][j];
            for(int s=0; s<space_r; s++) std::cout<<" ";
            if(j<1) std::cout<<"||";
            else    std::cout<<"|";
        }
    }
    std::cout<<"\n++";
    for(int s=0; s<m; s++){
        for(int ss=0; ss<sizes[s]; ss++) std::cout<<"-";
        if(s<1) std::cout<<"++";
        else    std::cout<<"+";
    }
    std::cout<<std::endl;
}


double test_time(void(*func)(long long), long long N, void (*preambula)(long long)){
    double sum = 0;
    int size = REPEAT_SIZE;
    for(int i=0; i<size; i++){
        preambula(N);
        auto start{std::chrono::steady_clock::now()};
        func(N);
        auto finish{std::chrono::steady_clock::now()};
        std::chrono::duration<double> elapsed_seconds{finish - start};
        sum += elapsed_seconds.count();
    }
    return sum
#ifdef AVERAGE
            /size
#endif
    ;
}

std::string get_pow(int N){
    int s = 0;
    while(N%10==0){
        N/=10;
        s++;
    }
    return std::to_string(N)+"*10^"+std::to_string(s);
}

std::vector<std::vector<std::string>> init_vect(int size, int start, int N, int step){
    std::vector<std::vector<std::string>> mass;

    for(int i=0; i<1+size; i++){
        std::vector<std::string> mass_i;
        for(int j=0; j<=N; j++){
            if(j>0 && i==0) mass_i.push_back(get_pow(start+(j-1)*step));
            else            mass_i.push_back("");
        }
        mass.push_back(mass_i);
    }
    mass[0][0] = "N";
    return mass;
}

void init_y_file(FILE* file, int start, int N, int step){
    fprintf(file, "N");
    for(int i=0; i<N; i++)
        fprintf(file, ",%d", start+i*step);
    fprintf(file, "\n");
}

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const char tofu = 254u;
CONSOLE_CURSOR_INFO structCursorInfo;

void func_test(long long start, int N, long long step, std::vector<void(*)(long long)> funcs, void (*preambula)(long long)){
    FILE* file = fopen("res.csv", "w");

    GetConsoleCursorInfo(hConsole, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);

    std::vector<std::vector<std::string>> mass = init_vect(funcs.size(), start, N, step);
    init_y_file(file, start, N, step);

    for(int f=0; f<funcs.size(); f++){
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        mass[f+1][0] = "test_" + std::to_string(f+1);
        fprintf(file, "%s", mass[f+1][0].c_str());

        for(int i=0; i<N; i++){
            std::cout << "\r" + mass[f+1][0] + "\tcompleted " << i*100/N << "%\t";
            for(int p=0; p<N; p++){
                if(p<i)  SetConsoleTextAttribute(hConsole, 2);
                else     SetConsoleTextAttribute(hConsole, 4);
                std::cout<<tofu;
            }
            SetConsoleTextAttribute(hConsole, 7);
            double res = test_time(funcs[f], start+i*step, preambula);
            mass[f+1][i+1] = std::to_string(res);
            fprintf(file, ",%s", mass[f+1][i+1].c_str());
        }
        std::cout << "\r" + mass[f+1][0] + "\tcompleted 100%\t";
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 2);
        for(int p=0; p<N; p++)
            std::cout<<tofu;
        std::cout<<"\n";
        SetConsoleTextAttribute(hConsole, 7);
        fprintf(file, "\n");
    }

#ifndef SILENT
    table_print(mass);
#endif
    structCursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &structCursorInfo);

    fclose(file);
}

void null_func(long long N){}

void func_test(long long start, int N, long long step, std::vector<void(*)(long long)> funcs){
    func_test(start, N, step, funcs, null_func);
}
