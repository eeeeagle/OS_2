#pragma once
#include "Source.hpp"

DWORD WINAPI Sub(LPVOID param)
{
    EnterCriticalSection(&cs_sub);

    HANDLE file_values = CreateFileW(values_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE file_subtrahend = CreateFileW(div_a_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    HANDLE mapping_subtrahend = CreateFileMappingW(file_subtrahend, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == NULL || mapping_subtrahend == NULL)
        ExitThread(-1);

    double* values = (double*)MapViewOfFile(mapping_values, PAGE_READONLY, 0, 0, NULL);
    double* subtrahend = (double*)MapViewOfFile(mapping_subtrahend, PAGE_READONLY, 0, 0, NULL);
    if (values == NULL || subtrahend == NULL)
        ExitThread(-1);
    
    double res[VALUE_NUM];
    for (unsigned i = 0; i < VALUE_NUM; i++)
        res[i] = values[i] - *subtrahend;

    HANDLE file_res = CreateFileW(sub_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, res, sizeof(double) * VALUE_NUM, &written_bytes, NULL);

    LeaveCriticalSection(&cs_sub);
    return 0UL;
}