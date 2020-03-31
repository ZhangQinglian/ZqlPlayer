//
// Created by Hari.Sheldon on 2020/3/31.
//

#include <unistd.h>
#include <GLES2/gl2.h>
#include "EGLThread.h"
#include "../log/ZqlPlayerLog.h"

EGLThread::EGLThread() {

}

EGLThread::~EGLThread() {

}

void *eglThreadRunnable(void *context) {
    EGLThread *eglThread = static_cast<EGLThread *>(context);
    if (eglThread != NULL) {
        eglThread->isExit = false;
        while (true) {
            if (eglThread->isCreated) {
                eglThread->onCreatedCallback(eglThread->onCreatedCallbackCtx);
                eglThread->isCreated = false;
            }
            if (eglThread->isChanged) {

                eglThread->onChangedCallback(eglThread->onChangeCallbackCtx,
                                             eglThread->surfaceWidth, eglThread->surfaceHeight);
                eglThread->isChanged = false;
                eglThread->isDrawStart = true;
            }

            if (eglThread->isDrawStart) {
                eglThread->onDrawCallback(eglThread->onDrawCallbackCtx);
            }
            if (eglThread->isExit) {
                eglThread->onDestroyCallback(eglThread->onDestroyCallbackCtx);
                break;
            }
            //60 fps
            usleep(1000000 / 60);
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
}

void EGLThread::onSurfaceDestroy() {
    isExit = true;
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

