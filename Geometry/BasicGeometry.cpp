const long double PI = acos(-1);
typedef long double C;
typedef complex<C> P;
#define X real()
#define Y imag()
#define dot(a, b) (conj(a) * (b)).X
#define cp(a, b) ((conj(a)) * (b)).Y
#define rotate(a, s)  ((a) * polar(one, s))


long double getDistLine(P x, P s1, P s2){
    return abs(cp(s2 - x, s1 - x)) / abs(s2 - s1);
}

long double getDistRay(P x, P s1, P s2){
    long double distSeg = getDistLine(x, s1, s2);
    P v1 = s1 - x;
    P v2 = s2 - s1;
    if(dot(v1, v2) > 0)
        return abs(v1);
    return distSeg;
}

long double getDistSeg(P x, P s1, P s2){
    long double distSeg = getDistLine(x, s1, s2);
    P v1 = s1 - x;
    P v3 = s2 - s1;
    P v2 = s2 - x;
    P v4 = s1 - s2;
    if(dot(v1, v3) > 0  || dot(v2, v4) > 0)
        return min(abs(v1), abs(v2));
    return distSeg;
}

long double getDistSegs(P s1, P s2, P r1, P r2) {
    long double ans = min(
            {getDistSeg(s1, r1, r2), getDistSeg(s2, r1, r2), getDistSeg(r1, s1, s2), getDistSeg(r2, s1, s2)});
    if ( cp(s2-s1,r1-s2)*cp(s2-s1,r2-s2) < 0 && cp(r2-r1,s1-r2)*cp(r2-r1,s2-r2) < 0)
        ans = 0;
    return ans;
}
