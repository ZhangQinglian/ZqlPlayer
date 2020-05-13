//
// Created by Hari.Sheldon on 2020/5/12.
//

#ifndef ZQLPLAYER_MATRIXUTIL_H
#define ZQLPLAYER_MATRIXUTIL_H

#include <tgmath.h>

static void initMatrix(float *matrix) {
    for (int i = 0; i < 16; i++) {
        if (i % 5 == 0) {
            matrix[i] = 1;
        } else {
            matrix[i] = 0;
        }
    }
}

static void rotationZMatrix(double angle, float *matrix) {
    angle = angle * M_PI / 180;
    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);
}

static void rotationXMatrix(double angle, float *matrix) {
    angle = angle * M_PI / 180;
    matrix[5] = cos(angle);
    matrix[6] = -sin(angle);
    matrix[9] = sin(angle);
    matrix[10] = cos(angle);
}


static void rotationYMatrix(double angle, float *matrix) {
    angle = angle * M_PI / 180;
    matrix[0] = cos(angle);
    matrix[2] = sin(angle);
    matrix[8] = -sin(angle);
    matrix[10] = cos(angle);
}

static void scaleMatrix(float scaleX, float scaleY, float scaleZ, float *matrix) {
    matrix[0] *= scaleX;
    matrix[5] *= scaleY;
    matrix[10] *= scaleZ;
}

static void transMatrix(float moveX, float moveY, float moveZ, float *matrix) {
    matrix[3] += moveX;
    matrix[7] += moveY;
    matrix[11] += moveZ;
}

static void orthoM(float left, float right, float bottom, float top, float *matrix) {
    matrix[0] = 2 / (right - left);
    matrix[3] = (right + left) / (right - left) * -1;
    matrix[5] = 2 / (top - bottom);
    matrix[7] = (top + bottom) / (top - bottom) * -1;
    matrix[10] = 1;
    matrix[15] = 1;
}

#endif //ZQLPLAYER_MATRIXUTIL_H
