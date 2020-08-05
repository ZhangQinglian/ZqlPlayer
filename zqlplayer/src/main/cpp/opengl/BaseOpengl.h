//
// Created by Hari.Sheldon on 2020/5/13.
//

#ifndef ZQLPLAYER_BASEOPENGL_H
#define ZQLPLAYER_BASEOPENGL_H


#include <GLES2/gl2.h>
#include <cstring>
#include <random>
#include "../log/ZqlPlayerLog.h"
#include "../matrix/MatrixUtil.h"
#include "../egl/EGLHelper.h"
static std::default_random_engine e;
static std::uniform_real_distribution<float> u(0, 1);
class BaseOpengl {

public:
    int surface_width;
    int surface_height;

    char *vertex;
    char *fragment;

    float *vertexes;
    float *fragments;

    GLuint program;

    GLuint vShader;
    GLuint fShader;

    float matrix[16];

    typedef void(*OnEglSwapBuffer)(void *ctx);

public:
    BaseOpengl();

    ~BaseOpengl();

    virtual void onCreate();

    virtual void onChanged(int width, int height);

    virtual void draw();

    virtual void destroy();

    virtual void setImage(void *data,int w, int h,int length);

    virtual void destroyImage();
};


#endif //ZQLPLAYER_BASEOPENGL_H
