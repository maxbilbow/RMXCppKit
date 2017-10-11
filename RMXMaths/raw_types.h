//
// Created by max on 10/10/17.
//

#ifndef RMXCPPKIT_RAW_TYPES_H
#define RMXCPPKIT_RAW_TYPES_H

#define RMXDecimal double

namespace rmx {
    union _Matrix4 {
        _Matrix4();

        explicit _Matrix4(const RMXDecimal[]);

        RMXDecimal &operator[](int);

        struct {
            RMXDecimal m00, m01, m02, m03;
            RMXDecimal m10, m11, m12, m13;
            RMXDecimal m20, m21, m22, m23;
            RMXDecimal m30, m31, m32, m33;
        };

    private:
        RMXDecimal m[16];
    };

    typedef union _Matrix4 Matrix4;

    union _Vector3 {
        _Vector3();

        explicit _Vector3(const RMXDecimal[]);

        _Vector3(RMXDecimal, RMXDecimal, RMXDecimal);

        RMXDecimal &operator[](int);

        struct {
            RMXDecimal x, y, z;
        };
    private:
        RMXDecimal v[3];
    };

    typedef union _Vector3 Vector3;


    union _Vector4 {
        _Vector4();

        explicit _Vector4(const RMXDecimal[]);

        _Vector4(RMXDecimal, RMXDecimal, RMXDecimal, RMXDecimal);

        RMXDecimal &operator[](int);

        struct {
            RMXDecimal x, y, z, w;
        };

    private:
        RMXDecimal v[4];
    };

    typedef union _Vector4 Vector4;

};
#endif //RMXCPPKIT_RAW_TYPES_H
