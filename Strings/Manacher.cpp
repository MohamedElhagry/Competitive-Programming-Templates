vi manacher_odd(string& s) {
    int n = s.size();

    string t = '^' + s  + '$';
    vi p(n+2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; ++i) {
        int &len = p[i];
        int j = l + r-i;
        len = max(0, min(r - i, p[j]));

        while (t[i + len] == t[i - len])
            ++len;

        if(i + len > r){
            r = i + len;
            l = i - len;
        }
    }

    return vi(p.begin() + 1, p.begin() + n + 1);
}

vector<pi> manacher(string& s){
    int n = (int)s.size();
    string t;
    for(int i=0; i<n; ++ i){
        t.pb('#');
        t.pb(s[i]);
    }
    t.pb('#');

    vi p = manacher_odd(t);
    vector<pi> ret(n);
    //odd then even
    for(int i=0; i<n; ++i){
        ret[i].F = (p[2*i+1])/2;
        ret[i].S = (p[2*i]-1)/2;
    }
    return ret;
}
