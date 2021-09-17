#include <stdio.h>


#include "xmanager.h"

//#include "xman_plugin.h"
//
//#include "xman_obj_helper.h"

//#include "../demo/plugin3/plugin3.h"
#include "../demo/plugin2/plugin2.h"

int main(int argc, char* argv[])
{
    printf("testing\n");
    char* plugins[] = {
//            "libplugin1.so",
//            "libplugin2.so",
            "libplugin3.so",
            NULL
    };
    xman::AutoLoadPlugins autoload(plugins, "plugin");
//    char* plugins1[] = {
//            "x3manager.pln", "plsimple.pln", NULL
//    };
//    xman::loadPlugins(plugins1, "plugins");
//
//    xman::unloadPlugin("x3manager.pln", "plugins");

    for (int i = 0; i < xman::g_plugins_num; i++)
    {
        xman::xmanObject * o = xman::g_plugins[i]->CreateObject();

        if (o)
        {
            Child * c = (Child*)o;

            c->show();
        }
    }

    return 0;
}