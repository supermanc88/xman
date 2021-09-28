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
        for (int i = 0; i < (XMAN_MAX_PLUGIN_NUM - PLUGIN_STORE_NUM_VAR(PROJECT_NAME)) && plugins[i] != NULL; i++)
        {
            LoadModuleHelper *l = new LoadModuleHelper();
            if (l->load(plugins[i], base_module, folder))
            {
                for ( int j = 0; j < XMAN_MAX_PLUGIN_NUM; j++)
                {
                    if(PLUGIN_STORE_VAR(PROJECT_NAME)[j] == NULL)
                    {
                        PLUGIN_STORE_VAR(PROJECT_NAME)[j] = l;
                        break;
                    }
                }
                PLUGIN_STORE_NUM_VAR(PROJECT_NAME)++;
            }
            else
            {
                delete l;
            }
        }

        return PLUGIN_STORE_NUM_VAR(PROJECT_NAME);
    }

    int loadPlugin(char *plugin, char *folder = XMAN_PLUGIN_PATH)
    {
        HMODULE base_module = GetModuleHandleA(NULL);
        if (XMAN_MAX_PLUGIN_NUM > PLUGIN_STORE_NUM_VAR(PROJECT_NAME) && plugin)
        {
            LoadModuleHelper *l = new LoadModuleHelper();
            if (l->load(plugin, base_module, folder))
            {
                for ( int j = 0; j < XMAN_MAX_PLUGIN_NUM; j++)
                {
                    if(PLUGIN_STORE_VAR(PROJECT_NAME)[j] == NULL)
                    {
                        PLUGIN_STORE_VAR(PROJECT_NAME)[j] = l;
                        break;
                    }
                }
                PLUGIN_STORE_NUM_VAR(PROJECT_NAME)++;
            }
            else
            {
                delete l;
            }
        }
        return PLUGIN_STORE_NUM_VAR(PROJECT_NAME);
    }

    void unloadPlugins()
    {
        for (int i = PLUGIN_STORE_NUM_VAR(PROJECT_NAME) - 1; i >= 0; i--)
        {
            delete PLUGIN_STORE_VAR(PROJECT_NAME)[i];
            PLUGIN_STORE_VAR(PROJECT_NAME)[i] = NULL;
        }

        PLUGIN_STORE_NUM_VAR(PROJECT_NAME) = 0;
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

        for (int i = 0; i < PLUGIN_STORE_NUM_VAR(PROJECT_NAME); i++)
        {
            if (strcmp(PLUGIN_STORE_VAR(PROJECT_NAME)[i]->GetPluginPath(), full_plugin_name) == 0)
            {
                delete PLUGIN_STORE_VAR(PROJECT_NAME)[i];
                PLUGIN_STORE_VAR(PROJECT_NAME)[i] = NULL;

                PLUGIN_STORE_NUM_VAR(PROJECT_NAME)--;

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

        char ** plugins;
        char *folder;
    };

} // namespace xman

#endif //XMAN_XMANAGER_H
