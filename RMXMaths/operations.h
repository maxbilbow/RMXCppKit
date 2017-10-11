//
// Created by max on 10/10/17.
//

#ifndef RMXCPPKIT_OPERATIONS_H
#define RMXCPPKIT_OPERATIONS_H
#define PI 3.14159265359
#define PI_OVER_180 (PI/180)

#define PIf 3.14159265359
#define PI_OVER_180f (PIf/180)

#include <iostream>
namespace rmx {
    Vector3 Vector3Make(RMXDecimal x=0, RMXDecimal y=0, RMXDecimal z=0);

    Vector3 Matrix4Position(Matrix4 m);


    Matrix4 Matrix4Negate(Matrix4 m);

    Matrix4 Matrix4NegatePosition(Matrix4 m);

    Vector3 Matrix3MakeEuler(Matrix4 m);

    Matrix4 Matrix4RotateWithVector3(Matrix4 matrix4, RMXDecimal radians, Vector3 vector3);

    Matrix4 Matrix4RotateAboutPoint(Matrix4 m, RMXDecimal radians, Vector3 axis, Vector3 point);

    Matrix4 &Matrix4SetPosition(Matrix4 &m, Vector3 position);

    Matrix4 &Matrix4SetPositionZero(Matrix4 &m);

    RMXDecimal rBounds(int min, int max);

    bool isZero(Vector3 v);

}

using namespace rmx;
Matrix4 operator*(Matrix4 lhs, Matrix4 rhs);

Matrix4 operator*(Matrix4 lhs, Vector3 rhs);

Matrix4 operator*(Matrix4 lhs, RMXDecimal rhs);

bool operator==(Matrix4 lhs, Matrix4 rhs);

bool operator!=(Matrix4 lhs, Matrix4 rhs);


Vector3 operator+(Vector3 lhs, Vector3 rhs);

Vector3 operator-(Vector3 lhs, Vector3 rhs);

Vector3 operator*(Vector3 lhs, Vector3 rhs);

Vector3 operator/(Vector3 lhs, Vector3 rhs);

Vector3 operator*(Vector3 lhs, RMXDecimal rhs);

Vector3 operator/(Vector3 lhs, RMXDecimal rhs);

bool operator==(Vector3 lhs, Vector3 rhs);

bool operator!=(Vector3 lhs, Vector3 rhs);

void operator+=(Vector3 &lhs, Vector3 rhs);

void operator-=(Vector3 &lhs, Vector3 rhs);

void operator*=(Vector3 &lhs, Vector3 rhs);

void operator/=(Vector3 &lhs, Vector3 rhs);

void operator*=(Vector3 &lhs, RMXDecimal rhs);

void operator/=(Vector3 &lhs, RMXDecimal rhs);

std::ostream &operator<<(std::ostream &in, Vector3 m);

std::ostream &operator<<(std::ostream &in, Vector4 v);

std::ostream &operator<<(std::ostream &in, Matrix4 m);

std::string operator+(std::string lhs, RMXDecimal rhs);

std::string operator+(RMXDecimal lhs, std::string rhs);

std::string &operator+=(std::string &lhs, RMXDecimal rhs);
#endif //RMXCPPKIT_OPERATIONS_H
