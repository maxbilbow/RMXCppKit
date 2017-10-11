//
// Created by max on 10/10/17.
//
#include "raw_types.h"
using namespace rmx;


Matrix4::_Matrix4() {
    m00 = m01 = m02 = m03 =
    m10 = m11 = m12 = m13 =
    m20 = m21 = m22 = m23 =
    m30 = m31 = m32 = m33 = 0;
};

Matrix4::_Matrix4(const RMXDecimal * array) {
    for (int i = 0; i < 16; ++i)
        m[i] = array[i];
};

RMXDecimal& _Matrix4::operator[](int i) {
    return m[i];
};


_Vector3::_Vector3() {
    x = y = z = 0;
}

_Vector3::_Vector3(RMXDecimal x, RMXDecimal y, RMXDecimal z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}


_Vector3::_Vector3(const RMXDecimal * arr)
{
    for (int i = 0; i < 3; ++i)
        v[i] = arr[i];
}

RMXDecimal& _Vector3::operator[](int i) {
    return v[i];
};


_Vector4::_Vector4() {
    x = y = z = w = 0;
}

_Vector4::_Vector4(RMXDecimal x, RMXDecimal y, RMXDecimal z, RMXDecimal w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}


_Vector4::_Vector4(const RMXDecimal * arr)
{
    for (int i = 0; i < 4; ++i)
        v[i] = arr[i];
}

RMXDecimal& _Vector4::operator[](int i) {
    return v[i];
};