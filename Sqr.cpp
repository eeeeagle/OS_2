#pragma once
#include "Source.hpp"

DWORD WINAPI Sqr(LPVOID param)
{
    EnterCriticalSection(&cs_sqr);

    HANDLE file_values = CreateFileW(sub_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    HANDLE mapping_values = CreateFileMappingW(file_values, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_values == NULL)
        ExitThread(-1);

    double* values = (double*)MapViewOfFile(mapping_values, PAGE_READONLY, 0, 0, NULL);
    if (values == NULL)
        ExitThread(-1);

    double res[VALUE_NUM];
    for (unsigned i = 0; i < VALUE_NUM; i++)
        res[i] = values[i] * values[i];

    HANDLE file_res = CreateFileW(sqr_path, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, res, sizeof(double) * VALUE_NUM, &written_bytes, NULL);

    LeaveCriticalSection(&cs_sqr);
    return 0UL;
}