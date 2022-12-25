#pragma once
#include "Source.hpp"

DWORD WINAPI Sqrt(LPVOID param)
{
    HANDLE file_value = CreateFile(L"\\\\.\\file\\sqrt_value", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    while (true)
    {
        double_convert received_value;
        DWORD real_reading_value = 0;

        ReadFile(file_value, &received_value.bytes, sizeof(double), &real_reading_value, NULL);

        double_convert res;
        DWORD real_reading_res = 0;
        res.value = sqrt(received_value.value);

        HANDLE file_res = CreateFile(L"\\\\.\\file\\sqrt_res", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(file_res, res.bytes, sizeof(double), &real_reading_res, NULL);
    }
}