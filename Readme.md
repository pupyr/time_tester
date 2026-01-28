# Time tester

## Requirements

g++

make

python:

    - pandas
    - matplotlib

## Run

Анализируемые функции перечисляются в main.cpp

Функция func_test принимает 3 параметра (начало диапазона, количество шагов, размер шага) и массив функций 

`make`

`make rep=10000` - для увеличения точности

`make sum` - если задача мала

`make sum rep=10000` - если задача слишком мала

`make run_only` - без построения графиков
