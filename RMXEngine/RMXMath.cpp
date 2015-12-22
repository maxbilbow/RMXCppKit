//
//  RMXMath.cpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

//#import "RMXEngine.hpp"
//#import "RMXMath.hpp"
//#import <GLKit/GLKVector3.h>
#include "Includes.h"
#include <math.h>
using namespace std;


Vector3 RMXMatrix4Position(Matrix4 m) {
    return GLKVector3Make(m.m30, m.m31, m.m32);
}

Matrix4 RMXMatrix4Negate(Matrix4 m) {
    for(int i=0; i<15;++i)
        m.m[i] *= -1;
    return m;
}

Matrix4 RMXMatrix4NegatePosition(Matrix4 m) {
    for(int i=12; i<15;++i)
        m.m[i] *= -1;
    return m;
}


Vector3 RMXMatrix3MakeEuler(Matrix4 m) {
    return GLKVector3Make (atan2f(-m.m20, m.m00),
                           asinf ( m.m10),
                           atan2f(-m.m12, m.m11)
                           );
//    m.m30 = m.m31 = m.m32 = 0;
//    return GLKVector3Make (
//                   atan2f(-m.m12, m.m11),
//                   atan2f(-m.m20, m.m00),
//                   asinf ( m.m10)
//                           );
}

Matrix4 RMXMatrix4RotateAboutPoint(Matrix4 m, float radians, Vector3 axis, Vector3 point) {
    
    Vector3 p = RMXMatrix4Position(m);
    m.m30 = point.x;
    m.m31 = point.y;
    m.m32 = point.z;
    m = GLKMatrix4RotateWithVector3(m, radians, axis);
    m.m30 = p.x;
    m.m31 = p.y;
    m.m32 = p.z;
    
    return m;
}

Matrix4& Matrix4SetPositionZero(Matrix4& m) {
    m.m30 = m.m31 = m.m32 = 0;
    return m;
}

Matrix4& RMXMatrix4SetPosition(Matrix4& m, Vector3 pos) {
    m.m30 = pos.x; m.m31 = pos.y; m.m32 = pos.z;
    return m;
}


Matrix4 operator*(Matrix4 lhs,  Matrix4 rhs) {
    return GLKMatrix4Multiply(lhs, rhs);
}


Matrix4 operator*(Matrix4 lhs,  Vector3 rhs) {
    return GLKMatrix4ScaleWithVector3(lhs, rhs);
}

Matrix4 operator*(Matrix4 lhs,  float rhs) {
    
    return GLKMatrix4Multiply(lhs, GLKMatrix4MakeScale(rhs, rhs, rhs));
}


Vector3 operator+(Vector3 lhs,  Vector3 rhs) {
    return GLKVector3Add(lhs, rhs);
}

Vector3 operator-(Vector3 lhs,  Vector3 rhs) {
    return GLKVector3Subtract(lhs, rhs);
}

Vector3 operator*(Vector3 lhs,  Vector3 rhs) {
    return GLKVector3Multiply(lhs, rhs);
}

Vector3 operator/(Vector3 lhs,  Vector3 rhs) {
    return GLKVector3Divide(lhs, rhs);
}

Vector3 operator*(Vector3 lhs,  float rhs) {
    return GLKVector3MultiplyScalar(lhs, rhs);
}

Vector3 operator/(Vector3 lhs,  float rhs) {
    return GLKVector3DivideScalar(lhs, rhs);
}

bool operator==(Vector3 lhs,  Vector3 rhs) {
    for (int i=0;i<16;++i)
        if (lhs.v[i] != rhs.v[i]) {
            //            cout << lhs.m[i] << " != " << rhs.m[i] << ", diff: " << (lhs.m[i] - rhs.m[i]) << endl;
            return false;
        }
    return true;
}

bool operator!=(Vector3 lhs,  Vector3 rhs) {
    for (int i=0;i<16;++i)
        if (lhs.v[i] != rhs.v[i]) {
            //            cout << lhs.m[i] << " != " << rhs.m[i] << ", diff: " << (lhs.m[i] - rhs.m[i]) << endl;
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

void operator*=(Vector3& lhs,  float rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
}

void operator/=(Vector3& lhs,  float rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
}

string operator+(string lhs, float rhs) {
    return lhs + to_string(rhs);
}

string operator+(float lhs, string rhs) {
    return to_string(lhs) + rhs;
}

string& operator+=(string& lhs, float rhs) {
    return lhs += to_string(rhs);
}

string S(float f) {
    return to_string(f);
}

std::ostream& operator<<(std::ostream& in,  Matrix4 m) {
    string s = "Matrix:\n";
    s += S(m.m00) + ", " + m.m01 + ", " + m.m02 + ", " + m.m03 + "\n";
    s += S(m.m10) + ", " + m.m11 + ", " + m.m12 + ", " + m.m13 + "\n";
    s += S(m.m20) + ", " + m.m21 + ", " + m.m22 + ", " + m.m23 + "\n";
    s += S(m.m30) + ", " + m.m31 + ", " + m.m32 + ", " + m.m33;
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
        if (lhs.m[i] != rhs.m[i])
            return false;
    return true;
}



bool operator!=(Matrix4 lhs,  Matrix4 rhs) {
    for (int i=0;i<16;++i)
        if (lhs.m[i] != rhs.m[i]) {
//            cout << lhs.m[i] << " != " << rhs.m[i] << ", diff: " << (lhs.m[i] - rhs.m[i]) << endl;
            return true;
        }
    return false;
}


double rBounds(int min, int max) {
    
    return random() % (max - min) + min;
}

