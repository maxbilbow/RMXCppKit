#include <iostream>
#include "RMXMaths/RMXMaths.h"

using namespace rmx;
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Matrix4 m4;
    cout << m4 << endl;
    for (int i = 0; i< 16; ++i)
        m4[i] = i;
    cout << m4 << endl;

    return 0;
}