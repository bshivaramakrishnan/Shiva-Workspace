#include <iostream>
using namespace std;

class base {
    int a, b;
public:
    base(int x, int y) : a(x), b(y) {}
    void base1() {
        cout << "Elements of base class : \t" << a << "\t" << b << endl;
    }
};

class l1 : public base {
    int c, d;
public:
    l1(int x, int y, int x1, int y1) : base(x, y), c(x1), d(y1) {}
    void l1sum() {
        cout << "Elements of l1 class : \t" << c << "\t" << d << endl;
        base1();
    }
};

class l2 : public base {
    int e, f;
public:
    l2(int x, int y, int x1, int y1) : base(x, y), e(x1), f(y1) {}
    void l2sum() {
        cout << "Elements of l2 class : \t" << e << "\t" << f << endl;
        base1();
    }
};

class s1 : public l1, public l2 {
    int g, h;
public:
    s1(int x, int y, int x1, int y1, int x2, int y2, int g1, int h1)
        : l1(x, y, x1, y1), l2(x, y, x2, y2), g(g1), h(h1) {}

    void s1sum() {
        cout << "Elements of s1 class : \t" << g << "\t" << h << endl;
        l1::base1();
        l2::base1();
    }
};

int main() {
    s1 obj(1, 2, 3, 4, 5, 6, 7, 8);

    obj.l1sum();
    obj.l2sum();
    obj.s1sum();
    return 0;
}