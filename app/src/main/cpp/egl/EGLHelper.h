//
// Created by zqlxt on 2020/3/29.
//

#ifndef ZQLPLAYER_EGLHELPER_H
#define ZQLPLAYER_EGLHELPER_H

#include "EGL/egl.h"

class EGLHelper {

public:
    EGLDisplay mEglDisplay;
    EGLSurface mEglSurface;
    EGLConfig mEglConfig;
    EGLContext mEglContext;
public:
    EGLHelper();

    ~EGLHelper();

    int initEGL(EGLNativeWindowType win);

    int swapBuffers();

    void destoryEgl();
};


#endif //ZQLPLAYER_EGLHELPER_H
