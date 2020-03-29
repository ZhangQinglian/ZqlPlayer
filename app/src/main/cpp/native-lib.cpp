#include <jni.h>
#include <string>
#include "log/ZqlPlayerLog.h"
#include "egl/EGLHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"

EGLHelper *eglHelper = NULL;
ANativeWindow *nativeWindow = NULL;
extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject thiz,
                                                         jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglHelper = new EGLHelper();
    eglHelper->initEGL(nativeWindow);

    //opengl
    glViewport(0, 0, 720, 1280);
    glClearColor(0.0F, 1.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    eglHelper->swapBuffers();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceDestory(JNIEnv *env, jobject thiz) {
    eglHelper->destoryEgl();
}