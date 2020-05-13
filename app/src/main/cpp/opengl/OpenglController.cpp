//
// Created by Hari.Sheldon on 2020/5/13.
//

#include "OpenglController.h"

OpenglController::OpenglController() {

}

OpenglController::~OpenglController() {

}

void onSurfaceCreatedCallback(void *ctx) {
    LOGD("Opengl Controller onSurfaceCreatedCallback");
    OpenglController *openglController = static_cast<OpenglController *>(ctx);
    if (openglController != NULL) {
        if (openglController->baseOpengl != NULL) {
            openglController->baseOpengl->onCreate();
        }
    }
}

void onSurfaceChangedCallback(void *ctx, int width, int height) {
    LOGD("Opengl Controller onSurfaceChangedCallback");
    OpenglController *openglController = static_cast<OpenglController *>(ctx);
    if (openglController != NULL) {
        if (openglController->baseOpengl != NULL) {
            openglController->baseOpengl->onChanged(width, height);
        }
    }
}

void onSurfaceDestroyCallback(void *ctx) {
    LOGD("Opengl Controller onSurfaceDestroyCallback");
    OpenglController *openglController = static_cast<OpenglController *>(ctx);
    if (openglController != NULL) {
        if (openglController->baseOpengl != NULL) {
            openglController->baseOpengl->destroy();
        }
    }
}

void onDrawCallback(void *ctx) {
    OpenglController *openglController = static_cast<OpenglController *>(ctx);
    if (openglController != NULL) {
        if (openglController->baseOpengl != NULL) {
            openglController->baseOpengl->draw();
        }
    }
}

void OpenglController::onSurfaceCreated(JNIEnv *env, jobject surface) {
    aNativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EGLThread();
    eglThread->setOnCreateCallback(onSurfaceCreatedCallback, this);
    eglThread->setOnChangedCallback(onSurfaceChangedCallback, this);
    eglThread->setOnDestroyCallback(onSurfaceDestroyCallback, this);
    eglThread->setOnDrawCallback(onDrawCallback, this);

    baseOpengl = new OpenglEnviromentTest();

    eglThread->onSurfaceCreated(aNativeWindow);
}

void OpenglController::onSurfaceChanged(int width, int height) {
    LOGD("eglthread call surface changed, width = %d, height = %d",
         width, height)

    if (eglThread != NULL) {
        if (baseOpengl != NULL) {
            baseOpengl->surface_height = height;
            baseOpengl->surface_width = width;
        }
        eglThread->onSurfaceChanged(width, height);
    }
}

void OpenglController::onSurfaceDestroy() {
    LOGD("eglthread call surface destroy")

    if (eglThread != NULL) {
        eglThread->onSurfaceDestroy();
    }

    if (baseOpengl != NULL) {
        baseOpengl->destroy();
        delete baseOpengl;
        baseOpengl = NULL;
    }

    if (aNativeWindow != NULL) {
        ANativeWindow_release(aNativeWindow);
        aNativeWindow = NULL;
    }
}

void OpenglController::setImage(void *data, int w, int h, int length) {
    pic_w = w;
    pic_h = h;
    pixels = malloc(length);
    memcpy(pixels, data, length);
    if (baseOpengl != NULL) {
        baseOpengl->setImage(pixels, w, h, length);
    }
    if (eglThread != NULL) {
        eglThread->notifyRender();
    }
}
