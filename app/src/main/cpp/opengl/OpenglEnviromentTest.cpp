//
// Created by Hari.Sheldon on 2020/5/13.
//

#include <random>
#include "OpenglEnviromentTest.h"
#include "../shaderutil/ShaderUtil.h"

void OpenglEnviromentTest::onCreate() {

    vertex = "attribute vec2 v_Position;\n"
             "attribute vec2 f_Position;\n"
             "varying vec2 ft_Position;\n"
             "uniform mat4 u_Matrix;\n"
             "void main() {\n"
             "    ft_Position = f_Position;\n"
             "    gl_Position = vec4(v_Position,1.0,1.0) * u_Matrix ;\n"
             "}";
    fragment = "precision mediump float;\n"
               "varying vec2 ft_Position;\n"
               "uniform sampler2D sTexture;\n"
               "void main() {\n"
               "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
               "}";

    LOGD("OpenglEnviromentTest call surface create")

    program = createProgram(vertex, fragment);
    LOGD("opengl shader program is %d", program);
    vPosition = glGetAttribLocation(program, "v_Position"); //顶点坐标
    fPosition = glGetAttribLocation(program, "f_Position"); //纹理坐标
    sTexture = glGetUniformLocation(program, "sTexture"); //2D纹理
    u_matrix = glGetUniformLocation(program, "u_Matrix");

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pic_w, pic_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenglEnviromentTest::onChanged(int width, int height) {
    BaseOpengl::onChanged(width, height);
    setMatrix(width, height);
}


std::default_random_engine e;
std::uniform_real_distribution<float> u(0, 1);

void OpenglEnviromentTest::draw() {

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
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexes);

        glEnableVertexAttribArray(fPosition);
        glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

OpenglEnviromentTest::OpenglEnviromentTest() {

}

OpenglEnviromentTest::~OpenglEnviromentTest() {

}

void OpenglEnviromentTest::setMatrix(int width, int height) {

    initMatrix(matrix);
    //rotationZMatrix(90, matrix); //旋转
    //scaleMatrix(0.5, 0.7, 1, matrix); //缩放
    //transMatrix(0.3, 0, 0, matrix); // 平移
    //orthoM(-1, 1, -1, 1, matrix);

    float screen_r = 1.0 * width / height;
    if (pic_w != 0 && pic_h != 0) {
        float picture_r = 1.0 * pic_w / pic_h;
        if (screen_r > picture_r) { //图片宽度缩放
            float r = width / (1.0 * height / pic_h * pic_w);
            orthoM(-r, r, -1, 1, matrix);
        } else { //图片高度缩放
            float r = height / (1.0 * width / pic_w * pic_h);
            orthoM(-1, 1, -r, r, matrix);
        }
    }
}

void OpenglEnviromentTest::setImage(void *data, int w, int h, int length) {
    this->pic_w = w;
    this->pic_h = h;
    this->pixels = data;

    if (surface_width > 0 && surface_height > 0) {
        setMatrix(surface_width, surface_height);
    }
}
