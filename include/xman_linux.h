//
// Created by CHM on 2021/9/14.
//

#ifndef XMAN_XMANLINUX_H
#define XMAN_XMANLINUX_H

#include <string.h>
#include <stdlib.h>

#include <dlfcn.h>
#include <unistd.h>

#include "xman_linux_str.h"

typedef void* HMODULE;


#ifndef MAX_PATH
#define MAX_PATH    512
#endif

#define OUTAPI      extern "C" __attribute__((visibility("default")))
#if defined(__APPLE__)
#define LOCALAPI
#else
#define LOCALAPI    __attribute__((visibility("hidden")))
#endif

static inline void seterr(const char* err)
{
    if (err) {}
}

/**
 * @brief 和windows同名的获取函数地址
 * @param hModule
 * @param name
 * @return
 */
void* GetProcAddress(HMODULE hModule, char *name)
{
    void *sym = NULL;
    if (hModule)
    {
        sym = dlsym(hModule, name);
        if (!sym)
        {
            seterr(dlerror());
        }
    }

    return sym;
}

/**
 * @brief 此函数在Windows上有，所有需要做一个Linux版获取自身绝对路径的功能
 * @param hmod
 * @param filename
 * @param size
 * @return
 */
int GetModuleFileNameA(HMODULE hmod, char* filename, int size)
{
    *filename = 0;
    int ret = 0;
    if (!hmod)
    {
        size_t bytes = readlink("/proc/self/exe", filename, size);
        if (bytes > 0)
            filename[bytes < size - 1 ? bytes : size - 1] = '\0';

        ret = bytes;
    }

    return ret;
}



HMODULE GetModuleHandleA(const char* filename)
{
    return NULL;
}

HMODULE xmanLoadLibrary(char *plugin_name)
{
    HMODULE hmod = NULL;

    hmod = dlopen(plugin_name, RTLD_LAZY);
}

bool xmanFreeLibrary(HMODULE hModule)
{
    int ret = hModule ? dlclose(hModule) : 0;

    seterr(dlerror());
    return ret == 0;
}

#endif //XMAN_XMANLINUX_H
