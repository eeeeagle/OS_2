#include <Windows.h>
#include <iostream>

#ifndef SOURCE
#define SOURCE

union double_convert
{
    double value = 0.0;
    byte bytes[sizeof(double)];
};

DWORD WINAPI Sum(LPVOID param);
DWORD WINAPI Div(LPVOID param);
DWORD WINAPI Sub(LPVOID param);
DWORD WINAPI Sqrt(LPVOID param);

#endif