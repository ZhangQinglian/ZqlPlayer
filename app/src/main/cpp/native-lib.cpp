#include <jni.h>
#include <string>
#include "log/ZqlPlayerLog.h"
#include "egl/EGLHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/EGLThread.h"

ANativeWindow *nativeWindow = NULL;
EGLThread *eglThread = NULL;
extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject thiz,
                                                         jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EGLThread();
    eglThread->onSurfaceCreated(nativeWindow);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceDestroy(JNIEnv *env, jobject thiz) {
    eglThread->onSurfaceDestroy();
}extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                          jint height) {
    eglThread->onSurfaceChanged(width, height);
}