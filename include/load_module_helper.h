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

#include "xman_obj_helper.h"

namespace xman {
    class LoadModuleHelper;

//    static LoadModuleHelper* g_plugins[XMAN_MAX_PLUGIN_NUM] = {NULL};
//    static int g_plugins_num = 0;

#ifndef PROJECT_NAME
// #define PROJECT_NAME

// 当发现没有定义这个宏的时候，直接编译报错
#error No defined constant Symbol "PROJECT_NAME"
#endif // PROJECT_NAME

#define PLUGIN_STORE_DEFINE(x) \
static LoadModuleHelper* g_plugins_##x[XMAN_MAX_PLUGIN_NUM] = {NULL};
#define PLUGIN_STORE_VAR(x) g_plugins_##x

    PLUGIN_STORE_DEFINE(PROJECT_NAME)

#define PLUGIN_STORE_NUM_DEFINE(x) \
static int g_plugins_num_##x = 0;
    PLUGIN_STORE_NUM_DEFINE(PROJECT_NAME)
#define PLUGIN_STORE_NUM_VAR(x) g_plugins_num_##x

#define XMAN_PLUGIN_FUNC_GET_VERSION            "get_version_XgoCzmhoeZUiFBwEKdZ1"
#define XMAN_PLUGIN_FUNC_INIT_PLUGIN            "init_plugin_XgoCzmhoeZUiFBwEKdZ1"
#define XMAN_PLUGIN_FUNC_FREE_PLUGIN            "free_plugin_XgoCzmhoeZUiFBwEKdZ1"
#define XMAN_PLUGIN_FUNC_CREATE_OBJECT          "xman_create_object_XgoCzmhoeZUiFBwEKdZ1"


    class LoadModuleHelper
    {
        public:
        LoadModuleHelper() : m_hModule(NULL)
        {
            memset(m_full_plugin_path, 0, MAX_PATH);
            memset(m_plugin_version, 0, MAX_PATH);
            memset(m_plugin_name, 0, MAX_PATH);
            memset(m_plugin_folder, 0, MAX_PATH);
            m_create_object_fun = NULL;
        }
        ~LoadModuleHelper()
        {
            unload();
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
                strcpy(m_full_plugin_path, full_plugin_name);
            }
            else
            {
                if (IsAlreadyLoaded(full_plugin_name))
                    return false;
                m_hModule = xmanLoadLibrary((char *)plugin_name);
                strcpy(m_full_plugin_path, plugin_name);
            }

            // 加载初始化接口
            typedef void (*I)();
            I init_plugin = (I)GetProcAddress(m_hModule, XMAN_PLUGIN_FUNC_INIT_PLUGIN);

            typedef void (*G)(char *, int);
            G get_version = (G)GetProcAddress(m_hModule, XMAN_PLUGIN_FUNC_GET_VERSION);

            typedef void (*F)();
            F free_plugin = (F)GetProcAddress(m_hModule, XMAN_PLUGIN_FUNC_FREE_PLUGIN);

            typedef xmanObject* (*C)();
            C create_object = (C)GetProcAddress(m_hModule, XMAN_PLUGIN_FUNC_CREATE_OBJECT);

            m_create_object_fun = (void *)create_object;

            if (!init_plugin || !get_version || !free_plugin)
            {
                xmanFreeLibrary(m_hModule);
                m_hModule = NULL;
                memset(m_full_plugin_path, 0, MAX_PATH);
                return false;
            }

            init_plugin();
            get_version(m_plugin_version, MAX_PATH);

            strcpy(m_plugin_name, plugin_name);
            strcpy(m_plugin_folder, folder);

            return m_hModule != NULL;
        }

        void unload()
        {
            if (m_hModule)
            {
                typedef void (*F)();
                F free_plugin = (F)GetProcAddress(m_hModule, XMAN_PLUGIN_FUNC_FREE_PLUGIN);
                free_plugin();
                xmanFreeLibrary(m_hModule);

                m_hModule = NULL;
            }
        }

        char *GetPluginPath()
        {
            return m_full_plugin_path;
        }

        char *GetPluginFolder()
        {
            return m_plugin_folder;
        }

        HMODULE GetPluginModuleHandle()
        {
            return m_hModule;
        }

        char *GetPluginName()
        {
            return m_plugin_name;
        }

        xmanObject *CreateObject()
        {
            xmanObject *obj = NULL;
            if (m_create_object_fun)
            {
                typedef xmanObject*(*C)();
                C c = (C)m_create_object_fun;
                obj = c();
            }

            return obj;
        }

        private:
        bool IsAlreadyLoaded(char *plugin_path)
        {
//            for (int i = 0; i < g_plugins_num; i++)
//            {
//                if (strcmp(g_plugins[i]->GetPluginPath(), plugin_path) == 0)
//                    return true;
//            }
            for (int i = 0; i < PLUGIN_STORE_NUM_VAR(PROJECT_NAME); i++)
            {
                if (strcmp(PLUGIN_STORE_VAR(PROJECT_NAME)[i]->GetPluginPath(), plugin_path) == 0)
                    return true;
            }
            return false;
        }
        HMODULE m_hModule;
        char m_full_plugin_path[MAX_PATH];
        char m_plugin_name[MAX_PATH];
        char m_plugin_folder[MAX_PATH];
        char m_plugin_version[MAX_PATH];
        void *m_create_object_fun;
    };
}

#endif //XMAN_LOADMODULEHELPER_H
