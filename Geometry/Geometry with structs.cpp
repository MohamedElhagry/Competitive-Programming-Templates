template<class T>
struct P {
    T x, y;

    P() { ; }
    P(T x, T y) : x(x), y(y) {};

    P operator+(const P &b) { return P(x + b.x, y + b.y); }
    P operator-(const P &b) { return P(x - b.x, y - b.y); }
    P operator*(const T v) { return P(x * v, y * v); }
    P operator/(const T v) { return P(x / v, y / v); }

    T norm() {return x*x + y*y;}
    T abs() { return sqrt(x * x + y * y); }
    P unit() { return *this / abs(); }

    friend istream &operator>>(istream &is, P& pt) {
        is >> pt.x >> pt.y;
        return is;
    }
    friend ostream &operator<<(ostream &os, P pt) {
        os << "" << pt.x << " " << pt.y << " ";
        return os;
    }
};
