#include <Windows.h>
#include <iostream>

constexpr auto VALUE_NUM = 3;

const wchar_t* path_values  = L".\\values.dat";
const wchar_t* path_sum_1   = L".\\sum_a.dat";
const wchar_t* path_sum_2   = L".\\sum_b.dat";
const wchar_t* path_div_1   = L".\\div_a.dat";
const wchar_t* path_div_2   = L".\\div_b.dat";
const wchar_t* path_sub     = L".\\sub.dat";
const wchar_t* path_sqr     = L".\\sqr.dat";

CRITICAL_SECTION cs_wait_1;
CRITICAL_SECTION cs_wait_2;
CRITICAL_SECTION cs_sum_1;
CRITICAL_SECTION cs_sum_2;
CRITICAL_SECTION cs_div_1;
CRITICAL_SECTION cs_div_2;
CRITICAL_SECTION cs_sub;
CRITICAL_SECTION cs_sqr;

DWORD WINAPI Sum_1(LPVOID param)
{
    std::cout << "[SUM_1] INITIALIZED" << '\n';
    while (cs_sum_1.LockCount != -1);
    EnterCriticalSection(&cs_sum_1);
    EnterCriticalSection(&cs_wait_1);

    std::cout << "[SUM_1] STARTED. READING FROM FILE..." << '\n';

    HANDLE file_values = CreateFileW(path_values, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == 0)
        ExitProcess(-11);

    double* values = (double*)MapViewOfFile(mapping_values, FILE_MAP_READ, 0, 0, 0);
    if (values == nullptr)
        ExitProcess(-12);

    std::cout << "[SUM_1] READ FILE. CALCULATING SUM..." << '\n';

    double res = 0.0;
    for (unsigned i = 0; i < VALUE_NUM; i++)
        res += values[i];
    UnmapViewOfFile(values);

    std::cout << "[SUM_1] CALCULATED SUM = " << res << '\n';
    std::cout << "[SUM_1] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_sum_1, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    std::cout << "[SUM_1] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_sum_1);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}

DWORD WINAPI Sum_2(LPVOID param)
{
    std::cout << "[SUM_2] INITIALIZED" << '\n';
    while (cs_sum_2.LockCount != -1);
    EnterCriticalSection(&cs_sum_2);
    EnterCriticalSection(&cs_wait_1);

    std::cout << "[SUM_2] STARTED. READING FROM FILE..." << '\n';

    HANDLE file_values = CreateFileW(path_sqr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == 0)
        ExitProcess(-13);

    double* values = (double*)MapViewOfFile(mapping_values, FILE_MAP_READ, 0, 0, 0);
    if (values == nullptr)
        ExitProcess(-14);

    std::cout << "[SUM_2] READ FILE. CALCULATING SUM..." << '\n';

    double res = 0.0;
    for (unsigned i = 0; i < VALUE_NUM; i++)
        res += values[i];
    UnmapViewOfFile(values);

    std::cout << "[SUM_2] CALCULATED SUM = " << res << '\n';
    std::cout << "[SUM_2] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_sum_2, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    std::cout << "[SUM_2] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_sum_2);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}

DWORD WINAPI Div_1(LPVOID param)
{
    std::cout << "[DIV_1] INITIALIZED" << '\n';
    while (cs_div_1.LockCount != -1);
    EnterCriticalSection(&cs_div_1);
    EnterCriticalSection(&cs_wait_1);

    std::cout << "[DIV_1] STARTED. READING FROM FILE..." << '\n';

    HANDLE file_value = CreateFileW(path_sum_1, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_value = CreateFileMappingW(file_value, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_value == 0)
        ExitProcess(-15);

    double* value = (double*)MapViewOfFile(mapping_value, FILE_MAP_READ, 0, 0, NULL);
    if (value == nullptr)
        ExitProcess(-16);

    std::cout << "[DIV_1] READ FILE. CALCULATING DIV..." << '\n';

    double res = *value / VALUE_NUM;
    UnmapViewOfFile(value);

    std::cout << "[DIV_1] CALCULATED DIV = " << res << '\n';
    std::cout << "[DIV_1] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_div_1, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    std::cout << "[DIV_1] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_div_1);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}

DWORD WINAPI Div_2(LPVOID param)
{
    std::cout << "[DIV_2] INITIALIZED" << '\n';
    while (cs_div_2.LockCount != -1);
    EnterCriticalSection(&cs_div_2);
    EnterCriticalSection(&cs_wait_1);

    std::cout << "[DIV_2] STARTED. READING FROM FILE..." << '\n';

    HANDLE file_value = CreateFileW(path_sum_2, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_value = CreateFileMappingW(file_value, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_value == 0)
        ExitProcess(-17);

    double* value = (double*)MapViewOfFile(mapping_value, FILE_MAP_READ, 0, 0, NULL);
    if (value == nullptr)
        ExitProcess(-18);

    std::cout << "[DIV_2] READ FILE. CALCULATING DIV..." << '\n';

    double res = *value / 2.0;
    UnmapViewOfFile(value);

    std::cout << "[DIV_2] CALCULATED DIV = " << res << '\n';
    std::cout << "[DIV_2] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_div_2, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    std::cout << "[DIV_2] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_div_2);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}

DWORD WINAPI Sub(LPVOID param)
{
    std::cout << "[SUB] INITIALIZED" << '\n';
    while (cs_sub.LockCount != -1);
    EnterCriticalSection(&cs_sub);
    EnterCriticalSection(&cs_wait_1);

    std::cout << "[SUB] STARTED. READING FROM FILES..." << '\n';

    HANDLE file_values = CreateFileW(path_values, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE file_subtrahend = CreateFileW(path_div_1, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    HANDLE mapping_subtrahend = CreateFileMappingW(file_subtrahend, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == 0 || mapping_subtrahend == 0)
        ExitProcess(-19);

    std::cout << "[SUB] READ FILES. CALCULATING SUB..." << '\n';

    double* values = (double*)MapViewOfFile(mapping_values, FILE_MAP_READ, 0, 0, NULL);
    double* subtrahend = (double*)MapViewOfFile(mapping_subtrahend, FILE_MAP_READ, 0, 0, NULL);
    if (values == nullptr || subtrahend == nullptr)
        ExitProcess(-20);

    double res[VALUE_NUM];
    for (unsigned i = 0; i < VALUE_NUM; i++)
    {
        res[i] = values[i] - *subtrahend;
        std::cout << "[SUB] CALCULATED SUB[" << i << "] = " << res[i] << '\n';
    }
    UnmapViewOfFile(values);
    UnmapViewOfFile(subtrahend);

    std::cout << "[SUB] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_sub, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, res, sizeof(double) * VALUE_NUM, &written_bytes, NULL);

    std::cout << "[SUB] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_sub);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}

DWORD WINAPI Sqr(LPVOID param)
{
    std::cout << "[SQR] INITIALIZED" << '\n';
    while (cs_sqr.LockCount != -1);
    EnterCriticalSection(&cs_wait_1);
    EnterCriticalSection(&cs_sqr);

    std::cout << "[SQR] STARTED. READING FROM FILES..." << '\n';

    HANDLE file_values = CreateFileW(path_sub, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == 0)
        ExitProcess(-21);

    double* values = (double*)MapViewOfFile(mapping_values, FILE_MAP_READ, 0, 0, NULL);
    if (values == nullptr)
        ExitProcess(-22);

    std::cout << "[SQR] READ FILE. CALCULATING SQR..." << '\n';

    double res[VALUE_NUM];
    for (unsigned i = 0; i < VALUE_NUM; i++)
    {
        res[i] = values[i] * values[i];
        std::cout << "[SQR] CALCULATED SQR[" << i << "] = " << res[i] << '\n';
    }
    UnmapViewOfFile(values);

    std::cout << "[SQR] WRITING TO FILE..." << '\n';

    HANDLE file_res = CreateFileW(path_sqr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, res, sizeof(double) * VALUE_NUM, &written_bytes, NULL);

    std::cout << "[SQR] WROTE TO FILE. END." << '\n';

    LeaveCriticalSection(&cs_sqr);
    LeaveCriticalSection(&cs_wait_2);
    ExitThread(0);
}