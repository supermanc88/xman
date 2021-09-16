//
// Created by CHM on 2021/9/16.
//

#ifndef XMAN_PLUGIN2_H
#define XMAN_PLUGIN2_H

#include "xman_obj_helper.h"

class Child : public xman::xmanObject{
    public:
    void show() {
        printf("Child\n");
    }
};

#endif //XMAN_PLUGIN2_H
