#include <stdio.h>

#define PROJECT_NAME "main"

#include "xmanager.h"

//#include "xman_plugin.h"
//
//#include "xman_obj_helper.h"

#include "plugin2.h"
#include "plugin3.h"
#include "plugin4.h"

int main(int argc, char* argv[])
{
    printf("testing\n");
//    char* plugins[] = {
////            "libplugin1.so",
//            "libplugin2.so",
//            "libplugin3.so",
//            NULL
//    };
//    xman::AutoLoadPlugins autoload(plugins, "plugin");
////    char* plugins1[] = {
////            "x3manager.pln", "plsimple.pln", NULL
////    };
////    xman::loadPlugins(plugins1, "plugins");
////
////    xman::unloadPlugin("x3manager.pln", "plugins");
//
//    for (int i = 0; i < xman::g_plugins_num; i++)
//    {
//        xman::xmanObject * o = xman::g_plugins[i]->CreateObject();
//
//        if (o)
//        {
//            Child * c = (Child*)o;
//
//            c->show();
//        }
//    }

    char* plugins[] = {
            "plugin4.dll",
            NULL
    };
    xman::AutoLoadPlugins autoload(plugins, "plugin");
    xman::xmanObject * o = xman::PLUGIN_STORE_VAR(PROJECT_NAME)[0]->CreateObject();

//    xman::LoadModuleHelper *l = new xman::LoadModuleHelper();
//    l->load(plugins[0], NULL, "plugin");
//
//    xman::xmanObject * o = l->CreateObject();

    if (o)
    {
        Manager * c = (Manager*)o;

        c->loadp();
    }
    return 0;
}