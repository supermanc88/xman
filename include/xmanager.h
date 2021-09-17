//
// Created by CHM on 2021/9/14.
//

#ifndef XMAN_XMANAGER_H
#define XMAN_XMANAGER_H

#include "xman_setting.h"
#include "load_module_helper.h"


namespace xman {
    int loadPlugins(const char* const* plugins, char *folder = XMAN_PLUGIN_PATH)
    {
        HMODULE base_module = GetModuleHandleA(NULL);
        for (int i = 0; i < (XMAN_MAX_PLUGIN_NUM - g_plugins_num) && plugins[i] != NULL; i++)
        {
            LoadModuleHelper *l = new LoadModuleHelper();
            if (l->load(plugins[i], base_module, folder))
            {
                for ( int j = 0; j < XMAN_MAX_PLUGIN_NUM; j++)
                {
                    if(g_plugins[j] == NULL)
                    {
                        g_plugins[j] = l;
                        break;
                    }
                }
                g_plugins_num++;
            }
            else
            {
                delete l;
            }
        }

        return g_plugins_num;
    }

    int loadPlugin(char *plugin, char *folder = XMAN_PLUGIN_PATH)
    {
        HMODULE base_module = GetModuleHandleA(NULL);
        if (XMAN_MAX_PLUGIN_NUM > g_plugins_num && plugin)
        {
            LoadModuleHelper *l = new LoadModuleHelper();
            if (l->load(plugin, base_module, folder))
            {
                for ( int j = 0; j < XMAN_MAX_PLUGIN_NUM; j++)
                {
                    if(g_plugins[j] == NULL)
                    {
                        g_plugins[j] = l;
                        break;
                    }
                }
                g_plugins_num++;
            }
            else
            {
                delete l;
            }
        }
        return g_plugins_num;
    }

    void unloadPlugins()
    {
        for (int i = g_plugins_num - 1; i >= 0; i--)
        {
            delete g_plugins[i];
            g_plugins[i] = NULL;
        }

        g_plugins_num = 0;
    }

    void unloadPlugin(char *plugin, char *folder = XMAN_PLUGIN_PATH)
    {
        HMODULE base_module = GetModuleHandleA(NULL);
        char full_plugin_name[MAX_PATH] = {0};
        if (PathIsRelativeA(plugin))
        {
            GetModuleFileNameA(base_module, full_plugin_name, MAX_PATH);
            PathRemoveFileSpecA(full_plugin_name);
            PathAppendA(full_plugin_name, folder);
            PathAppendA(full_plugin_name, plugin);
        }
        else
        {
            strcpy(full_plugin_name, plugin);
        }

        for (int i = 0; i < g_plugins_num; i++)
        {
            if (strcmp(g_plugins[i]->GetPluginPath(), full_plugin_name) == 0)
            {
                delete g_plugins[i];
                g_plugins[i] = NULL;

                g_plugins_num--;

                break;
            }
        }

    }


    // 利用c++的构造和析构
    // 适用于用完就卸载的插件
    struct AutoLoadPlugins
    {
        AutoLoadPlugins(const char* const* plugins, char *folder = XMAN_PLUGIN_PATH)
        {
            loadPlugins(plugins, folder);
            this->plugins = (char **)plugins;
            this->folder = folder;
        }

        ~AutoLoadPlugins()
        {
//            unloadPlugins();
            for (int i = 0; plugins[i] != NULL; i++)
            {
                unloadPlugin(plugins[i], folder);
            }
        }

        char ** plugins = NULL;
        char *folder = NULL;
    };

} // namespace xman

#endif //XMAN_XMANAGER_H
