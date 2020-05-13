//
// Created by Hari.Sheldon on 2020/5/13.
//

#include "BaseOpengl.h"

BaseOpengl::BaseOpengl() {
    vertexes = new float[8];
    fragments = new float[8];
    float v[] = {
            1, -1,
            1, 1,
            -1, -1,
            -1, 1
    };

    memcpy(vertexes, v, sizeof(v));

    float f[] = {
            1, 1,
            1, 0,
            0, 1,
            0, 0
    };

    memcpy(fragments, f, sizeof(f));
}

BaseOpengl::~BaseOpengl() {
    delete[]vertexes;
    delete[]fragments;
}

void BaseOpengl::onCreate() {}

void BaseOpengl::onChanged(int width, int height) {
    surface_width = width;
    surface_height = height;
    glViewport(0, 0, surface_width, surface_height);
}

void BaseOpengl::draw() {}

void BaseOpengl::destroy() {
}

void BaseOpengl::setImage(void *data,int w, int h,int length) {}