#pragma once
struct rect_t {
    union {
        struct { float x, y, w, h; };
        float data[4];
    };
    rect_t() noexcept : x(0), y(0), w(0), h(0) {}
    rect_t(float x, float y, float w, float h) noexcept : x(x), y(y), w(w), h(h) {}
};
