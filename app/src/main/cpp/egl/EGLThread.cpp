//
// Created by Hari.Sheldon on 2020/3/31.
//

#include <unistd.h>
#include <GLES2/gl2.h>
#include "EGLThread.h"
#include "EGLHelper.h"
#include "../log/ZqlPlayerLog.h"

EGLThread::EGLThread() {

}

EGLThread::~EGLThread() {

}

void *eglThreadRunnable(void *context) {
    EGLThread *eglThread = static_cast<EGLThread *>(context);
    if (eglThread != NULL) {
        eglThread->eglHelper = new EGLHelper();
        eglThread->eglHelper->initEGL(eglThread->nativeWindow);

        eglThread->isExit = false;
        while (true) {
            if (eglThread->isExit) {
                eglThread->eglHelper->destroyEgl();
                break;
            }
            if (eglThread->isCreated) {
                LOGD("eglthread call surface create")
                eglThread->isCreated = false;
            }
            if (eglThread->isChanged) {
                LOGD("eglthread call surface changed, width = %d, height = %d",
                     eglThread->surfaceWidth, eglThread->surfaceHeight)
                glViewport(0, 0, eglThread->surfaceWidth, eglThread->surfaceHeight);
                eglThread->isChanged = false;
                eglThread->isDrawStart = true;
            }

            if (eglThread->isDrawStart) {
                LOGD("draw");
                glClearColor(0.0F, 1.0F, 0.0F, 1.0F);
                glClear(GL_COLOR_BUFFER_BIT);
                eglThread->eglHelper->swapBuffers();
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

