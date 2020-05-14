//
// Created by Hari.Sheldon on 2020/3/31.
//

#ifndef ZQLPLAYER_EGLTHREAD_H
#define ZQLPLAYER_EGLTHREAD_H

#include "pthread.h"
#include "egl/egl.h"
#include "EGLHelper.h"

#define OPENGL_RENDER_AUTO  1
#define OPENGL_RENDER_MANUAL 2

class EGLThread {

public:
    pthread_t eglThreadID = -1;
    ANativeWindow *nativeWindow = NULL;
    bool isCreated = false;
    bool isChanged = false;
    bool isExit = false;
    bool isDrawStart = false;
    bool isFilterChanged = false;

    int surfaceWidth = 0;
    int surfaceHeight = 0;

    typedef void(*OnCreatedCallback)(void *onCreateCallbackCtx);

    typedef void(*OnChangedCallback)(void *onChangedCallbackCtx, int width, int height);

    typedef void(*OnDestroyCallback)(void *onDestroyCallbackCtx);

    typedef void(*OnDrawCallback)(void *onDrawCallbackCtx);

    typedef void(*OnChangeFilterCallback)(int width, int height, void *);

    OnCreatedCallback onCreatedCallback;
    void *onCreatedCallbackCtx;
    OnChangedCallback onChangedCallback;
    void *onChangeCallbackCtx;
    OnDestroyCallback onDestroyCallback;
    void *onDestroyCallbackCtx;
    OnDrawCallback onDrawCallback;
    void *onDrawCallbackCtx;
    OnChangeFilterCallback onChangeFilterCallback;
    void *onChangeFilterCallbackCtx;


    int renderType = OPENGL_RENDER_AUTO;

    pthread_mutex_t pthreadMutex;
    pthread_cond_t pthreadCond;
public:
    EGLThread();

    ~EGLThread();

    void onSurfaceCreated(EGLNativeWindowType win);

    void onSurfaceChanged(int width, int height);

    void onChangeFilter();

    void onSurfaceDestroy();

    void setOnCreateCallback(OnCreatedCallback onCreateCallback, void *ctx);

    void setOnChangedCallback(OnChangedCallback onChangedCallback, void *ctx);

    void setOnDestroyCallback(OnDestroyCallback onDestroyCallback, void *ctx);

    void setOnDrawCallback(OnDrawCallback onDrawCallback, void *ctx);

    void setOnChangeFilterCallback(OnChangeFilterCallback, void *);

    void setRenderType(int renderType);

    void notifyRender();
};


#endif //ZQLPLAYER_EGLTHREAD_H
