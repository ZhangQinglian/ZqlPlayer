//
// Created by Hari.Sheldon on 2020/3/31.
//

#include <unistd.h>
#include <GLES2/gl2.h>
#include "EGLThread.h"
#include "../log/ZqlPlayerLog.h"

EGLThread::EGLThread() {
    pthread_mutex_init(&pthreadMutex, NULL);
    pthread_cond_init(&pthreadCond, NULL);
}

EGLThread::~EGLThread() {
    pthread_mutex_destroy(&pthreadMutex);
    pthread_cond_destroy(&pthreadCond);
}

void *eglThreadRunnable(void *context) {
    EGLThread *eglThread = static_cast<EGLThread *>(context);
    if (eglThread != NULL) {
        EGLHelper *eglHelper = new EGLHelper();
        eglHelper->initEGL(eglThread->nativeWindow);
        eglThread->isExit = false;
        while (true) {
            if (eglThread->isCreated) {
                LOGD("egl thread : isCreated");
                eglThread->onCreatedCallback(eglThread->onCreatedCallbackCtx);
                eglThread->isCreated = false;
            }
            if (eglThread->isChanged) {
                LOGD("egl thread : isChanged");
                eglThread->onChangedCallback(eglThread->onChangeCallbackCtx,
                                             eglThread->surfaceWidth, eglThread->surfaceHeight);
                eglThread->isChanged = false;
                eglThread->isDrawStart = true;
            }
            if (eglThread->isFilterChanged) {
                eglThread->isFilterChanged = false;
                eglThread->onChangeFilterCallback(eglThread->surfaceWidth, eglThread->surfaceHeight,
                                                  eglThread->onChangeFilterCallbackCtx);
            }

            if (eglThread->isDrawStart) {
                LOGD("egl thread : isDrawStart");
                eglThread->onDrawCallback(eglThread->onDrawCallbackCtx);
                eglHelper->swapBuffers();
            }
            if (eglThread->isExit) {
                LOGD("egl thread : isExit");
                eglHelper->destroyEgl();
                delete eglHelper;
                eglHelper = NULL;
                break;
            }

            if (eglThread->renderType == OPENGL_RENDER_AUTO) {
                LOGD("egl thread : sleep");
                //60 fps
                usleep(1000000 / 5);
            } else {
                pthread_mutex_lock(&eglThread->pthreadMutex);
                LOGD("egl thread : wait");

                pthread_cond_wait(&eglThread->pthreadCond, &eglThread->pthreadMutex);

                pthread_mutex_unlock(&eglThread->pthreadMutex);
            }

        }
    }
    return 0;
}

void EGLThread::onSurfaceCreated(EGLNativeWindowType win) {
    if (eglThreadID == -1) {
        isCreated = true;
        nativeWindow = win;
        pthread_create(&eglThreadID, NULL, eglThreadRunnable, this);
    }

}

void EGLThread::onSurfaceChanged(int width, int height) {
    isChanged = true;
    surfaceWidth = width;
    surfaceHeight = height;
    notifyRender();
}

void EGLThread::onSurfaceDestroy() {
    isExit = true;
    notifyRender();
    pthread_join(eglThreadID, NULL);
    nativeWindow = NULL;
    eglThreadID = -1;
    onDestroyCallback(onDestroyCallbackCtx);
}

void EGLThread::setOnCreateCallback(EGLThread::OnCreatedCallback onCreateCallback, void *ctx) {
    this->onCreatedCallback = onCreateCallback;
    this->onCreatedCallbackCtx = ctx;
}

void EGLThread::setOnChangedCallback(EGLThread::OnChangedCallback onChangedCallback, void *ctx) {
    this->onChangedCallback = onChangedCallback;
    this->onChangeCallbackCtx = ctx;
}

void EGLThread::setOnDestroyCallback(EGLThread::OnDestroyCallback onDestroyCallback, void *ctx) {
    this->onDestroyCallback = onDestroyCallback;
    this->onDestroyCallbackCtx = ctx;
}

void EGLThread::setOnDrawCallback(EGLThread::OnDrawCallback onDrawCallback, void *ctx) {
    this->onDrawCallback = onDrawCallback;
    this->onDrawCallbackCtx = ctx;
}

void EGLThread::setRenderType(int renderType) {
    this->renderType = renderType;
}

void EGLThread::notifyRender() {
    pthread_mutex_lock(&pthreadMutex);
    pthread_cond_signal(&pthreadCond);
    pthread_mutex_unlock(&pthreadMutex);
}

void EGLThread::setOnChangeFilterCallback(EGLThread::OnChangeFilterCallback callback, void *ctx) {
    this->onChangeFilterCallback = callback;
    this->onChangeFilterCallbackCtx = ctx;
}

void EGLThread::onChangeFilter() {
    isFilterChanged = true;
    notifyRender();
}

