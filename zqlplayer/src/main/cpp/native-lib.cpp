#include <jni.h>
#include <string>
#include "opengl/OpenglController.h"


OpenglController *openglController = NULL;
extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject thiz,
                                                         jobject surface) {
    if (openglController == NULL) {
        openglController = new OpenglController();
    }
    openglController->onSurfaceCreated(env, surface);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceDestroy(JNIEnv *env, jobject thiz) {
    if (openglController != NULL) {
        openglController->onSurfaceDestroy();
        delete openglController;
        openglController = NULL;
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_surfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                          jint height) {
    if (openglController != NULL) {
        openglController->onSurfaceChanged(width, height);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_imgData(JNIEnv *env, jobject thiz, jint width,
                                                   jint height,
                                                   jint length, jbyteArray data_) {

    if(openglController == NULL){
        return;
    }
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    if(openglController != NULL){
        openglController->setImage(data,width,height,length);

    }
    env->ReleaseByteArrayElements(data_, data, 0);

}extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_changeOpenglProgram(JNIEnv *env, jobject thiz) {
    if(openglController != NULL){
        openglController->changeOpenglProgram();
    }
}