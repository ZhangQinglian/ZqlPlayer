//
// Created by Hari.Sheldon on 2020/5/13.
//

#ifndef ZQLPLAYER_OPENGLCONTROLLER_H
#define ZQLPLAYER_OPENGLCONTROLLER_H

#include "../egl/EGLThread.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "BaseOpengl.h"
#include "OpenglEnviromentTest.h"

class OpenglController {
public:
    EGLThread *eglThread = NULL;
    ANativeWindow *aNativeWindow = NULL;
    BaseOpengl *baseOpengl = NULL;

    int pic_w;
    int pic_h;
    void *pixels = NULL;
public:
    OpenglController();

    ~OpenglController();

    void onSurfaceCreated(JNIEnv *env, jobject surface);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroy();

    void setImage(void *data,int w,int h,int length);
};


#endif //ZQLPLAYER_OPENGLCONTROLLER_H
