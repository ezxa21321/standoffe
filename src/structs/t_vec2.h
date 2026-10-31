#pragma once
struct vec2_t {
    union {
        struct { float x, y; };
        float data[2];
    };
    inline vec2_t() noexcept : x(0), y(0) {};
    inline vec2_t(float x, float y) noexcept : x(x), y(y) {};
    [[maybe_unused]] inline static vec2_t Down() { return vec2_t(0, -1); }
    [[maybe_unused]] inline static vec2_t Left() { return vec2_t(-1, 0); }
    [[maybe_unused]] inline static vec2_t One() { return vec2_t(1, 1); }
    [[maybe_unused]] inline static vec2_t Right() { return vec2_t(1, 0); }
    [[maybe_unused]] inline static vec2_t Up() { return vec2_t(0, 1); }
    inline static vec2_t Zero() { return vec2_t(0, 0); }
    inline static float Angle(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t ClampMagnitude(vec2_t, float);
    [[maybe_unused]] inline static float Component(vec2_t, vec2_t);
    [[maybe_unused]] inline static float Distance(vec2_t, vec2_t);
    inline static float Dot(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t FromPolar(float, float);
    [[maybe_unused]] inline static vec2_t Lerp(vec2_t, vec2_t, float) ;
    inline static vec2_t LerpUnclamped(vec2_t, vec2_t, float);
    inline static float Magnitude(vec2_t);
    [[maybe_unused]] inline static vec2_t Max(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t Min(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t MoveTowards(vec2_t, vec2_t, float);
    inline static vec2_t Normalize(vec2_t);
    [[maybe_unused]] inline static void OrthoNormalize(vec2_t &, vec2_t &);
    inline static vec2_t Project(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t Reflect(vec2_t, vec2_t);
    inline static vec2_t Reject(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t RotateTowards(vec2_t, vec2_t, float, float);
    [[maybe_unused]] inline static vec2_t Scale(vec2_t, vec2_t);
    [[maybe_unused]] inline static vec2_t Slerp(vec2_t, vec2_t, float);
    inline static vec2_t SlerpUnclamped(vec2_t, vec2_t, float);
    inline static float SqrMagnitude(vec2_t);
    [[maybe_unused]] inline static void ToPolar(vec2_t, float &, float &);
    inline float magnitude() { return Magnitude(*this); }
    inline float sqrMagnitude() { return SqrMagnitude(*this); }
    inline vec2_t normalized() { return Normalize(*this); }
    inline vec2_t& operator+=(float rhs) { x += rhs; y += rhs; return *this; }
    inline vec2_t& operator-=(float rhs) { x -= rhs; y -= rhs; return *this; }
    inline vec2_t& operator*=(float rhs) { x *= rhs; y *= rhs; return *this; }
    inline vec2_t& operator/=(float rhs) { x /= rhs; y /= rhs; return *this; }
    inline vec2_t& operator+=(vec2_t rhs) { x += rhs.x; y += rhs.y; return *this; }
    inline vec2_t& operator-=(vec2_t rhs) { x -= rhs.x; y -= rhs.y; return *this; }
};

inline vec2_t operator+(vec2_t lhs, const float rhs) { return vec2_t(lhs.x + rhs, lhs.y + rhs); }
inline vec2_t operator-(vec2_t lhs, const float rhs) { return vec2_t(lhs.x - rhs, lhs.y - rhs); }
inline vec2_t operator*(vec2_t lhs, const float rhs) { return vec2_t(lhs.x * rhs, lhs.y * rhs); }
inline vec2_t operator/(vec2_t lhs, const float rhs) { return vec2_t(lhs.x / rhs, lhs.y / rhs); }
inline vec2_t operator+(const float lhs, vec2_t rhs) { return vec2_t(lhs + rhs.x, lhs + rhs.y); }
inline vec2_t operator-(const float lhs, vec2_t rhs) { return vec2_t(lhs - rhs.x, lhs - rhs.y); }
inline vec2_t operator*(const float lhs, vec2_t rhs) { return vec2_t(lhs * rhs.x, lhs * rhs.y); }
inline vec2_t operator/(const float lhs, vec2_t rhs) { return vec2_t(lhs / rhs.x, lhs / rhs.y); }
inline vec2_t operator+(vec2_t lhs, const vec2_t rhs) { return vec2_t(lhs.x + rhs.x, lhs.y + rhs.y); }
inline vec2_t operator-(vec2_t lhs, const vec2_t rhs) { return vec2_t(lhs.x - rhs.x, lhs.y - rhs.y); }
inline vec2_t operator*(vec2_t lhs, const vec2_t rhs) { return vec2_t(lhs.x * rhs.x, lhs.y * rhs.y); }
inline vec2_t operator/(vec2_t lhs, const vec2_t rhs) { return vec2_t(lhs.x / rhs.x, lhs.y / rhs.y); }
inline bool operator==(const vec2_t lhs, const vec2_t rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const vec2_t lhs, const vec2_t rhs) { return lhs.x != rhs.x && lhs.y != rhs.y; }
inline vec2_t operator-(vec2_t v) {return v * -1;}

float vec2_t::Angle(vec2_t a, vec2_t b) {
    float v = Dot(a, b) / (a.magnitude() * b.magnitude());
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

[[maybe_unused]] vec2_t vec2_t::ClampMagnitude(vec2_t vector, float maxLength) {
    float length = vector.magnitude();
    if (length > maxLength) vector *= maxLength / length;
    return vector;
}

[[maybe_unused]] float vec2_t::Component(vec2_t a, vec2_t b) {
    return Dot(a, b) / b.magnitude();
}

[[maybe_unused]] float vec2_t::Distance(vec2_t a, vec2_t b) {
    return (a - b).magnitude();
}

float vec2_t::Dot(vec2_t lhs, vec2_t rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

[[maybe_unused]] vec2_t vec2_t::FromPolar(float rad, float theta) {
    vec2_t v;
    v.x = rad * cos(theta);
    v.y = rad * sin(theta);
    return v;
}

[[maybe_unused]] vec2_t vec2_t::Lerp(vec2_t a, vec2_t b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

vec2_t vec2_t::LerpUnclamped(vec2_t a, vec2_t b, float t) {
    return (b - a) * t + a;
}

float vec2_t::Magnitude(vec2_t v) {
    return sqrt(v.sqrMagnitude());
}

[[maybe_unused]] vec2_t vec2_t::Max(vec2_t a, vec2_t b) {
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    return vec2_t(x, y);
}

[[maybe_unused]] vec2_t vec2_t::Min(vec2_t a, vec2_t b) {
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    return vec2_t(x, y);
}

[[maybe_unused]] vec2_t vec2_t::MoveTowards(vec2_t current, vec2_t target, float maxDistanceDelta) {
    vec2_t d = target - current;
    float m = d.magnitude();
    if (m < maxDistanceDelta || m == 0) return target;
    return current + (d * maxDistanceDelta / m);
}

vec2_t vec2_t::Normalize(vec2_t v) {
    float mag = v.magnitude();
    if (mag == 0) return vec2_t::Zero();
    return v / mag;
}

[[maybe_unused]] void vec2_t::OrthoNormalize(vec2_t &normal, vec2_t &tangent) {
    normal = normal.normalized();
    tangent = Reject(tangent, normal);
    tangent = tangent.normalized();
}

vec2_t vec2_t::Project(vec2_t a, vec2_t b) {
    float m = b.magnitude();
    return Dot(a, b) / (m * m) * b;
}

[[maybe_unused]] vec2_t vec2_t::Reflect(vec2_t vector, vec2_t planeNormal) {
    return vector - 2 * Project(vector, planeNormal);
}

vec2_t vec2_t::Reject(vec2_t a, vec2_t b) {
    return a - Project(a, b);
}

[[maybe_unused]] vec2_t vec2_t::RotateTowards(vec2_t current, vec2_t target, float maxRadiansDelta, float maxMagnitudeDelta) {
    float magCur = current.magnitude();
    float magTar = target.magnitude();
    float newMag = magCur + maxMagnitudeDelta * ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));
    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0) return target.normalized() * newMag;
    else if (totalAngle >= M_PI) return -target.normalized() * newMag;
    float axis = current.x * target.y - current.y * target.x;
    axis = axis / fabs(axis);
    if (!(1 - fabs(axis) < 0.00001)) axis = 1;
    current = current.normalized();
    vec2_t newVector = current * cos(maxRadiansDelta) + vec2_t(-current.y, current.x) * sin(maxRadiansDelta) * axis;
    return newVector * newMag;
}

[[maybe_unused]] vec2_t vec2_t::Scale(vec2_t a, vec2_t b) {
    return vec2_t(a.x * b.x, a.y * b.y);
}

[[maybe_unused]] vec2_t vec2_t::Slerp(vec2_t a, vec2_t b, float t) {
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

vec2_t vec2_t::SlerpUnclamped(vec2_t a, vec2_t b, float t) {
    float magA = a.magnitude();
    float magB = b.magnitude();
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    vec2_t relativeVec = (b - a * dot).normalized();
    vec2_t newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float vec2_t::SqrMagnitude(vec2_t v) {
    return v.x * v.x + v.y * v.y;
}

[[maybe_unused]] void vec2_t::ToPolar(vec2_t vector, float &rad, float &theta) {
    rad = vector.magnitude();
    theta = atan2(vector.y, vector.x);
}
