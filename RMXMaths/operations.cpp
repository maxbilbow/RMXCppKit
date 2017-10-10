//
// Created by max on 10/10/17.
//

#include "RMXMaths.h"
#include <cmath>


using namespace std;
using namespace rmx;


Vector3 rmx::Matrix4Position(Matrix4 m) {
    return Vector3Make(m.m30, m.m31, m.m32);
}

Matrix4 rmx::Matrix4Negate(Matrix4 m) {
    for(int i=0; i<15;++i)
        m[i] *= -1;
    return m;
}

Matrix4 rmx::Matrix4NegatePosition(Matrix4 m) {
    for(int i=12; i<15;++i)
        m[i] *= -1;
    return m;
}


Vector3 rmx::Matrix3MakeEuler(Matrix4 m) {
    return Vector3Make (atan2(-m.m20, m.m00),
                           asin ( m.m10),
                           atan2(-m.m12, m.m11)
    );
//    m.m30 = m.m31 = m.m32 = 0;
//    return GLKVector3Make (
//                   atan2f(-m.m12, m.m11),
//                   atan2f(-m.m20, m.m00),
//                   asinf ( m.m10)
//                           );
}

Matrix4 rmx::Matrix4RotateAboutPoint(Matrix4 m, RMXDouble radians, Vector3 axis, Vector3 point) {

    Vector3 p = rmx::Matrix4Position(m);
    m.m30 = point.x;
    m.m31 = point.y;
    m.m32 = point.z;
    m = rmx::Matrix4RotateWithVector3(m, radians, axis);
    m.m30 = p.x;
    m.m31 = p.y;
    m.m32 = p.z;

    return m;
}

Matrix4 rmx::Matrix4RotateWithVector3(Matrix4 matrix4, RMXDouble radians, Vector3 vector3) {
    return Matrix4(); //TODO GLKMatrix4RotateWithVector3
}

Matrix4& Matrix4SetPositionZero(Matrix4& m) {
    m.m30 = m.m31 = m.m32 = 0;
    return m;
}

Matrix4& rmx::Matrix4SetPosition(Matrix4& m, Vector3 pos) {
    m.m30 = pos.x; m.m31 = pos.y; m.m32 = pos.z;
    return m;
}


Matrix4 operator*(Matrix4 lhs,  Matrix4 rhs) {
    return Matrix4(); //todo GLKMatrix4Multiply(lhs, rhs);
}


Matrix4 operator*(Matrix4 lhs,  Vector3 rhs) {
    return Matrix4();//todo GLKMatrix4ScaleWithVector3(lhs, rhs);
}

Matrix4 operator*(Matrix4 lhs, RMXDouble rhs) {

    return Matrix4();//todo GLKMatrix4Multiply(lhs, GLKMatrix4MakeScale(rhs, rhs, rhs));
}


Vector3 operator+(Vector3 lhs,  Vector3 rhs) {
    Vector3 v;
    v.x = lhs.x + rhs.x;
    v.y = lhs.y + rhs.y;
    v.z = lhs.z + rhs.z;
    return v;
}

Vector3 operator-(Vector3 lhs,  Vector3 rhs) {
    Vector3 v;
    v.x = lhs.x - rhs.x;
    v.y = lhs.y - rhs.y;
    v.z = lhs.z - rhs.z;
    return v;
}

Vector3 operator*(Vector3 lhs,  Vector3 rhs) {
    Vector3 v;
    v.x = lhs.x * rhs.x;
    v.y = lhs.y * rhs.y;
    v.z = lhs.z * rhs.z;
    return v;
//    todo: is this the same as GLKVector3Multiply(lhs, rhs);
}

Vector3 operator/(Vector3 lhs,  Vector3 rhs) {
    Vector3 v;
    v.x = lhs.x / rhs.x;
    v.y = lhs.y / rhs.y;
    v.z = lhs.z / rhs.z;
    return v;
//    todo: is this the same as  GLKVector3Divide(lhs, rhs);
}

Vector3 operator*(Vector3 lhs, RMXDouble rhs) {
    Vector3 v;
    v.x = lhs.x * rhs;
    v.y = lhs.y * rhs;
    v.z = lhs.z * rhs;
    return v;
}

Vector3 operator/(Vector3 lhs,  RMXDouble rhs) {
    Vector3 v;
    v.x = lhs.x / rhs;
    v.y = lhs.y / rhs;
    v.z = lhs.z / rhs;
    return v;
}

bool operator==(Vector3 lhs,  Vector3 rhs) {
    for (int i=0;i<16;++i)
        if (lhs[i] != rhs[i]) {
            //            cout << lhs[i] << " != " << rhs[i] << ", diff: " << (lhs[i] - rhs[i]) << endl;
            return false;
        }
    return true;
}

bool operator!=(Vector3 lhs,  Vector3 rhs) {
    for (int i=0;i<16;++i)
        if (lhs[i] != rhs[i]) {
            //            cout << lhs[i] << " != " << rhs[i] << ", diff: " << (lhs[i] - rhs[i]) << endl;
            return true;
        }
    return false;
}

bool isZero(Vector3 v){
    return v.x == 0 && v.y == 0 && v.z == 0;
}

void operator+=(Vector3& lhs,  Vector3 rhs){
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
}

void operator-=(Vector3& lhs,  Vector3 rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
}

void operator*=(Vector3& lhs,  Vector3 rhs){
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    lhs.z *= rhs.z;
}

void operator/=(Vector3& lhs,  Vector3 rhs) {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    lhs.z /= rhs.z;
}

void operator*=(Vector3& lhs,  RMXDouble rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
}

void operator/=(Vector3& lhs,  RMXDouble rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
}

string operator+(string lhs, RMXDouble rhs) {
    return lhs + to_string(rhs);
}

string operator+(RMXDouble lhs, string rhs) {
    return to_string(lhs) + rhs;
}

string& operator+=(string& lhs, RMXDouble rhs) {
    return lhs += to_string(rhs);
}

string S(RMXDouble f) {
    return to_string(f);
}

std::ostream& operator<<(std::ostream& in,  Matrix4 m) {
    string s = "Matrix:\n";
    s += S(m.m00) + ", " + S(m.m01) + ", " + S(m.m02) + ", " + S(m.m03) + "\n";
    s += S(m.m10) + ", " + S(m.m11) + ", " + S(m.m12) + ", " + S(m.m13) + "\n";
    s += S(m.m20) + ", " + S(m.m21) + ", " + S(m.m22) + ", " + S(m.m23) + "\n";
    s += S(m.m30) + ", " + S(m.m31) + ", " + S(m.m32) + ", " + S(m.m33);
    return in << s;
}

std::ostream& operator<<(std::ostream& in,  Vector3 v) {
    return in << v.x << ", " << v.y << ", " << v.z;
}

std::ostream& operator<<(std::ostream& in,  Vector4 v) {
    return in << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
}

bool operator==(Matrix4 lhs,  Matrix4 rhs) {
    for (int i=0;i<16;++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}



bool operator!=(Matrix4 lhs,  Matrix4 rhs) {
    for (int i=0;i<16;++i)
        if (lhs[i] != rhs[i]) {
            return true;
        }
    return false;
}


RMXDouble rBounds(int min, int max) {

    return random() % (max - min) + min;
}

