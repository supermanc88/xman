//
// Created by CHM on 2021/9/14.
//

#ifndef XMAN_XMANAGER_H
#define XMAN_XMANAGER_H

#include "xman_setting.h"
#include "load_module_helper.h"


namespace xman {
    static LoadModuleHelper* m_plugins[200] = {NULL};
    static int m_num_plugins = 0;

    int loadPlugins(char *plugins[], char *folder = XMAN_PLUGIN_PATH)
    {
        for (int i = 0; i < 200 && plugins[i] != NULL; i++)
        {
            LoadModuleHelper *l = new LoadModuleHelper();
            if (l->load(plugins[i], NULL, folder))
            {
                m_plugins[m_num_plugins++] = l;
            }
            else
            {
                delete l;
            }
        }

        return m_num_plugins;
    }

    void unloadPlugins()
    {
        for (int i = m_num_plugins - 1; i >= 0; i--)
        {
            delete m_plugins[i];
            m_plugins[i] = NULL;
        }

        m_num_plugins = 0;
    }


    // 利用c++的构造和析构
    struct AutoLoadPlugins
    {
        AutoLoadPlugins(char *plugins[], char *folder = XMAN_PLUGIN_PATH)
        {
            loadPlugins(plugins, folder);
        }

        ~AutoLoadPlugins()
        {
            unloadPlugins();
        }
    };

} // namespace xman

#endif //XMAN_XMANAGER_H
