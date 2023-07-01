
template<class P>
pair<int, P> lineInter(P a, P b, P c, P d) {
    auto dir = (b - a).cross(d - c);
    if (dir == 0)
        return {-(a.cross(b, c) == 0), P(0, 0)};
    auto p = c.cross(b, d), q = c.cross(d, a);
    return {1, (a * p + b * q) / dir};
}


template <class P>
struct HalfPlane{
    P p, pq;
    long double angle;

    HalfPlane(){}
    HalfPlane(P& a, P& b):p(a), pq(b-a){
        angle = pq.angle();
    }

    bool out(P r){
        return pq.cross(r-p) < -EPS;
    }

    bool operator < (const HalfPlane<P>& e)const{
        return angle < e.angle;
    }

    P inter( HalfPlane<P>& s){
        return lineInter(s.p, s.p + s.pq, p, p + pq).S;
    }
};

template <class P>
vector<P> HalfPlaneInter(vector<HalfPlane<P>>& H) {
    //bounding box
    P box[4] = {P(-OO, -OO),
             P(OO, -OO),
             P(OO, OO),
             P(-OO, OO)};

    for (int i = 0; i < 4; i++) {
        HalfPlane<P> temp(box[i], box[(i + 1) % 4]);
        H.pb(temp);
    }

    sort(H.begin(), H.end());
    deque<HalfPlane<P>> dq;
    int len = 0;
    for (int i = 0; i < (int) H.size(); i++) {
        while (len > 1 && H[i].out(dq[len - 1].inter(dq[len - 2]))) {
            dq.pop_back();
            --len;
        }
        while (len > 1 && H[i].out(dq[0].inter(dq[1]))) {
            dq.pop_front();
            --len;
        }

        if (len > 0 && fabsl(H[i].pq.cross(dq.back().pq)) < EPS) {
            //opposite direction, no planes at all
            if (H[i].pq.dot(dq.back().pq) < 0.0)
                return vector<P>();

            if (H[i].out(dq[len - 1].p)) {
                dq.pop_back();
                --len;
            } else
                continue;
        }
        dq.push_back(H[i]);
        ++len;
    }

    while (len > 2 && dq[0].out(dq[len - 1].inter(dq[len - 2]))) {
        dq.pop_back();
        --len;
    }

    while (len > 2 && dq[len - 1].out(dq[0].inter( dq[1]))) {
        dq.pop_front();
        --len;
    }

    if (len < 3)return vector<P>();

    vector<P> vec(len);
    for (int i = 0; i + 1 < len; i++)
        vec[i] = dq[i].inter(dq[i + 1]);

    vec[len - 1] = dq[len - 1].inter(dq[0]);
    return vec;
}