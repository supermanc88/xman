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
    class LoadModuleHelper
    {
        public:
        LoadModuleHelper() : m_hModule(NULL)
        {

        }

        bool load(char *plugin_name, HMODULE base_module = NULL, char *folder = "")
        {
            unload();

            // 判断是否是绝对路径

            // 如果不是绝对路径，就补全

            m_hModule = xmanLoadLibrary(plugin_name);

            return m_hModule != NULL;
        }

        void unload()
        {
            if (m_hModule)
            {
                xmanFreeLibrary(m_hModule);
            }
        }

        private:
        HMODULE m_hModule;
    };
}

#endif //XMAN_LOADMODULEHELPER_H
