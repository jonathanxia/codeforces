#include "../matrix.h"

int main()
{
    llarray I(2, 2, 0);
    I(0, 0) = 13;
    I(0, 1) = -2;
    I(1, 0) = -5;
    I(1, 1) = 1;

    llarray A(2, 2);
    A(0, 0) = 10;
    A(0, 1) = 8;
    A(1, 0) = -7;
    A(1, 1) = -8;

    llarray B(2, 3, { 1, 2, 3, 4, 5, 6 }, 5);

    print(linalg::mult(A, B, 13));

    print(linalg::identity<ll>(3));

    llarray M(4, 4, { 12, 1, -2, 3, 65, 8, 31, -15, -17, -48, 4, 23, 5, 2, 5, -78 });
    print(linalg::pow(M, 4));
}