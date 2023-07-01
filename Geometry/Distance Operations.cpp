template <class T>
long double lineDist(P<T>& x, P<T>& a, P<T>& b){
    return abs(a.cross(b, x)) / (b-a).abs();
}

template <class T>
long double rayDist(P<T> x, P<T> s1, P<T> s2){
    long double distSeg = lineDist(x, s1, s2);
    P<T> v1 = s1 - x;
    P<T> v2 = s2 - s1;
    if(v1.dot(v2) > 0)
        return v1.abs();
    return distSeg;
}

template <class T>
long double segDist(P<T> x, P<T> s1, P<T> s2){
    long double distLine = lineDist(x, s1, s2);
    P<T> v1 = s1 - x;
    P<T> v3 = s2 - s1;
    P<T> v2 = s2 - x;
    P<T> v4 = s1 - s2;
    if(v1.dot(v3) > 0  || v2.dot(v4) > 0)
        return min(v1.abs(), v2.abs());
    return distLine;
}

template <class P>
long double onSeg(P s1, P s2, P x){
    return segDist(x, s1, s2) < - EPS;
}

template <class P>
vector<P> segInter(P a, P b, P c, P d){
    auto oa = c.cross(d, a), ob = c.cross(d, b),
        oc = a.cross(b, c), od = a.cross(b, d);

    //very complicated formula, don't try to understand from here, only for quick writing
    if(oa * ob < 0 && oc * od < 0)
        return {(a * ob - b * oa) / (ob - oa)};

    set<P> s;
    if(onSeg(c, d, a))s.insert(a);
    if(onSeg(c, d, b))s.insert(b);
    if(onSeg(a, b, c))s.insert(c);
    if(onSeg(a, b, d))s.insert(d);
    return {s.begin(), s.end()};
}

template<class P>
pair<int, P> lineInter(P a, P b, P c, P d) {
    auto dir = (b - a).cross(d - c);
    if (dir == 0)
        return {-(a.cross(b, c) == 0), P(0, 0)};
    auto p = c.cross(b, d), q = c.cross(d, a);
    return {1, (a * p + b * q) / dir};
}