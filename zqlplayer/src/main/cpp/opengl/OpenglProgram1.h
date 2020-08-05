//
// Created by Hari.Sheldon on 2020/5/14.
//

#ifndef ZQLPLAYER_OPENGLPROGRAM1_H
#define ZQLPLAYER_OPENGLPROGRAM1_H


#include "BaseOpengl.h"

class OpenglProgram1 : public BaseOpengl {
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
    OpenglProgram1();

    ~OpenglProgram1();

    void onCreate() override;

    void onChanged(int width, int height) override;

    void draw() override;

    void setMatrix(int width, int height);

    void setImage(void *data, int w, int h, int length) override;

    void destroy() override;

    void destroyImage() override;
};

#endif //ZQLPLAYER_OPENGLPROGRAM1_H
