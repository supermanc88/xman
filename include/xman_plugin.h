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


#include <vector>
#include <string>
std::vector<std::string> xman_func_lists;

#define XMAN_ADD_SYMBOL(x)          xman_func_lists.push_back(#x)

// 由插件去填充
static char xman_plugin_version[MAX_PATH] = {0};

// 后面的是为了防重名
OUTAPI void get_version_XgoCzmhoeZUiFBwEKdZ1(char *version, int version_len)
{
    strncpy(version, xman_plugin_version, strlen(xman_plugin_version) < version_len ? strlen(xman_plugin_version) : version_len);
}

// 这里只声明了一个初始化函数，具体实现由插件开发者提供。
// 插件管理程序会在加载插件后，自动去调用此函数。
// 没有此函数的话，会卸载插件。
// 例如在此函数中填充插件版本号
OUTAPI void init_plugin_XgoCzmhoeZUiFBwEKdZ1();

OUTAPI void free_plugin_XgoCzmhoeZUiFBwEKdZ1();

// 此函数在这没什么实际作用，就是为了防止开发者忘记实现初始化及卸载函数
// 不实现的话，编译就报错。
LOCALAPI void prevent_forgetting_XgoCzmhoeZUiFBwEKdZ1()
{
    init_plugin_XgoCzmhoeZUiFBwEKdZ1();
    free_plugin_XgoCzmhoeZUiFBwEKdZ1();
}

#endif //XMAN_XMAN_PLUGIN_H
