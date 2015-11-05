#include "Vector3.hpp"
#include <assert.h>

using namespace matrix;

template class Vector<float, 3>;

int main()
{
    Vector3f v;
    v(0) = 1;
    v(1) = 2;
    v(2) = 3;

    v.print();

    assert(v(0) == 1);
    assert(v(1) == 2);
    assert(v(2) == 3);

    Vector3f v2(4, 5, 6);

    v2.print();

    assert(v2(0) == 4);
    assert(v2(1) == 5);
    assert(v2(2) == 6);

    return 0;
}

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */