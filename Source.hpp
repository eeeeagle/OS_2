#ifndef SOURCE
#define SOURCE

#include <Windows.h>
#include <iostream>

constexpr auto VALUE_NUM = 3;

static const wchar_t* values_path  = L"\\\\.\\FileMapping\\Values";
static const wchar_t* sum_a_path   = L"\\\\.\\FileMapping\\SumA";
static const wchar_t* sum_b_path   = L"\\\\.\\FileMapping\\SumB";
static const wchar_t* div_a_path   = L"\\\\.\\FileMapping\\DivA";
static const wchar_t* div_b_path   = L"\\\\.\\FileMapping\\DivA";
static const wchar_t* sub_path     = L"\\\\.\\FileMapping\\Sub";
static const wchar_t* sqr_path     = L"\\\\.\\FileMapping\\Sqr";

static CRITICAL_SECTION cs_sum;
static CRITICAL_SECTION cs_div;
static CRITICAL_SECTION cs_sub;
static CRITICAL_SECTION cs_sqr;


struct SumParams
{
    const std::wstring in, out;
};

struct DivParams
{
    const std::wstring in, out;
    int divider;
};


DWORD WINAPI Sum(LPVOID param);
DWORD WINAPI Div(LPVOID param);
DWORD WINAPI Sub(LPVOID param);
DWORD WINAPI Sqr(LPVOID param);

#endif