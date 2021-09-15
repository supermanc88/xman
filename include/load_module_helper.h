//
// Created by CHM on 2021/9/14.
//

// 用来做跨平台加载动态库通用接口

#ifndef XMAN_LOADMODULEHELPER_H
#define XMAN_LOADMODULEHELPER_H

#ifdef __GNUC__
#include "xman_linux.h"
#else
#include "xman_win.h"
#endif // __GNUC__

namespace xman {
    class LoadModuleHelper;

    static LoadModuleHelper* g_plugins[200] = {NULL};
    static int g_plugins_num = 0;

    class LoadModuleHelper
    {
        public:
        LoadModuleHelper() : m_hModule(NULL)
        {
            memset(m_plugin_path, MAX_PATH, 0);
        }

        bool load(const char *plugin_name, HMODULE base_module = NULL, char *folder = "")
        {
            unload();

            // 这里需要判断动态库是否已经加载


            // 判断是否是绝对路径
            // 如果不是绝对路径，就补全
            char full_plugin_name[MAX_PATH] = {0};
            if (PathIsRelativeA(plugin_name))
            {
                GetModuleFileNameA(base_module, full_plugin_name, MAX_PATH);
                PathRemoveFileSpecA(full_plugin_name);
                PathAppendA(full_plugin_name, folder);
                PathAppendA(full_plugin_name, plugin_name);

                if (IsAlreadyLoaded(full_plugin_name))
                    return false;
                m_hModule = xmanLoadLibrary(full_plugin_name);
                strcpy(m_plugin_path, full_plugin_name);
            }
            else
            {
                if (IsAlreadyLoaded(full_plugin_name))
                    return false;
                m_hModule = xmanLoadLibrary((char *)plugin_name);
            }

            return m_hModule != NULL;
        }

        void unload()
        {
            if (m_hModule)
            {
                xmanFreeLibrary(m_hModule);
            }
        }

        char *GetPluginPath()
        {
            return m_plugin_path;
        }

        private:
        bool IsAlreadyLoaded(char *plugin_path)
        {
            for (int i = 0; i < g_plugins_num; i++)
            {
                if (strcmp(g_plugins[i]->GetPluginPath(), plugin_path) == 0)
                    return true;
            }
            return false;
        }
        HMODULE m_hModule;
        char m_plugin_path[MAX_PATH];
    };
}

#endif //XMAN_LOADMODULEHELPER_H
