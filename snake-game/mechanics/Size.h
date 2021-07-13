#pragma once

struct Size {
    int width;
    int height;

    Size(int w, int h) {
        this->width = w;
        this->height = h;
    }

    Size() : Size(0, 0) {};

    bool operator==(const Size& other) const {
        return this->width == other.width && this->height == other.height;
    }

    bool operator!=(const Size& other) const {
        return !(*this == other);
    }
};