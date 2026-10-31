#pragma once
#include <string>
struct color_t {
    union {
        struct { float r, g, b, a; };
        float data[4];
    };
    inline color_t() noexcept : r(0), g(0), b(0), a(255) {}
    inline color_t(float r, float g, float b) noexcept : r(r), g(g), b(b), a(255) {}
    inline color_t(float r, float g, float b, float a) noexcept : r(r), g(g), b(b), a(a) {}
    [[maybe_unused]] inline static color_t Black(float a = 255) { return {0, 0, 0, a}; }
    [[maybe_unused]] inline static color_t Red(float a = 255) { return {255, 0, 0, a}; }
    [[maybe_unused]] inline static color_t Green(float a = 255) { return {0, 255, 0, a}; }
    [[maybe_unused]] inline static color_t Blue(float a = 255) { return {0, 0, 255, a}; }
    [[maybe_unused]] inline static color_t White(float a = 255) { return {255, 255, 255, a}; }
    [[maybe_unused]] inline static color_t Orange(float a = 255) { return {255, 153, 0, a}; }
    [[maybe_unused]] inline static color_t Yellow(float a = 255) { return {255, 255, 0, a}; }
    [[maybe_unused]] inline static color_t Cyan(float a = 255) { return {0, 255, 255, a}; }
    [[maybe_unused]] inline static color_t Magenta(float a = 255) { return {255, 0, 255, a}; }
    [[maybe_unused]] inline static color_t MonoBlack(float a = 1) { return {0, 0, 0, a}; }
    [[maybe_unused]] inline static color_t MonoRed(float a = 1) { return {1, 0, 0, a}; }
    [[maybe_unused]] inline static color_t MonoGreen(float a = 1) { return {0, 1, 0, a}; }
    [[maybe_unused]] inline static color_t MonoBlue(float a = 1) { return {0, 0, 1, a}; }
    [[maybe_unused]] inline static color_t MonoWhite(float a = 1) { return {1, 1, 1, a}; }
    [[maybe_unused]] inline static color_t MonoOrange(float a = 1) { return {1, 0.55, 0, a}; }
    [[maybe_unused]] inline static color_t MonoYellow(float a = 1) { return {1, 1, 0, a}; }
    [[maybe_unused]] inline static color_t MonoCyan(float a = 1) { return {0, 1, 1, a}; }
    [[maybe_unused]] inline static color_t MonoMagenta(float a = 1) { return {1, 0, 1, a}; }
    [[maybe_unused]] inline static color_t random(float a = 255) {
        float r = static_cast<float>(rand()) / static_cast<float>(255);
        float g = static_cast<float>(rand()) / static_cast<float>(255);
        float b = static_cast<float>(rand()) / static_cast<float>(255);
        return {r, g, b, a};
    }
    inline color_t ToMono() { return {r / 255, g / 255, b / 255, a / 255 }; }
};
inline bool operator ==(const color_t& lhs, const color_t& rhs) { return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a; }
inline bool operator !=(const color_t& lhs, const color_t& rhs) { return !(lhs == rhs); }
