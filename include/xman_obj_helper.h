//
// Created by CHM on 2021/9/16.
//

#ifndef XMAN_XMAN_OBJ_HELPER_H
#define XMAN_XMAN_OBJ_HELPER_H

// 如果想在插件中导出一个对象的话，需要加载此文件

#ifdef __GNUC__
#define OUTAPI      extern "C" __attribute__((visibility("default")))
#if defined(__APPLE__)
#define LOCALAPI
#else
#define LOCALAPI    __attribute__((visibility("hidden")))
#endif
#else
#define OUTAPI      extern "C" __declspec(dllexport)
#define LOCALAPI
#endif // __GNUC__

namespace xman {
    class xmanObject {
    public:
        xmanObject() {};

        ~xmanObject() {};
    };

}

#define XMAN_DEFINE_CLASS(_CLASS) \
OUTAPI xman::xmanObject *xman_create_object_XgoCzmhoeZUiFBwEKdZ1()\
{                              \
    _CLASS * c = new _CLASS();    \
    return (xman::xmanObject *)c;\
}
#endif //XMAN_XMAN_OBJ_HELPER_H