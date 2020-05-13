#include <jni.h>
#include <string>
#include <random>
#include "log/ZqlPlayerLog.h"
#include "egl/EGLHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "GLES2/gl2.h"
#include "egl/EGLThread.h"
#include "shaderutil/ShaderUtil.h"
#include "matrix/MatrixUtil.h"

ANativeWindow *nativeWindow = NULL;
EGLThread *eglThread = NULL;
EGLHelper *eglHelper;


const char *vertex = "attribute vec2 v_Position;\n"
                     "attribute vec2 f_Position;\n"
                     "varying vec2 ft_Position;\n"
                     "uniform mat4 u_Matrix;\n"
                     "void main() {\n"
                     "    ft_Position = f_Position;\n"
                     "    gl_Position = vec4(v_Position,1.0,1.0) * u_Matrix ;\n"
                     "}";
const char *fragment = "precision mediump float;\n"
                       "varying vec2 ft_Position;\n"
                       "uniform sampler2D sTexture;\n"
                       "void main() {\n"
                       "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
                       "}";

GLuint program = 0;
GLint vPosition;
GLint fPosition;
GLint sTexture;
GLuint textureId;
GLint u_matrix;
int w;
int h;
void *pixels = NULL;

float vertexs[] = {
        1, -1,
        1, 1,
        -1, -1,
        -1, 1
};

float fragments[] = {
        1, 1,
        1, 0,
        0, 1,
        0, 0
};

float matrix[16];
std::default_random_engine e;
std::uniform_real_distribution<float> u(0, 1);

void onSurfaceCreatedCallback(void *) {
    LOGD("eglthread call surface create")
    eglHelper = new EGLHelper();
    eglHelper->initEGL(eglThread->nativeWindow);
    program = createProgram(vertex, fragment);
    LOGD("opengl shader program is %d", program);
    vPosition = glGetAttribLocation(program, "v_Position"); //顶点坐标
    fPosition = glGetAttribLocation(program, "f_Position"); //纹理坐标
    sTexture = glGetUniformLocation(program, "sTexture"); //2D纹理
    u_matrix = glGetUniformLocation(program, "u_Matrix");
    initMatrix(matrix);
    //rotationZMatrix(90, matrix); //旋转
    //scaleMatrix(0.5, 0.7, 1, matrix); //缩放
    //transMatrix(0.3, 0, 0, matrix); // 平移
    //orthoM(-1, 1, -1, 1, matrix);
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void onSurfaceChangedCallback(void *, int width, int height) {
    LOGD("eglthread call surface changed, width = %d, height = %d",
         eglThread->surfaceWidth, eglThread->surfaceHeight)
    glViewport(0, 0, eglThread->surfaceWidth, eglThread->surfaceHeight);

    float screen_r = 1.0 * width / height;
    if (w != 0 && h != 0) {
        float picture_r = 1.0 * w / h;
        if (screen_r > picture_r) { //图片宽度缩放
            float r = width / (1.0 * height / h * w);
            orthoM(-r, r, -1, 1, matrix);
        } else { //图片高度缩放
            float r = height / (1.0 * width / w * h);
            orthoM(-1, 1, -r, r, matrix);
        }
    }
}

void onSurfaceDestroyCallback(void *) {
    LOGD("eglthread call surface destroy")
    eglHelper->destroyEgl();
}

void onDrawCallback(void *) {

    //绘制底色
    float read = u(e);
    float green = u(e);
    float blue = u(e);
    glClearColor(read, green, blue, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    if (program != 0) {
        glUseProgram(program);
        glUniformMatrix4fv(u_matrix, 1, GL_FALSE, matrix);


        glActiveTexture(GL_TEXTURE5);
        glUniform1i(sTexture, 5);

        glBindTexture(GL_TEXTURE_2D, textureId);

        glEnableVertexAttribArray(vPosition);
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);

        glEnableVertexAttribArray(fPosition);
        glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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
}extern "C"
JNIEXPORT void JNICALL
Java_com_zql_zqlplayer_opengl_NativeOpengl_imgData(JNIEnv *env, jobject thiz, jint width,
                                                   jint height,
                                                   jint length, jbyteArray data_) {

    jbyte *data = env->GetByteArrayElements(data_, NULL);

    w = width;
    h = height;
    pixels = malloc(length);
    memcpy(pixels, data, length);

    env->ReleaseByteArrayElements(data_, data, 0);

}