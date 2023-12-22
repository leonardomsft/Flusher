#include <windows.h>
#include <stdio.h>
#include <chrono>


void PrintUsage()
{
    wprintf(L"\n\nFlusher - Volume Flushing Tool \n");
    wprintf(L"Created by Leonardo Fagundes. No rights reserved.\n");
    wprintf(L"https://github.com/leonardomsft/Flusher\n\n");

    wprintf(L"Usage: Flusher.exe <Volume Letter>\n\n");
    wprintf(L"\tExample: Flusher.exe c:\n\n");
}

int wmain(int argc, wchar_t* argv[])
{
    HANDLE hFile = NULL;
    WCHAR wszpath[MAX_PATH] = {};
    std::chrono::duration<double> elapsed;

    //Capture start time
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    

    if (argc != 2)
    {
        wprintf(L"ERROR: Invalid parameter.");

        PrintUsage();

        goto exit;

    }

    if (wcsnlen(argv[1], 10) != 2)
    {
        wprintf(L"ERROR: Invalid parameter.");

        PrintUsage();

        goto exit;

    }

    if (isalpha((char)argv[1][0]) && argv[1][1] == ':')
    {
        swprintf_s(wszpath, 10, L"\\\\.\\%s", argv[1]);
    }
    else
    {
        wprintf(L"ERROR: Invalid parameter.");

        PrintUsage();

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
        wprintf(L"ERROR %d attempting to open a volume handle.\n", GetLastError());

        goto exit;
    }

    //Flush
    if (!FlushFileBuffers(hFile))
    {
        wprintf(L"ERROR %d attempting to call FlushFileBuffers. Exiting.\n", GetLastError());

        goto exit;
    }


    //Capture finish time
    finish = std::chrono::high_resolution_clock::now();

    //Calculate elapsed time
    elapsed = finish - start;

    wprintf(L"SUCCESS flushing volume %s \nTotal elapsed time: %0.7f seconds\n", wszpath, elapsed);

exit:

    if (hFile != NULL && hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    return 0;

}
