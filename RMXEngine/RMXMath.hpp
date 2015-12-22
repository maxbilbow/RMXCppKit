//
//  RMXMath.hpp
//  RMXKit
//
//  Created by Max Bilbow on 19/08/2015.
//  Copyright © 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef RMXMath_hpp
#define RMXMath_hpp

#include <stdio.h>

#endif /* RMXMath_hpp */

#define PI 3.14159265359f
#define PI_OVER_180 (PI/180)

static const Vector3 Vector3Zero = GLKVector3Make(0,0,0);
Vector3 RMXMatrix4Position(Matrix4 m);
Matrix4 RMXMatrix4Negate(Matrix4 m);
Matrix4 RMXMatrix4NegatePosition(Matrix4 m) ;
Vector3 RMXMatrix3MakeEuler(Matrix4 m);
Matrix4 RMXMatrix4RotateAboutPoint(Matrix4 m, float radians, Vector3 axis, Vector3 point);
Matrix4& RMXMatrix4SetPosition(Matrix4& m, Vector3 position);
Matrix4& Matrix4SetPositionZero(Matrix4& m);
Matrix4 operator*(Matrix4 lhs,  Matrix4 rhs);
Matrix4 operator*(Matrix4 lhs,  Vector3 rhs);
Matrix4 operator*(Matrix4 lhs,  float rhs);
bool operator==(Matrix4 lhs,  Matrix4 rhs);
bool operator!=(Matrix4 lhs,  Matrix4 rhs);


Vector3 operator+(Vector3 lhs,  Vector3 rhs);
Vector3 operator-(Vector3 lhs,  Vector3 rhs);
Vector3 operator*(Vector3 lhs,  Vector3 rhs);
Vector3 operator/(Vector3 lhs,  Vector3 rhs);

Vector3 operator*(Vector3 lhs,  float rhs);
Vector3 operator/(Vector3 lhs,  float rhs);
bool isZero(Vector3 v);
bool operator==(Vector3 lhs,  Vector3 rhs);
bool operator!=(Vector3 lhs,  Vector3 rhs);

void operator+=(Vector3& lhs,  Vector3 rhs);
void operator-=(Vector3& lhs,  Vector3 rhs);
void operator*=(Vector3& lhs,  Vector3 rhs);
void operator/=(Vector3& lhs,  Vector3 rhs);

void operator*=(Vector3& lhs,  float rhs);
void operator/=(Vector3& lhs,  float rhs);

std::ostream& operator<<(std::ostream& in,  Vector3 m);
std::ostream& operator<<(std::ostream& in,  Vector4 v);
std::ostream& operator<<(std::ostream& in,  Matrix4 m);

std::string operator+(std::string lhs, float rhs);

std::string operator+(float lhs, std::string rhs);

std::string& operator+=(std::string& lhs, float rhs);

double rBounds(int min, int max);