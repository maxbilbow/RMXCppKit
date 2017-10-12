#include <iostream>
#include <RMXMaths.h>

using namespace rmx;
using namespace std;

struct u_test {
    union {
        struct {
            int a, b, c;
        };
        int n[3];
    };
};

int main() {
    cout << "Hello, World!" << endl;

    Matrix4 m4;
    cout << m4 << endl;
    for (int i = 0; i< 16; ++i)
        m4[i] = i;
    cout << m4 << endl;


     u_test uTest;
    uTest.a = 1;
    uTest.b = 2;
    uTest.c = 3;

    cout << uTest.a     << ", " << uTest.b      << ", " << uTest.c      << endl;
    cout << uTest.n[0]  << ", " << uTest.n[1]   << ", " << uTest.n[2]   << endl;
    return 0;
}