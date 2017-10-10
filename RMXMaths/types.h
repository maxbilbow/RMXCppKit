//
// Created by max on 10/10/17.
//

#ifndef CPPKIT_TYPES_H
#define CPPKIT_TYPES_H

#define PI 3.14159265359f
#define PI_OVER_180 (PI/180)
#define RMXDouble long double

namespace rmx {
    struct Matrix4 {
        RMXDouble m00, m01, m02, m03;
        RMXDouble m10, m11, m12, m13;
        RMXDouble m20, m21, m22, m23;
        RMXDouble m30, m31, m32, m33;

        Matrix4();

        RMXDouble & operator[](int);
    };

    struct Vector3 {
        RMXDouble x, y, z;
        Vector3();
        RMXDouble & operator[](int position);
        static const Vector3 Zero;
    };

    Vector3 Vector3Make(RMXDouble=0, RMXDouble=0, RMXDouble=0);

    struct Vector4 {
        RMXDouble x, y, z, w;
        Vector4();
        RMXDouble & operator[](int position);
        static const Vector4 Zero;
    };

    Vector4 Vector4Make(RMXDouble=0, RMXDouble=0, RMXDouble=0, RMXDouble=0);

    struct Quaternion;


}
#endif //CPPKIT_TYPES_H
