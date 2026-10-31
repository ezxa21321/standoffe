#pragma once
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <cfloat>

struct quaternion_t;
struct vec3_t {
    union {
        struct { float x{}, y{}, z{}; };
        union {
            struct {
                // Y axis
                float pitch{};
                // Z axis
                float yaw{};
                // X axis
                float roll{};
            } UE4;
            struct {
                // Z axis
                float yaw{};
                // X axis
                float roll{};
                // Y axis
                float pitch{};
            } Unity;
        } Rot;
        float data[3];
    };
    
    inline vec3_t() noexcept : x(0.f), y(0.f), z(0.f) {};
    inline vec3_t(float x, float y, float z) noexcept : x(x), y(y), z(z) {};
    
    // Static methods
    inline static float Angle(vec3_t from, vec3_t to);
    inline static float Dot(vec3_t, vec3_t);
    [[maybe_unused]] inline static vec3_t ClampMagnitude(vec3_t, float);
    [[maybe_unused]] inline static float Component(vec3_t, vec3_t);
    inline static vec3_t Cross(vec3_t, vec3_t);
    [[maybe_unused]] inline static float Distance(vec3_t, vec3_t);
    [[maybe_unused]] inline static vec3_t FromSpherical(float, float, float);
    [[maybe_unused]] inline static vec3_t Lerp(vec3_t, vec3_t, float);
    inline static vec3_t LerpUnclamped(vec3_t, vec3_t, float);
    [[maybe_unused]] inline static vec3_t Max(vec3_t, vec3_t);
    [[maybe_unused]] inline static vec3_t Min(vec3_t, vec3_t);
    [[maybe_unused]] inline static vec3_t MoveTowards(vec3_t, vec3_t, float);
    inline static vec3_t Orthogonal(vec3_t);
    [[maybe_unused]] inline static vec3_t RotateTowards(vec3_t, vec3_t, float, float);
    [[maybe_unused]] inline static vec3_t Scale(vec3_t, vec3_t);
    [[maybe_unused]] inline static std::vector<vec3_t> MultiScale(vec3_t, float);
    [[maybe_unused]] inline static vec3_t Slerp(vec3_t, vec3_t, float);
    inline static vec3_t SlerpUnclamped(vec3_t, vec3_t, float);
    [[maybe_unused]] inline static void ToSpherical(vec3_t vector, float &, float &, float &);
    inline static float Magnitude(vec3_t);
    inline static float SqrMagnitude(vec3_t);
    inline static vec3_t Normalize(vec3_t);
    inline static vec3_t NormalizeEuler(vec3_t, bool is180 = true);
    inline static float NormalizeAngle(float f, bool is180 = true);
    [[maybe_unused]] inline static vec3_t FromString(std::string);
    
    // Instance methods
    inline vec3_t orthogonal() const { return Orthogonal(*this); }
    inline float magnitude() const { return Magnitude(*this); }
    inline float sqrMagnitude() const { return SqrMagnitude(*this); }
    inline vec3_t normalized() const { return Normalize(*this); }
    [[maybe_unused]] inline vec3_t normalizedEuler(bool is180 = true) const { return NormalizeEuler(*this, is180); }
    inline std::string str() const { return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z); }
    
    // Operators
    bool operator==(const vec3_t& v) const { return x == v.x && y == v.y && z == v.z; }
    bool operator!=(const vec3_t& v) const { return x != v.x || y != v.y || z != v.z; }
    vec3_t& operator+=(const vec3_t& inV) { x += inV.x; y += inV.y; z += inV.z; return *this; }
    vec3_t& operator-=(const vec3_t& inV) { x -= inV.x; y -= inV.y; z -= inV.z; return *this; }
    vec3_t& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    vec3_t& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
    vec3_t& operator/=(const vec3_t& inV) { x /= inV.x; y /= inV.y; z /= inV.z; return *this; }
    vec3_t operator-() const { return vec3_t(-x, -y, -z); }
    
    // Static constants
    static const vec3_t infinityVec;
    static const vec3_t zero;
    static const vec3_t one;
    static const vec3_t up;
    static const vec3_t down;
    static const vec3_t left;
    static const vec3_t right;
    static const vec3_t forward;
    static const vec3_t back;
};

// Static constants definitions
inline const vec3_t vec3_t::infinityVec(FLT_MAX, FLT_MAX, FLT_MAX);
inline const vec3_t vec3_t::zero(0.f, 0.f, 0.f);
inline const vec3_t vec3_t::one(1.f, 1.f, 1.f);
inline const vec3_t vec3_t::up(0.f, 1.f, 0.f);
inline const vec3_t vec3_t::down(0.f, -1.f, 0.f);
inline const vec3_t vec3_t::left(-1.f, 0.f, 0.f);
inline const vec3_t vec3_t::right(1.f, 0.f, 0.f);
inline const vec3_t vec3_t::forward(0.f, 0.f, 1.f);
inline const vec3_t vec3_t::back(0.f, 0.f, -1.f);

// Operator overloads
inline vec3_t operator+(const vec3_t& lhs, const vec3_t& rhs) { return vec3_t(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z); }
inline vec3_t operator-(const vec3_t& lhs, const vec3_t& rhs) { return vec3_t(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z); }
inline vec3_t operator*(const vec3_t& inV, const float s) { return vec3_t(inV.x * s, inV.y * s, inV.z * s); }
inline vec3_t operator*(const float s, const vec3_t& inV) { return vec3_t(inV.x * s, inV.y * s, inV.z * s); }
inline vec3_t operator*(const vec3_t& lhs, const vec3_t& rhs) { return vec3_t(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z); }
inline vec3_t operator/(const vec3_t& inV, const float s) { return vec3_t(inV.x / s, inV.y / s, inV.z / s); }
inline vec3_t operator/(const vec3_t& lhs, const vec3_t& rhs) { return vec3_t(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z); }

// Method implementations
inline float vec3_t::Angle(vec3_t from, vec3_t to) {
    float v = Dot(from, to) / (from.magnitude() * to.magnitude());
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

inline float vec3_t::Dot(vec3_t lhs, vec3_t rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline vec3_t vec3_t::ClampMagnitude(vec3_t vector, float maxLength) {
    float length = vector.magnitude();
    if (length > maxLength) vector *= maxLength / length;
    return vector;
}

// ... (остальные реализации методов остаются без изменений)

[[maybe_unused]] float vec3_t::Component(vec3_t a, vec3_t b) {
    return Dot(a, b) / b.magnitude();
}

vec3_t vec3_t::Cross(vec3_t lhs, vec3_t rhs) {
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return vec3_t(x, y, z);
}

[[maybe_unused]] float vec3_t::Distance(vec3_t a, vec3_t b) {
    return (a - b).magnitude();
}

[[maybe_unused]] vec3_t vec3_t::FromSpherical(float rad, float theta, float phi) {
    vec3_t v;
    v.x = rad * sin(theta) * cos(phi);
    v.y = rad * sin(theta) * sin(phi);
    v.z = rad * cos(theta);
    return v;
}

[[maybe_unused]] vec3_t vec3_t::Lerp(vec3_t a, vec3_t b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

vec3_t vec3_t::LerpUnclamped(vec3_t a, vec3_t b, float t) {
    return (b - a) * t + a;
}

[[maybe_unused]] vec3_t vec3_t::Max(vec3_t a, vec3_t b) {
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return vec3_t(x, y, z);
}

[[maybe_unused]] vec3_t vec3_t::Min(vec3_t a, vec3_t b) {
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    float z = a.z > b.z ? b.z : a.z;
    return vec3_t(x, y, z);
}

[[maybe_unused]] vec3_t vec3_t::MoveTowards(vec3_t current, vec3_t target, float maxDistanceDelta) {
    vec3_t d = target - current;
    float m = d.magnitude();
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

vec3_t vec3_t::Orthogonal(vec3_t v) {
    return v.z < v.x ? vec3_t(v.y, -v.x, 0) : vec3_t(0, -v.z, v.y);
}

[[maybe_unused]] vec3_t vec3_t::RotateTowards(vec3_t current, vec3_t target, float maxRadiansDelta, float maxMagnitudeDelta) {
    float magCur = current.magnitude();
    float magTar = target.magnitude();
    float newMag = magCur + maxMagnitudeDelta * ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));
    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0) return Normalize(target) * newMag;
    else if (totalAngle >= M_PI) return -target.normalized() * newMag;
    vec3_t axis = Cross(current, target);
    float magAxis = axis.magnitude();
    if (magAxis == 0) axis = Cross(current, current + vec3_t(3.95, 5.32, -4.24)).normalized();
    else axis /= magAxis;
    current = current.normalized();
    vec3_t newVector = current * cos(maxRadiansDelta) + Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

[[maybe_unused]] vec3_t vec3_t::Scale(vec3_t a, vec3_t b) {
    return vec3_t(a.x * b.x, a.y * b.y, a.z * b.z);
}

[[maybe_unused]] std::vector<vec3_t> vec3_t::MultiScale(vec3_t a, float b) {
     std::vector<vec3_t> ret;
     vec3_t multi = {};
     for (float i = 0; i < b; i++){
     multi = a + vec3_t(b / 200, 0, 0);
     multi = a + vec3_t(0, b / 200, 0);
     multi = a + vec3_t(0, 0, b / 200);
     multi = a + vec3_t(b / 200, b / 200, 0);
     multi = a + vec3_t(b / 200, b / 200, b / 200);
     multi = a + vec3_t(0, b / 200, b / 200);
     if(!(std::find(ret.begin(), ret.end(), multi) != ret.end())){
 
     ret.push_back(multi);
     }
    }
    return std::move(ret);
}

[[maybe_unused]] vec3_t vec3_t::Slerp(vec3_t a, vec3_t b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

vec3_t vec3_t::SlerpUnclamped(vec3_t a, vec3_t b, float t) {
    float magA = a.magnitude();
    float magB = b.magnitude();
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    vec3_t relativeVec = Normalize(b - a * dot);
    vec3_t newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

[[maybe_unused]] void vec3_t::ToSpherical(vec3_t vector, float &rad, float &theta, float &phi) {
    rad = vector.magnitude();
    float v = vector.z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.y, vector.x);
}

float vec3_t::Magnitude(vec3_t v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec3_t::SqrMagnitude(vec3_t v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

vec3_t vec3_t::Normalize(vec3_t v) {
    float mag = v.magnitude();
    if (mag == 0) return vec3_t::zero;
    return v / mag;
}

float vec3_t::NormalizeAngle(float f, bool is180) {
    while (f > (is180 ? 180 : 360)) f -= 360;
    while (f < (is180 ? -180 : 0.f)) f += 360;
    return f;
}

vec3_t vec3_t::NormalizeEuler(vec3_t vec, bool is180) {
    vec.x = NormalizeAngle(vec.x, is180);
    vec.y = NormalizeAngle(vec.y, is180);
    vec.z = NormalizeAngle(vec.z, is180);
    return vec;
}

[[maybe_unused]] vec3_t vec3_t::FromString(std::string str) {
    std::vector<std::string> commands;
    std::string buffer = "";
    for (int i = 0; i < str.size(); i++) {
        bool no = true;
        if (str[i] == 'f') no = false;
        if (str[i] != ',') buffer += str[i];
        else if (no) {
            commands.push_back(buffer);
            buffer = "";
        }
    }
    if (!buffer.empty()) commands.push_back(buffer);
    return vec3_t(std::atof(commands[0].c_str()), std::atof(commands[1].c_str()), std::atof(commands[2].c_str()));
}


