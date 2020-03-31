//
// Created by Hari.Sheldon on 2020/3/31.
//

#ifndef ZQLPLAYER_EGLTHREAD_H
#define ZQLPLAYER_EGLTHREAD_H

#include "pthread.h"
#include "egl/egl.h"
#include "EGLHelper.h"

class EGLThread {

public:
    pthread_t eglThreadID = -1;
    ANativeWindow *nativeWindow = NULL;
    EGLHelper *eglHelper;
    bool isCreated = false;
    bool isChanged = false;
    bool isExit = false;
    bool isDrawStart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;
public:
    EGLThread();

    ~EGLThread();

    void onSurfaceCreated(EGLNativeWindowType win);

    void onSurfaceChanged(int width,int height);

    void onSurfaceDestroy();
};


#endif //ZQLPLAYER_EGLTHREAD_H
