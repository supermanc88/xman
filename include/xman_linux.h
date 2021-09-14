//
// Created by CHM on 2021/9/14.
//

#ifndef XMAN_XMANLINUX_H
#define XMAN_XMANLINUX_H

#include <string.h>
#include <stdlib.h>

#include <dlfcn.h>
#include <unistd.h>

typedef void* HMODULE;

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
        sym = slsym(hModule, name);
        if (!sym)
        {
            seterr(slerror());
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

    if (!hmod)
    {
        size_t bytes = readlink("/proc/self/exe", filename, size);
        if (bytes > 0)
            filename[bytes < size - 1 ? bytes : size - 1] = '\0';
    }

    return bytes;
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
