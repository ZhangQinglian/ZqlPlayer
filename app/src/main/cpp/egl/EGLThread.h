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
    bool isCreated = false;
    bool isChanged = false;
    bool isExit = false;
    bool isDrawStart = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;

    typedef void(*OnCreatedCallback)(void *onCreateCallbackCtx);

    typedef void(*OnChangedCallback)(void *onChangedCallbackCtx, int width, int height);

    typedef void(*OnDestroyCallback)(void *onDestroyCallbackCtx);

    typedef void(*OnDrawCallback)(void *onDrawCallbackCtx);

    OnCreatedCallback onCreatedCallback;
    void *onCreatedCallbackCtx;
    OnChangedCallback onChangedCallback;
    void *onChangeCallbackCtx;
    OnDestroyCallback onDestroyCallback;
    void *onDestroyCallbackCtx;
    OnDrawCallback onDrawCallback;
    void *onDrawCallbackCtx;

public:
    EGLThread();

    ~EGLThread();

    void onSurfaceCreated(EGLNativeWindowType win);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    void setOnCreateCallback(OnCreatedCallback onCreateCallback, void *ctx);

    void setOnChangedCallback(OnChangedCallback onChangedCallback, void *ctx);

    void setOnDestroyCallback(OnDestroyCallback onDestroyCallback, void *ctx);

    void setOnDrawCallback(OnDrawCallback onDrawCallback,void *ctx);
};


#endif //ZQLPLAYER_EGLTHREAD_H
