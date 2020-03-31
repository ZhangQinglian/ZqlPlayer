#include <jni.h>
#include <string>
#include <random>
#include "log/ZqlPlayerLog.h"
#include "egl/EGLHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/EGLThread.h"

ANativeWindow *nativeWindow = NULL;
EGLThread *eglThread = NULL;
EGLHelper *eglHelper;

std::default_random_engine e;
std::uniform_real_distribution<float> u(0, 1);

void onSurfaceCreatedCallback(void *) {
    LOGD("eglthread call surface create")
    eglHelper = new EGLHelper();
    eglHelper->initEGL(eglThread->nativeWindow);
}

void onSurfaceChangedCallback(void *, int width, int height) {
    LOGD("eglthread call surface changed, width = %d, height = %d",
         eglThread->surfaceWidth, eglThread->surfaceHeight)
    glViewport(0, 0, eglThread->surfaceWidth, eglThread->surfaceHeight);
}

void onSurfaceDestroyCallback(void *) {
    LOGD("eglthread call surface destroy")
    eglHelper->destroyEgl();
}

void onDrawCallback(void *) {
    LOGD("draw");

    float read = u(e);
    float green = u(e);
    float blue = u(e);
    glClearColor(read, green, blue, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    eglHelper->swapBuffers();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject thiz,
                                                         jobject surface) {

    nativeWindow = ANativeWindow_fromSurface(env, surface);
    eglThread = new EGLThread();
    eglThread->setOnCreateCallback(onSurfaceCreatedCallback, eglThread);
    eglThread->setOnChangedCallback(onSurfaceChangedCallback, eglThread);
    eglThread->setOnDestroyCallback(onSurfaceDestroyCallback, eglThread);
    eglThread->setOnDrawCallback(onDrawCallback, eglThread);
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