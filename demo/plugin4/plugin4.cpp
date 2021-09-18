//
// Created by CHM on 2021/9/18.
//

#include "plugin4.h"

#include "xman_plugin.h"

OUTAPI void init_plugin_XgoCzmhoeZUiFBwEKdZ1()
{
    strcpy(xman_plugin_version, "2.0.0.1");
    printf("hello!\n");
}

OUTAPI void free_plugin_XgoCzmhoeZUiFBwEKdZ1()
{
    printf("bye bye!\n");
}

XMAN_DEFINE_CLASS(Manager)


#include "xmanager.h"
#include "plugin2.h"
#include "plugin3.h"
void Manager::loadp() {
    char* plugins[] = {
//            "libplugin1.so",
            "plugin2.dll",
            "plugin3.dll",
            NULL
    };
    xman::loadPlugins(plugins, "plugin");

    for (int i = 0; i < xman::PLUGIN_STORE_NUM_VAR(PROJECT_NAME); i++)
    {
        xman::xmanObject * o = xman::PLUGIN_STORE_VAR(PROJECT_NAME)[i]->CreateObject();

        if (o)
        {
            Child * c = (Child*)o;

            c->show();
        }
    }
}
