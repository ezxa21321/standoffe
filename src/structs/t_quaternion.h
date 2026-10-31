#pragma once
#define SMALL_FLOAT 0.0000000001
#define rad2deg(x) ((x) * (180.f / M_PI))
#define deg2rad(x) ((x) * (M_PI / 180.0))
#define Deg2Rad (2.f * M_PI / 360.f)
#define Rad2Deg (1.f / Deg2Rad)
#include <string>
#include "t_vec3.h"

struct quaternion_t {
    union {
        struct { float x, y, z, w; };
        float data[4];
    };
    inline quaternion_t() noexcept : x(0), y(0), z(0), w(1) {};
    inline quaternion_t(float data[]) noexcept : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
    inline quaternion_t(vec3_t vector, float scalar) noexcept : x(vector.x), y(vector.y), z(vector.z), w(scalar) {};
    inline quaternion_t(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {};
    inline quaternion_t(float Pitch, float Yaw, float Roll) {
        *this = quaternion_t::FromEuler(Pitch, Yaw, Roll);
    };
    inline static quaternion_t Identity() { return quaternion_t(0, 0, 0, 1); };
    [[maybe_unused]] inline static vec3_t Up(quaternion_t q);
    [[maybe_unused]] inline static vec3_t Down(quaternion_t q);
    [[maybe_unused]] inline static vec3_t Left(quaternion_t q);
    [[maybe_unused]] inline static vec3_t Right(quaternion_t q);
    [[maybe_unused]] inline static vec3_t Forward(quaternion_t q);
    [[maybe_unused]] inline static vec3_t Back(quaternion_t q);
    inline static float Angle(quaternion_t a, quaternion_t b);
    inline static quaternion_t Conjugate(quaternion_t rotation);
    inline static float Dot(quaternion_t lhs, quaternion_t rhs);
    [[maybe_unused]] inline static quaternion_t FromAngleAxis(float angle, vec3_t axis);
    [[maybe_unused]] inline static quaternion_t FromEuler(vec3_t rotation);
    inline static quaternion_t FromEuler(float roll, float pitch, float yaw, bool fromDeg = true);
    inline static quaternion_t FromToRotation(vec3_t fromVector, vec3_t toVector);
    [[maybe_unused]] inline static quaternion_t Inverse(quaternion_t rotation);
    [[maybe_unused]] inline static quaternion_t Lerp(quaternion_t a, quaternion_t b, float t);
    inline static quaternion_t LerpUnclamped(quaternion_t a, quaternion_t b, float t);
    [[maybe_unused]] inline static quaternion_t LookRotation(vec3_t forward);
    inline static quaternion_t LookRotation(vec3_t forward, vec3_t upwards);
    inline static float Norm(quaternion_t rotation);
    inline static quaternion_t Normalize(quaternion_t rotation);
    [[maybe_unused]] inline static quaternion_t RotateTowards(quaternion_t from, quaternion_t to, float maxRadiansDelta);
    [[maybe_unused]] inline static quaternion_t Slerp(quaternion_t a, quaternion_t b, float t);
    inline static quaternion_t SlerpUnclamped(quaternion_t a, quaternion_t b, float t);
    inline static quaternion_t ToRotation(const vec3_t& ang);
    [[maybe_unused]] inline static void ToAngleAxis(quaternion_t rotation, float &angle, vec3_t &axis);
    inline static vec3_t ToEuler(quaternion_t rotation, bool toDeg = true);
    [[maybe_unused]] inline vec3_t euler() { return ToEuler(*this); }
    inline quaternion_t normalized() { return Normalize(*this); }
    inline std::string str() {return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w); }
    quaternion_t& operator+=(const quaternion_t& aQuat);
    quaternion_t& operator-=(const quaternion_t& aQuat);
    quaternion_t& operator*=(const float aScalar);
    quaternion_t& operator*=(const quaternion_t& aQuat);
    quaternion_t& operator/=(const quaternion_t& aQuat);
    quaternion_t& operator/=(const float aScalar);
    friend quaternion_t operator+(const quaternion_t& lhs, const quaternion_t& rhs) {
        quaternion_t q(lhs);
        return q += rhs;
    }

    friend quaternion_t  operator-(const quaternion_t& lhs, const quaternion_t& rhs) {
        quaternion_t t(lhs);
        return t -= rhs;
    }

    quaternion_t operator-() const {
        return quaternion_t(-x, -y, -z, -w);
    }

    quaternion_t operator*(const float s) const {
        return quaternion_t(x * s, y * s, z * s, w * s);
    }

    friend quaternion_t  operator*(const float s, const quaternion_t& q) {
        quaternion_t t(q);
        return t *= s;
    }

    friend quaternion_t  operator/(const quaternion_t& q, const float s) {
        quaternion_t t(q);
        return t /= s;
    }

    inline friend quaternion_t operator*(const quaternion_t& lhs, const quaternion_t& rhs) {
        return {lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
                lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z};
    }
    inline friend quaternion_t operator/(const quaternion_t& lhs, const quaternion_t& rhs) {
        return {lhs.w / rhs.x + lhs.x / rhs.w + lhs.y / rhs.z - lhs.z / rhs.y,
                lhs.w / rhs.y + lhs.y / rhs.w + lhs.z / rhs.x - lhs.x / rhs.z,
                lhs.w / rhs.z + lhs.z / rhs.w + lhs.x / rhs.y - lhs.y / rhs.x,
                lhs.w / rhs.w - lhs.x / rhs.x - lhs.y / rhs.y - lhs.z / rhs.z};
    }
};

inline quaternion_t& quaternion_t::operator+=(const quaternion_t& aQuat) {
    x += aQuat.x;
    y += aQuat.y;
    z += aQuat.z;
    w += aQuat.w;
    return *this;
}

inline quaternion_t& quaternion_t::operator-=(const quaternion_t& aQuat) {
    x -= aQuat.x;
    y -= aQuat.y;
    z -= aQuat.z;
    w -= aQuat.w;
    return *this;
}

inline quaternion_t& quaternion_t::operator*=(float aScalar) {
    x *= aScalar;
    y *= aScalar;
    z *= aScalar;
    w *= aScalar;
    return *this;
}

inline quaternion_t& quaternion_t::operator/=(const float aScalar) {
    x /= aScalar;
    y /= aScalar;
    z /= aScalar;
    w /= aScalar;
    return *this;
}

inline quaternion_t& quaternion_t::operator*=(const quaternion_t& rhs) {
    float tempx = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
    float tempy = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
    float tempz = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
    float tempw = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    x = tempx; y = tempy; z = tempz; w = tempw;
    return *this;
}
inline quaternion_t& quaternion_t::operator/=(const quaternion_t& rhs) {
    float tempx = w / rhs.x + x / rhs.w + y / rhs.z - z / rhs.y;
    float tempy = w / rhs.y + y / rhs.w + z / rhs.x - x / rhs.z;
    float tempz = w / rhs.z + z / rhs.w + x / rhs.y - y / rhs.x;
    float tempw = w / rhs.w - x / rhs.x - y / rhs.y - z / rhs.z;
    x = tempx; y = tempy; z = tempz; w = tempw;
    return *this;
}
inline vec3_t operator*(quaternion_t lhs, const vec3_t rhs) {
    vec3_t u = vec3_t(lhs.x, lhs.y, lhs.z);
    float s = lhs.w;
    return u * (vec3_t::Dot(u, rhs) * 2.0f) + rhs * (s * s - vec3_t::Dot(u, u)) + vec3_t::Cross(u, rhs) * (2.0f * s);
}
[[maybe_unused]] vec3_t quaternion_t::Up(quaternion_t q) { return q * vec3_t::up; }
[[maybe_unused]] vec3_t quaternion_t::Down(quaternion_t q) { return q * vec3_t::down; }
[[maybe_unused]] vec3_t quaternion_t::Left(quaternion_t q) { return q * vec3_t::left; }
[[maybe_unused]] vec3_t quaternion_t::Right(quaternion_t q) { return q * vec3_t::right; }
[[maybe_unused]] vec3_t quaternion_t::Forward(quaternion_t q) { return q * vec3_t::forward; }
[[maybe_unused]] vec3_t quaternion_t::Back(quaternion_t q) { return q * vec3_t::back; }

float quaternion_t::Angle(quaternion_t a, quaternion_t b) {
    float dot = Dot(a, b);
    return acosf(fminf(fabs(dot), 1)) * 2;
}

quaternion_t quaternion_t::Conjugate(quaternion_t rotation) {
    return quaternion_t(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

float quaternion_t::Dot(quaternion_t lhs, quaternion_t rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

[[maybe_unused]] quaternion_t quaternion_t::FromAngleAxis(float angle, vec3_t axis) {
    quaternion_t q;
    float m = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    float s = sinf(angle / 2) / m;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = cosf(angle / 2);
    return q;
}

[[maybe_unused]] quaternion_t quaternion_t::FromEuler(vec3_t rotation) {
    return FromEuler(rotation.Rot.Unity.roll, rotation.Rot.Unity.pitch, rotation.Rot.Unity.yaw);
}

quaternion_t quaternion_t::FromEuler(float roll, float pitch, float yaw, bool fromDeg) {
    if (fromDeg) {
        roll *= Deg2Rad;
        pitch *= Deg2Rad;
        yaw *= Deg2Rad;
    }
    double cr = cos((double)roll * 0.5);
    double sr = sin((double)roll * 0.5);
    double cp = cos((double)pitch * 0.5);
    double sp = sin((double)pitch * 0.5);
    double cy = cos((double)yaw * 0.5);
    double sy = sin((double)yaw * 0.5);

    quaternion_t q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}
vec3_t quaternion_t::ToEuler(quaternion_t q, bool toDeg) {
    auto singularity_test = q.y * q.z - q.x * q.w;
    auto Z1 = 2.0f * (q.x * q.y + q.z * q.w);
    auto Z2 = q.y * q.y - q.z * q.z - q.x * q.x + q.w * q.w;
    auto X1 = -1.0f;
    auto X2 = 2.0f * singularity_test;
    float Y1 = 0, Y2 = 0;
    bool n = false;
    const float SINGULARITY_CUTOFF = 0.499999f;
    if (abs(singularity_test) < SINGULARITY_CUTOFF) {
        Y1 = 2.0f * (q.x * q.z + q.y * q.w);
        Y2 = q.z * q.z - q.x * q.x - q.y * q.y + q.w * q.w;
    } else {
        float a, b, c, e;
        a = q.x * q.y + q.z * q.w;
        b = -(q.y * q.z) + q.x * q.w;
        c = q.x * q.y - q.z * q.w;
        e = q.y * q.z + q.x * q.w;
        Y1 = a * e + b * c;
        Y2 = b * e - a * c;
        n = true;
    }
    vec3_t v {X1 * asinf(std::clamp(X2, -1.f, 1.f)), atan2f(Y1, Y2), n ? 0 : atan2f(Z1, Z2)};
    if (toDeg) v *= Rad2Deg;
    return v;
}
quaternion_t quaternion_t::FromToRotation(vec3_t fromVector, vec3_t toVector) {
    float dot = vec3_t::Dot(fromVector, toVector);
    float k = sqrt(fromVector.sqrMagnitude() * toVector.sqrMagnitude());
    if (fabs(dot / k + 1) < 0.00001) {
        vec3_t ortho = fromVector.orthogonal();
        return quaternion_t(ortho.normalized(), 0);
    }
    vec3_t cross = vec3_t::Cross(fromVector, toVector);
    return Normalize(quaternion_t(cross, dot + k));
}

[[maybe_unused]] quaternion_t quaternion_t::Inverse(quaternion_t rotation) {
    float n = Norm(rotation);
    return Conjugate(rotation) / (n * n);
}

[[maybe_unused]] quaternion_t quaternion_t::Lerp(quaternion_t a, quaternion_t b, float t) {
    if (t < 0) return a.normalized();
    else if (t > 1) return b.normalized();
    return LerpUnclamped(a, b, t);
}

quaternion_t quaternion_t::LerpUnclamped(quaternion_t a, quaternion_t b, float t) {
    quaternion_t quaternion;
    if (Dot(a, b) >= 0) quaternion = a * (1 - t) + b * t;
    else quaternion = a * (1 - t) - b * t;
    return quaternion.normalized();
}

[[maybe_unused]] quaternion_t quaternion_t::LookRotation(vec3_t forward) {
    return LookRotation(forward, vec3_t(0, 1, 0));
}

quaternion_t quaternion_t::LookRotation(vec3_t forward, vec3_t upwards) {
    forward = forward.normalized();
    upwards = upwards.normalized();
    if (forward.sqrMagnitude() < SMALL_FLOAT || upwards.sqrMagnitude() < SMALL_FLOAT)
        return quaternion_t::Identity();
    if (1 - fabs(vec3_t::Dot(forward, upwards)) < SMALL_FLOAT)
        return FromToRotation(vec3_t::forward, forward);
    vec3_t right = vec3_t::Cross(upwards, forward).normalized();
    upwards = vec3_t::Cross(forward, right);
    quaternion_t quaternion;
    float radicand = right.x + upwards.y + forward.z;
    if (radicand > 0) {
        quaternion.w = sqrt(1.0f + radicand) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.w);
        quaternion.x = (upwards.z - forward.y) * recip;
        quaternion.y = (forward.x - right.z) * recip;
        quaternion.z = (right.y - upwards.x) * recip;
    }
    else if (right.x >= upwards.y && right.x >= forward.z) {
        quaternion.x = sqrt(1.0f + right.x - upwards.y - forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.x);
        quaternion.w = (upwards.z - forward.y) * recip;
        quaternion.z = (forward.x + right.z) * recip;
        quaternion.y = (right.y + upwards.x) * recip;
    }
    else if (upwards.y > forward.z) {
        quaternion.y = sqrt(1.0f - right.x + upwards.y - forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.y);
        quaternion.z = (upwards.z + forward.y) * recip;
        quaternion.w = (forward.x - right.z) * recip;
        quaternion.x = (right.y + upwards.x) * recip;
    }
    else {
        quaternion.z = sqrt(1.0f - right.x - upwards.y + forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.z);
        quaternion.y = (upwards.z + forward.y) * recip;
        quaternion.x = (forward.x + right.z) * recip;
        quaternion.w = (right.y - upwards.x) * recip;
    }
    return quaternion;
}

float quaternion_t::Norm(quaternion_t rotation) {
    return sqrt(rotation.x * rotation.x +
                rotation.y * rotation.y +
                rotation.z * rotation.z +
                rotation.w * rotation.w);
}

quaternion_t quaternion_t::Normalize(quaternion_t rotation) {
    return rotation / Norm(rotation);
}

[[maybe_unused]] quaternion_t quaternion_t::RotateTowards(quaternion_t from, quaternion_t to, float maxRadiansDelta) {
    float angle = quaternion_t::Angle(from, to);
    if (angle == 0) return to;
    maxRadiansDelta = fmaxf(maxRadiansDelta, angle - (float)M_PI);
    float t = fminf(1, maxRadiansDelta / angle);
    return quaternion_t::SlerpUnclamped(from, to, t);
}

[[maybe_unused]] quaternion_t quaternion_t::Slerp(quaternion_t a, quaternion_t b, float t) {
    if (t < 0) return a.normalized();
    else if (t > 1) return b.normalized();
    return SlerpUnclamped(a, b, t);
}

quaternion_t quaternion_t::SlerpUnclamped(quaternion_t a, quaternion_t b, float t) {
    float n1;
    float n2;
    float n3 = Dot(a, b);
    bool flag = false;
    if (n3 < 0) {
        flag = true;
        n3 = -n3;
    }
    if (n3 > 0.999999) {
        n2 = 1 - t;
        n1 = flag ? -t : t;
    }
    else {
        float n4 = acosf(n3);
        float n5 = 1 / sinf(n4);
        n2 = sinf((1 - t) * n4) * n5;
        n1 = flag ? -sinf(t * n4) * n5 : sinf(t * n4) * n5;
    }
    quaternion_t quaternion;
    quaternion.x = (n2 * a.x) + (n1 * b.x);
    quaternion.y = (n2 * a.y) + (n1 * b.y);
    quaternion.z = (n2 * a.z) + (n1 * b.z);
    quaternion.w = (n2 * a.w) + (n1 * b.w);
    return quaternion.normalized();
}

[[maybe_unused]] void quaternion_t::ToAngleAxis(quaternion_t rotation, float &angle, vec3_t &axis) {
    if (rotation.w > 1) rotation = rotation.normalized();
    angle = 2 * acosf(rotation.w);
    float s = sqrt(1 - rotation.w * rotation.w);
    if (s < 0.00001) {
        axis.x = 1;
        axis.y = 0;
        axis.z = 0;
    } else {
        axis.x = rotation.x / s;
        axis.y = rotation.y / s;
        axis.z = rotation.z / s;
    }
}

quaternion_t quaternion_t::ToRotation(const vec3_t& ang) {
    quaternion_t ret{};
    const float cx = cosf(deg2rad(ang.x) * 0.5);
    const float cy = cosf(deg2rad(ang.y) * 0.5);
    const float cz = cosf(deg2rad(ang.z) * 0.5);
    const float sx = sinf(deg2rad(ang.x) * 0.5);
    const float sy = sinf(deg2rad(ang.y) * 0.5);
    const float sz = sinf(deg2rad(ang.z) * 0.5);
    
    ret.x = cx * sy * sz + cy * cz * sx;
    ret.y = cx * cz * sy - cy * sx * sz;
    ret.z = cx * cy * sz - cz * sx * sy;
    ret.w = sx * sy * sz + cx * cy * cz;
    return ret;
}
