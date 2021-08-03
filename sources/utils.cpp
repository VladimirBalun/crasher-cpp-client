#include "utils.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <winnt.h>
    #include <windows.h>
#endif

std::string Crashser::getOSName()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    return "Windows";
#elif defined(__APPLE__) || defined(__MACH__)
    return "Mac OSX";
#elif defined(__linux__)
    return "Linux";
#elif defined(__FreeBSD__)
    return "FreeBSD";
#elif defined(__unix) || defined(__unix__)
    return "Unix";
#else
    return "Other";
#endif
}

std::string Crashser::getOSVersion()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    OSVERSIONINFOEX info;
    ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
    info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx(&info);
    return std::to_string(info.dwMajorVersion) + std::to_string(info.dwMinorVersion);
#else
    // TODO: need to implement
    return "";
#endif
}
