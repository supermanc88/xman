//
// Created by CHM on 2021/9/16.
//

#include "xman_plugin.h"

#include "plugin3.h"
#include <stdio.h>

OUTAPI void init_plugin_XgoCzmhoeZUiFBwEKdZ1()
{
    strcpy(xman_plugin_version, "2.0.0.1");
    printf("hello!\n");
}

OUTAPI void free_plugin_XgoCzmhoeZUiFBwEKdZ1()
{
    printf("bye bye!\n");
}

XMAN_DEFINE_CLASS(ChildChild)
