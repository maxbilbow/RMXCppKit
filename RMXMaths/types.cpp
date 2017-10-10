//
// Created by max on 10/10/17.
//

#include <exception>
#include "types.h"

using namespace rmx;

Matrix4::Matrix4() {
    m00 = m01 = m02 = m03 =
    m10 = m11 = m12 = m13 =
    m20 = m21 = m22 = m23 =
    m30 = m31 = m32 = m33 = 0;
}

RMXDouble & Matrix4::operator[](int position) {
    switch (position) {
        case 0:
            return m00;
        case 1:
            return
                    m01;
        case 2:
            return
                    m02;
        case 3:
            return
                    m03;
        case 4:
            return
                    m10;
        case 5:
            return
                    m11;
        case 6:
            return
                    m12;
        case 7:
            return
                    m13;
        case 8:
            return
                    m20;
        case 9:
            return
                    m21;
        case 10:
            return
                    m22;
        case 11:
            return
                    m23;
        case 12:
            return
                    m30;
        case 13:
            return
                    m31;
        case 14:
            return
                    m32;
        case 15:
            return
                    m33;
        default:
            throw std::exception();//"Not a valid matrix position: " + position);
    }
};

Vector4::Vector4()
{
    x=y=z=w=0;
}

RMXDouble & Vector4::operator[](int position) {
    switch (position) {
        case 0:
            return
                    x;
        case 1:
            return
                    y;
        case 2:
            return
                    z;
        case 3:
            return
                    w;
        default:
           throw std::exception();//todo throw error?
    }
};



Vector3::Vector3() {
    x=y=z=0;
}

RMXDouble & Vector3::operator[](int position) {
    switch (position) {
        case 0:
            return
                    x;
        case 1:
            return
                    y;
        case 2:
            return
                    z;
        default:
            throw std::exception();//todo detailed error
    }
};


Vector3 rmx::Vector3Make(RMXDouble x, RMXDouble y, RMXDouble z)
{
    Vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vector4 rmx::Vector4Make(RMXDouble x, RMXDouble y, RMXDouble z, RMXDouble w)
{
    Vector4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}