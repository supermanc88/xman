//
// Created by CHM on 2021/9/16.
//

#ifndef XMAN_PLUGIN3_H
#define XMAN_PLUGIN3_H
#include "xman_obj_helper.h"

class Child : public xman::xmanObject{
public:
    virtual void show() {
        printf("Child\n");
    }
};

class ChildChild : public Child {
    public:
    virtual void show() {
        printf("Child Child\n");
    }
};
#endif //XMAN_PLUGIN3_H
