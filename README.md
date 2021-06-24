# Flusher

Flusher.exe is a tool that triggers the I/O manager to flush the specified volume. As a result, all buffered data is written to the disk.

Typically when processes call the WriteFile function, data is written to an internal buffer controlled by the operating system, also known as Write-Back cache. Later, the cache manager's lazy writer thread wakes up and flushes the dirty pages to the disk. A complex algorithm makes these decisions in order to maximize performance. 

This tool simply flushes all dirty pages from the specified volume and causes them to be immediatelly written to the disk (requires Admin privileges):

![Alt text](screenshots/example1.png?raw=true "Image1")



# Download

https://github.com/leonardomsft/Flusher/releases/download/0.1/Flusher.exe



# References

FlushFileBuffers function (fileapi.h) https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-flushfilebuffers

Write-Back Caching and Lazy Writing Windows Internals, Sixth Edition, Part 2, Chapter 11, Page 379.
