#pragma once
#include "Source.hpp"

DWORD WINAPI Sum(LPVOID param)
{
    HANDLE file_a = CreateFile(L"\\\\.\\file\\sum_a", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE file_b = CreateFile(L"\\\\.\\file\\sum_b", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    while (true)
    {
        double_convert received_a;
        double_convert received_b;
        DWORD real_reading_a = 0;
        DWORD real_reading_b = 0;

        ReadFile(file_a, &received_a.bytes, sizeof(double), &real_reading_a, NULL);
        ReadFile(file_b, &received_b.bytes, sizeof(double), &real_reading_b, NULL);

        double_convert res;
        DWORD real_reading_res = 0;
        res.value = received_a.value + received_b.value;

        HANDLE file_sum = CreateFile(L"\\\\.\\file\\sum_res", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(file_sum, res.bytes, sizeof(double), &real_reading_res, NULL);
    }
}