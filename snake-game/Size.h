#pragma once

struct Size {
    int width;
    int height;

    Size(int w, int h) {
        this->width = w;
        this->height = h;
    }

    Size() : Size(0, 0) {};
};
