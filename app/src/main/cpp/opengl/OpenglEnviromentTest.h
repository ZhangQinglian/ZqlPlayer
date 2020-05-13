//
// Created by Hari.Sheldon on 2020/5/13.
//

#ifndef ZQLPLAYER_OPENGLENVIROMENTTEST_H
#define ZQLPLAYER_OPENGLENVIROMENTTEST_H


#include "BaseOpengl.h"

class OpenglEnviromentTest : public BaseOpengl {

public:

    GLint vPosition;
    GLint fPosition;
    GLint sTexture;
    GLuint textureId;
    GLint u_matrix;

    int pic_w;
    int pic_h;
    void *pixels = NULL;

public:
    OpenglEnviromentTest();

    ~OpenglEnviromentTest();

    void onCreate() override;

    void onChanged(int width, int height) override;

    void draw() override;

    void setMatrix(int width,int height);

    void setImage(void *data,int w, int h,int length) override;
};


#endif //ZQLPLAYER_OPENGLENVIROMENTTEST_H
