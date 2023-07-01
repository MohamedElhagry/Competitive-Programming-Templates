const double PI = acos(-1);

template<class T>
struct P {
    T x, y;

    P() { ; }

    P(T x, T y) : x(x), y(y) {};

    P operator+(const P b) { return P(x + b.x, y + b.y); }
    P operator-(const P b) { return P(x - b.x, y - b.y); }
    P operator*(const T v) { return P(x * v, y * v); }
    P operator/(const T v) { return P(x / v, y / v); }

    bool operator== (const P b){ return MP(x, y) == MP(b.x, b.y);}
    T cross(P b) const{ return x * b.y - y * b.x; };
    T dot(P b) const{ return x * b.x + y * b.y; };
    T cross(P b,  P c) const { return (b - *this).cross(c - *this); }

    T norm() { return x * x + y * y; }
    long double abs() { return sqrt(x * x + y * y); }

    P unit() { return *this / abs(); }

    friend istream &operator>>(istream &is, P &pt) {
        is >> pt.x >> pt.y;
        return is;
    }

    friend ostream &operator<<(ostream &os, P pt) {
        os << "(" << pt.x << ", " << pt.y << ")";
        return os;
    }
};