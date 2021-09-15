#include <stdio.h>


#include "xmanager.h"

int main(int argc, char* argv[])
{
    printf("testing\n");
    char* plugins[] = {
            "x3manager.pln", "plsimple.pln", NULL
    };
    xman::AutoLoadPlugins autoload(plugins, "plugins");

    return 0;
}