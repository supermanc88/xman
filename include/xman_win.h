//
// Created by CHM on 2021/9/14.
//

#ifndef XMAN_XMANWIN_H
#define XMAN_XMANWIN_H

HMODULE xmanLoadLibrary(char *plugin_name)
{
    // 以绝对路径加载，防止动态库劫持
    return LoadLibraryExA(plugin_name, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
}

bool xmanFreeLibrary(HMODULE hModule)
{
    return !!FreeLibrary(hModule);
}



#endif //XMAN_XMANWIN_H
