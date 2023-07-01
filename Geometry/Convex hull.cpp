//convex hull
void convex_hull(vector<P<ll>> &pts, bool inc_collinear = false) {
    P<ll> p0 = *min_element(pts.begin(), pts.end(), [](P<ll> &a, P<ll> &b) {
        return MP(a.y, a.x) < MP(b.y, b.x);
    });

    sort(pts.begin(), pts.end(), [&p0]( P<ll> &a,  P<ll> &b) {
        ll o = p0.cross(a, b);
        if (o != 0)return o > 0;
        return (a - p0).norm() < (b - p0).norm();
    });

    if(inc_collinear){
        int ind = pts.size() - 1;
        while(ind >= 0 && p0.cross(pts[ind], pts.back()) == 0) --ind;
        reverse(pts.begin() + ind + 1, pts.end());
    }

    vector<P<ll>> ch;
    for(int i=0; i<(int)pts.size(); i++){
        int sz = ch.size();
        while(ch.size() > 1 &&
                (ch[sz-2].cross(ch[sz-1], pts[i]) < 0 ||
                (!inc_collinear && ch[sz-2].cross(ch[sz-1], pts[i]) == 0))){
            ch.pop_back();
            sz = ch.size();
        }
        ch.push_back(pts[i]);
    }

    pts = ch;
}