Tool to flush all buffered data to the disk.

Typically when processes call the WriteFile function, data is written to an internal buffer controlled by the operating system, also known as Write-Back cache. Later, the cache manager's lazy writer thread wakes up and flushes the dirty pages to the actual disk. This tool simply flushes all dirty pages from the specified volume and causes them to be written to the disk.


References

FlushFileBuffers function (fileapi.h) https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-flushfilebuffers

Write-Back Caching and Lazy Writing Windows Internals, Sixth Edition, Part 2, Chapter 11, Page 379.
