// rotating calipers for finding all antipodal pairs
template <class P>
ll rotatingCalipers(vector<P>& pts){
    ll ans = 0;
    int i = 0, j = 1, sz = pts.size();
    auto nxt = [&sz](int x){return (x+1) % sz;};
    if((int)pts.size() < 3)
        return ans;
    while((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) > 0)
        j = nxt(j);

    int j0 = j;
    while(i != j0){
        i = nxt(i);

        ;//yield

        while((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) > 0){
            j = nxt(j);
            if(MP(i, j) != MP(j0, sz - 1))
                ;//yield
            else
                return ans;
        }
        if((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) == 0){
            if(MP(i, j) != MP(j0, sz - 1))
                ;//yield
            else
                ;//yield
        }
    }
    return ans;
}

template <class P>
ll diameter(vector<P>& pts){
    ll ans = 0;
    int i = 0, j = 1, sz = pts.size();
    auto nxt = [&sz](int x){return (x+1) % sz;};
    if((int)pts.size() < 3)
        return ans;
    while((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) > 0)
        j = nxt(j);

    int j0 = j;
    while(i != j0){
        i = nxt(i);

        ans = max(ans, (pts[j] - pts[i]).norm());

        while((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) > 0){
            j = nxt(j);
            if(MP(i, j) != MP(j0, sz - 1))
                ans = max(ans, (pts[j] - pts[i]).norm());
            else
                return ans;
        }
        if((pts[nxt(i)] - pts[i]).cross(pts[nxt(j)] - pts[j]) == 0){
            if(MP(i, j) != MP(j0, sz - 1))
                ans = max(ans, (pts[nxt(j)] - pts[i]).norm());
            else
                ans = max(ans, (pts[j] - pts[nxt(i)]).norm());
        }
    }
    return ans;
}