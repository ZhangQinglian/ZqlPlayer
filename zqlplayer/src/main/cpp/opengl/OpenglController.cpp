//
// Created by Hari.Sheldon on 2020/5/13.
//

#include "OpenglController.h"
#include "OpenglProgram1.h"

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

void onFilterChangeCallback(int w, int h, void *ctx) {
    LOGD("Opengl Controller onFilterChangeCallback");
    OpenglController *openglController = static_cast<OpenglController *>(ctx);
    if (openglController != NULL) {
        if (openglController->baseOpengl != NULL) {
            openglController->baseOpengl->destroy();
            openglController->baseOpengl->destroyImage();
            delete openglController->baseOpengl;
            openglController->baseOpengl = NULL;
        }
        openglController->baseOpengl = new OpenglProgram1();
        openglController->baseOpengl->onCreate();
        openglController->baseOpengl->onChanged(w, h);
        openglController->baseOpengl->setImage(openglController->pixels, openglController->pic_w,
                                               openglController->pic_h, -1);
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
    eglThread->setRenderType(OPENGL_RENDER_MANUAL);
    eglThread->setOnCreateCallback(onSurfaceCreatedCallback, this);
    eglThread->setOnChangedCallback(onSurfaceChangedCallback, this);
    eglThread->setOnChangeFilterCallback(onFilterChangeCallback, this);
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
        baseOpengl->destroyImage();
        delete baseOpengl;
        baseOpengl = NULL;
    }

    if (aNativeWindow != NULL) {
        ANativeWindow_release(aNativeWindow);
        aNativeWindow = NULL;
    }

    if (pixels != NULL) {
        free(pixels);
    }
}

void OpenglController::setImage(void *data, int w, int h, int length) {
    pic_w = w;
    pic_h = h;
    pixels = malloc(length);
    memcpy(pixels, data, length);
    if (baseOpengl != NULL) {
        baseOpengl->setImage(pixels, w, h, length);
        LOGD("set image")
    }
    if (eglThread != NULL) {
        eglThread->notifyRender();
    }
}

void OpenglController::changeOpenglProgram() {
    if (eglThread != NULL) {
        eglThread->onChangeFilter();
    }
}
