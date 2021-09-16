#include <stdio.h>


#include "xmanager.h"

#include "xman_plugin.h"

#include "xman_obj_helper.h"

int main(int argc, char* argv[])
{
    printf("testing\n");
    char* plugins[] = {
            "x3manager.pln", "plsimple.pln", NULL
    };
    xman::AutoLoadPlugins autoload(plugins, "plugins");
    char* plugins1[] = {
            "x3manager.pln", "plsimple.pln", NULL
    };
    xman::loadPlugins(plugins1, "plugins");

    xman::unloadPlugin("x3manager.pln", "plugins");

    return 0;
}