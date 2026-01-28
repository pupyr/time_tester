#pragma once

#include <conio.h>
#include <iostream>
#include <inttypes.h>
#include <vector>
#include <string>
#include <chrono>
#include <windows.h>

#ifndef REPEAT_SIZE
#define REPEAT_SIZE 10
#endif

void func_test(long long start, int N, long long step, std::vector<void(*)(long long)> funcs);
