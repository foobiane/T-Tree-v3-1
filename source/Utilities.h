#pragma once

#include <filesystem>
#include <limits.h>

#ifdef _WIN32
#include <libloaderapi.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;

class Utilities {
public:
    static fs::path getBinaryLocation() {
        fs::path res;

#ifdef _WIN32
        char buf[PATH_MAX];
        GetModuleFileNameA(NULL, buf, PATH_MAX);
        res = fs::canonical(fs::path(buf));
#endif

#ifdef __APPLE__
        char buf[PATH_MAX];
        uint32_t bufSize = PATH_MAX;
        _NSGetExecutablePath(buf, &bufSize);
        res = fs::canonical(fs::path(buf));

        // Since we wrap the Mac standalone binary in a .app package, we need to back up 4 directories
        res /= ".."; res /= ".."; res /= "..";
        res = fs::canonical(res);
#endif

#ifdef __linux__
        res = fs::canonical(fs::path("/proc/self/exe"));
#endif

        return res;
    }
};