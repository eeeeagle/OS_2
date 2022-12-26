#pragma once
#include "Source.hpp"

DWORD WINAPI Sum(LPVOID param)
{
    SumParams* real_param = (SumParams*)param;
    EnterCriticalSection(&cs_sum);

    HANDLE file_values = CreateFileW(real_param->in.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == NULL)
        ExitThread(-1);

    double* values = (double*) MapViewOfFile(mapping_values, PAGE_READONLY, 0, 0, NULL);
    if (values == NULL)
        ExitThread(-1);

    double res = 0.0;
    for (unsigned i = 0; i < VALUE_NUM; i++)
        res += values[i];

    HANDLE file_res = CreateFileW(real_param->out.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    LeaveCriticalSection(&cs_sum);
    return 0UL;
}