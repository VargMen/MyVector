#include <iostream>

#include "MyVector.h"
int main() {
    MyVector<int> vec1(5);
    std::cout << vec1 << '\n';

    MyVector<int> vec2{1, 2, 3, 4, 5};
    std::cout << vec2 << '\n';

    MyVector<int> vec3 { vec2 };
    std::cout << vec3 << '\n';

    MyVector<int> vec4 { std::move(vec3) };
    std::cout << vec4 << '\n';

    std::cout << vec4[2] << '\n';

    return 0;
}