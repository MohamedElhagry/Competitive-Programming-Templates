vector<P<C>> circleLineIntersect(C a, C b, C c, C r) {
    //circle is centered at the origin
    //distance between the line and the closest point to is c/sqrt(a*a + b*b)
    //vector perpendicular to line is (a,b),
    // and the vector collinear to the line is (-b,a)
    C scaleFactor = c / (a * a + b * b);
    C xo = -a * scaleFactor, yo = -b * scaleFactor;

    //if dist^2 = c^2/(a^2 + b^2) is greater than r^2
    if (c * c > r * r * (a * a + b * b) + eps)
        return {};
    if (fabs(c * c - r * r * (a * a + b * b)) < eps)
        return {P<C>(xo, yo)};

    //now there are two solutions
    //calculate the distance between the closest point and the two solutions
    C d = r * r - c * c / (a * a + b * b);
    //d / sqrt(b^2 + a^2)
    C secondScaleFactor = sqrt(d / (a * a + b * b));
    vector<P<C>> ret;
    ret.pb(P<C>(xo + secondScaleFactor * -b, yo + secondScaleFactor * a));
    ret.pb(P<C>(xo + secondScaleFactor * b, yo + secondScaleFactor * -a));
    return ret;
}

vector<P<C>> circleLineIntersect(C a, C b, C c, C r, P<C> cen) {
    //scale c appropriately
    c += cen.x * a + cen.y * b;
    auto res = circleLineIntersect(a, b, c, r);
    for (auto &e:res) {
        e.x += cen.x;
        e.y += cen.y;
    }
    return res;
}