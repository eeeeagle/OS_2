#pragma once
#include "Source.hpp"

DWORD WINAPI Div(LPVOID param)
{
    DivParams* real_param = (DivParams*)param;

    EnterCriticalSection(&cs_div);

    HANDLE file_value = CreateFileW(real_param->in.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE mapping_value = CreateFileMappingW(file_value, 0, PAGE_READONLY, 0, 0, NULL);
    if (mapping_value == NULL)
        ExitThread(-1);

    double* value = (double*)MapViewOfFile(mapping_value, PAGE_READONLY, 0, 0, NULL);
    if (value == NULL)
        ExitThread(-1);

    double res = *value / real_param->divider;

    HANDLE file_res = CreateFileW(real_param->out.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD written_bytes = 0;
    WriteFile(file_res, &res, sizeof(double), &written_bytes, NULL);

    LeaveCriticalSection(&cs_div);
    return 0UL;
}