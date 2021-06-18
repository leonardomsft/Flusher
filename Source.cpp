#include <windows.h>
#include <stdio.h>
#include <chrono>

int wmain(int argc, wchar_t* argv[])
{
    HANDLE hFile = NULL;
    WCHAR wszpath[MAX_PATH] = {};
    std::chrono::duration<double> elapsed;

    //Capture start time
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    
    if (argc == 2)
    {
        if (!_wcsicmp(argv[1], L"C:")) wcscpy_s(wszpath, L"\\\\.\\C:");
        if (!_wcsicmp(argv[1], L"D:")) wcscpy_s(wszpath, L"\\\\.\\D:");
        if (!_wcsicmp(argv[1], L"E:")) wcscpy_s(wszpath, L"\\\\.\\E:");
        if (!_wcsicmp(argv[1], L"F:")) wcscpy_s(wszpath, L"\\\\.\\F:");
        if (!_wcsicmp(argv[1], L"G:")) wcscpy_s(wszpath, L"\\\\.\\G:");
        if (!_wcsicmp(argv[1], L"H:")) wcscpy_s(wszpath, L"\\\\.\\H:");
        if (!_wcsicmp(argv[1], L"I:")) wcscpy_s(wszpath, L"\\\\.\\I:");
        if (!_wcsicmp(argv[1], L"S:")) wcscpy_s(wszpath, L"\\\\.\\S:");

    }


    if (argc != 2 || wcsnlen(wszpath, MAX_PATH) != 6)
    {
        wprintf(L"ERROR: Missing Volume Letter. Please specify the Volume to flush.\n  Example: Flusher.exe C:\n");

        goto exit;

    }


    hFile = CreateFile(wszpath,
        GENERIC_READ | GENERIC_WRITE,       // open for read/write
        FILE_SHARE_READ | FILE_SHARE_WRITE, // shared read/write
        NULL,                               // default security
        OPEN_EXISTING,                      // open existing
        FILE_ATTRIBUTE_NORMAL,              // normal file
        NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateFile ERROR: %d. Exiting.\n", GetLastError());

        goto exit;
    }

    //Flush
    if (!FlushFileBuffers(hFile))
    {
        wprintf(L"FlushFileBuffers ERROR: %d. Exiting.\n", GetLastError());

        goto exit;
    }


    //Capture finish time
    finish = std::chrono::high_resolution_clock::now();

    //Calculate elapsed time
    elapsed = finish - start;

    wprintf(L"Total elapsed time: %0.7f seconds\n", elapsed);

exit:

    if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    return 0;

}
