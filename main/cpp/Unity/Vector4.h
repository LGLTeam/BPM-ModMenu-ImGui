#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

struct Vector4
{
    float X;
    float Y;
    float Z;

    Vector4();
    Vector4(float X, float Y, float Z);
    ~Vector4();


    /**
     * Constructors.
     */


    /**
     * Constants for common vectors.
     */
    static inline Vector4 Zero();
    static inline Vector4 One();
    static inline Vector4 Right();
    static inline Vector4 Left();
    static inline Vector4 Up();
    static inline Vector4 Down();
    static inline Vector4 Forward();
    static inline Vector4 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector4 a, Vector4 b);

    /**
     * Returns a vector with its magnitude clamped to m.XLength.
     * @param vector: The target vector.
     * @param m.XLength: The m.Ximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vector4 ClampMagnitude(Vector4 vector, float maXLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vector4 a, Vector4 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline Vector4 Cross(Vector4 lhs, Vector4 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector4 a, Vector4 b);

    static inline char ToChar(Vector4 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector4 lhs, Vector4 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, .Zimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the..Y plane from the.X .Xis.
     * @param phi: The angle from the positive.Z .Xis to the vector.
     * @return: A new vector.
     */
    static inline Vector4 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linear.Y interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go b.Yond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector4 Lerp(Vector4 a, Vector4 b, float t);

    /**
     * Returns a vector linear.Y interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector4 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector4 MAX(Vector4 a, Vector4 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector4 Min(Vector4 a, Vector4 b);

    /**
     * Returns a vector "m.XDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param m.XDistanceDelta: The m.Ximum distance to move.
     * @return: A new vector.
     */
    static inline Vector4 MoveTowards(Vector4 current, Vector4 target,
                                      float maXDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector4 Normalized(Vector4 v);

    /**
     * Returns an arbitra.Y vector orthogonal to the input.
     * This vector is not normal.Zed.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vector4 Orthogonal(Vector4 v);

    /**
     * Creates a new coordinate .Ystem out of the three vectors.
     * Normal.Zes "normal", normal.Zes "tangent" and makes it orthogonal to
     * "normal" and normal.Zes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first .Xis vector.
     * @param tangent: A reference to the second .Xis vector.
     * @param binormal: A reference to the third .Xis vector.
     */
    static inline void OrthoNormalize(Vector4 &normal, Vector4 &tangent,
                                      Vector4 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector4 Project(Vector4 a, Vector4 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visual.Zed as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vector4 ProjectOnPlane(Vector4 vector, Vector4 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vector4 Reflect(Vector4 vector, Vector4 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector4 Reject(Vector4 a, Vector4 b);

    /**
     * Rotates vector "current" towards vector "target" .Y "m.XRadiansDelta".
     * This treats the vectors as directions and will linear.Y interpolate
     * between their magnitudes .Y "m.XMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate aw.Y from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param m.XRadiansDelta: The m.Ximum number of radians to rotate.
     * @param m.XMagnitudeDelta: The m.Ximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector4 RotateTowards(Vector4 current, Vector4 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector4 Scale(Vector4 a, Vector4 b);

    /**
     * Returns a vector rotated towards b from a .Y the percent t.
     * Since interpolation is done spherical.Y, the vector moves at a constant
     * angular veloci.Y. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector4 Slerp(Vector4 a, Vector4 b, float t);

    /**
     * Returns a vector rotated towards b from a .Y the percent t.
     * Since interpolation is done spherical.Y, the vector moves at a constant
     * angular veloci.Y. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector4 SlerpUnclamped(Vector4 a, Vector4 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the .Xact length
     * is not important, and much time can be saved .Y not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector4 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, .Zimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the..Y plane from the.X .Xis.
     * @param phi: The angle from the positive.Z .Xis to the vector.
     */
    static inline void ToSpherical(Vector4 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vector4& operator+=(const float rhs);
    inline struct Vector4& operator-=(const float rhs);
    inline struct Vector4& operator*=(const float rhs);
    inline struct Vector4& operator/=(const float rhs);
    inline struct Vector4& operator+=(const Vector4 rhs);
    inline struct Vector4& operator-=(const Vector4 rhs);
};

inline Vector4 operator-(Vector4 rhs);
inline Vector4 operator+(Vector4 lhs, const float rhs);
inline Vector4 operator-(Vector4 lhs, const float rhs);
inline Vector4 operator*(Vector4 lhs, const float rhs);
inline Vector4 operator/(Vector4 lhs, const float rhs);
inline Vector4 operator+(const float lhs, Vector4 rhs);
inline Vector4 operator-(const float lhs, Vector4 rhs);
inline Vector4 operator*(const float lhs, Vector4 rhs);
inline Vector4 operator/(const float lhs, Vector4 rhs);
inline Vector4 operator+(Vector4 lhs, const Vector4 rhs);
inline Vector4 operator-(Vector4 lhs, const Vector4 rhs);
inline bool operator==(const Vector4 lhs, const Vector4 rhs);
inline bool operator!=(const Vector4 lhs, const Vector4 rhs);



/*******************************************************************************
 * Implementation
 */

Vector4::Vector4() {}
Vector4::Vector4(float X, float Y, float Z) : X(X),Y(Y),Z(Z) {}
Vector4::~Vector4() {}


Vector4 Vector4::Zero() { return Vector4(0, 0, 0); }
Vector4 Vector4::One() { return Vector4(1, 1, 1); }
Vector4 Vector4::Right() { return Vector4(1, 0, 0); }
Vector4 Vector4::Left() { return Vector4(-1, 0, 0); }
Vector4 Vector4::Up() { return Vector4(0, 1, 0); }
Vector4 Vector4::Down() { return Vector4(0, -1, 0); }
Vector4 Vector4::Forward() { return Vector4(0, 0, 1); }
Vector4 Vector4::Backward() { return Vector4(0, 0, -1); }


float Vector4::Angle(Vector4 a, Vector4 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector4 Vector4::ClampMagnitude(Vector4 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector4::Component(Vector4 a, Vector4 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vector4 Vector4::Cross(Vector4 lhs, Vector4 rhs)
{
    float X = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
    float Y = lhs.Z * rhs.X - lhs.X * rhs.Z;
    float Z = lhs.X * rhs.Y - lhs.Y * rhs.X;
    return Vector4(X,Y,Z);
}

float Vector4::Distance(Vector4 a, Vector4 b)
{
    return Vector4::Magnitude(a - b);
}

float Vector4::Dot(Vector4 lhs, Vector4 rhs)
{
    return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

Vector4 Vector4::FromSpherical(float rad, float theta, float phi)
{
    Vector4 v;
    v.X = rad * sin(theta) * cos(phi);
    v.Y = rad * sin(theta) * sin(phi);
    v.Z = rad * cos(theta);
    return v;
}

Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
{
    return (b - a) * t + a;
}

float Vector4::Magnitude(Vector4 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector4 Vector4::MAX(Vector4 a, Vector4 b)
{
    float X = a.X > b.X ? a.X : b.X;
    float Y = a.Y > b.Y ? a.Y : b.Y;
    float Z = a.Z > b.Z ? a.Z : b.Z;
    return Vector4(X,Y,Z);
}

Vector4 Vector4::Min(Vector4 a, Vector4 b)
{
    float X = a.X > b.X ? b.X : a.X;
    float Y = a.Y > b.Y ? b.Y : a.Y;
    float Z = a.Z > b.Z ? b.Z : a.Z;
    return Vector4(X,Y,Z);
}

Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target,
                             float maxDistanceDelta)
{
    Vector4 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector4 Vector4::Normalized(Vector4 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector4::Zero();
    return v / mag;
}

Vector4 Vector4::Orthogonal(Vector4 v)
{
    return v.Z < v.X ? Vector4(v.Y, -v.X, 0) : Vector4(0, -v.Z, v.Y);
}

void Vector4::OrthoNormalize(Vector4 &normal, Vector4 &tangent,
                             Vector4 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vector4 Vector4::Project(Vector4 a, Vector4 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector4 Vector4::ProjectOnPlane(Vector4 vector, Vector4 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vector4 Vector4::Reflect(Vector4 vector, Vector4 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector4 Vector4::Reject(Vector4 a, Vector4 b)
{
    return a - Project(a, b);
}

Vector4 Vector4::RotateTowards(Vector4 current, Vector4 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vector4 axis = Cross(current, target);
    float magaxis = Magnitude(axis);
    if (magaxis == 0)
        axis = Normalized(Cross(current, current + Vector4(3.95, 5.32, -4.24)));
    else
        axis /= magaxis;
    current = Normalized(current);
    Vector4 newVector = current * cos(maxRadiansDelta) +
                        Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vector4 Vector4::Scale(Vector4 a, Vector4 b)
{
    return Vector4(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
}

Vector4 Vector4::Slerp(Vector4 a, Vector4 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector4 Vector4::SlerpUnclamped(Vector4 a, Vector4 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector4 relativeVec = Normalized(b - a * dot);
    Vector4 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector4::SqrMagnitude(Vector4 v)
{
    return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
}

void Vector4::ToSpherical(Vector4 vector, float &rad, float &theta,
                          float &phi)
{
    rad = Magnitude(vector);
    float v = vector.Z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.Y, vector.X);
}


struct Vector4& Vector4::operator+=(const float rhs)
{
    X += rhs;
    Y += rhs;
    Z += rhs;
    return *this;
}

struct Vector4& Vector4::operator-=(const float rhs)
{
    X -= rhs;
    Y -= rhs;
    Z -= rhs;
    return *this;
}

struct Vector4& Vector4::operator*=(const float rhs)
{
    X *= rhs;
    Y *= rhs;
    Z *= rhs;
    return *this;
}

struct Vector4& Vector4::operator/=(const float rhs)
{
    X /= rhs;
    Y /= rhs;
    Z /= rhs;
    return *this;
}

struct Vector4& Vector4::operator+=(const Vector4 rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    return *this;
}

struct Vector4& Vector4::operator-=(const Vector4 rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    return *this;
}

char Vector4::ToChar(Vector4 a) {
    const char* X = (const char*)(int)a.X;
    const char* Y = (const char*)(int)a.Y;
    const char* Z = (const char*)(int)a.Z;
    char buffer[25];
    strncpy(buffer, X, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, Y, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, Z, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    return buffer[25];
}

Vector4 operator-(Vector4 rhs) { return rhs * -1; }
Vector4 operator+(Vector4 lhs, const float rhs) { return lhs += rhs; }
Vector4 operator-(Vector4 lhs, const float rhs) { return lhs -= rhs; }
Vector4 operator*(Vector4 lhs, const float rhs) { return lhs *= rhs; }
Vector4 operator/(Vector4 lhs, const float rhs) { return lhs /= rhs; }
Vector4 operator+(const float lhs, Vector4 rhs) { return rhs += lhs; }
Vector4 operator-(const float lhs, Vector4 rhs) { return rhs -= lhs; }
Vector4 operator*(const float lhs, Vector4 rhs) { return rhs *= lhs; }
Vector4 operator/(const float lhs, Vector4 rhs) { return rhs /= lhs; }
Vector4 operator+(Vector4 lhs, const Vector4 rhs) { return lhs += rhs; }
Vector4 operator-(Vector4 lhs, const Vector4 rhs) { return lhs -= rhs; }

bool operator==(const Vector4 lhs, const Vector4 rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

bool operator!=(const Vector4 lhs, const Vector4 rhs)
{
    return !(lhs == rhs);
}
