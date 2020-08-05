//
// Created by Hari.Sheldon on 2020/5/11.
//

#ifndef ZQLPLAYER_SHADERUTIL_H
#define ZQLPLAYER_SHADERUTIL_H

#include <GLES2/gl2.h>

static GLuint loadShaders(GLuint shaderType, const char *code) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);
    return shader;
}

static GLuint
createProgram(const char *vertex, const char *fragment, GLuint *v_shader, GLuint *f_shader) {
    GLuint vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);
    GLuint fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    *v_shader = vertexShader;
    *f_shader = fragmentShader;
    return program;
}

#endif //ZQLPLAYER_SHADERUTIL_H
