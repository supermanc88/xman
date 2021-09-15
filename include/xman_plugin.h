//
// Created by CHM on 2021/9/15.
//

/************************ 所有的插件必须加载此头文件 ************************/

#ifndef XMAN_XMAN_PLUGIN_H
#define XMAN_XMAN_PLUGIN_H

#include <stdlib.h>
#include <string.h>

#ifdef __GNUC__
#define OUTAPI      extern "C" __attribute__((visibility("default")))
#if defined(__APPLE__)
#define LOCALAPI
#else
#define LOCALAPI    __attribute__((visibility("hidden")))
#endif
#else
#define OUTAPI      extern "C" __declspec(dllexport)
#define LOCALAPI
#endif // __GNUC__

#ifndef MAX_PATH
#define MAX_PATH 512
#endif

// 由插件去填充
static char xman_plugin_version[MAX_PATH] = {0};

// 后面的是为了防重名
OUTAPI void get_version_XgoCzmhoeZUiFBwEKdZ1(char *version, int version_len)
{
    strncpy(version, xman_plugin_version, strlen(xman_plugin_version) < version_len ? strlen(xman_plugin_version) : version_len);
}

#endif //XMAN_XMAN_PLUGIN_H
