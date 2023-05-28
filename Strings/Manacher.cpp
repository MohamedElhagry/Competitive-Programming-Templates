vi odd_manacher(string &s) {
    string t = '$' + s + '#';
    int n = s.size(), l = 1, r = 1;
    vi d(n + 2);
    for (int i = 1; i <= n; i++) {
        int &len = d[i];
        int j = l + r - i;
        len = max(0, min(r - i, d[j]));
        while (t[i - len] == t[i + len])
            ++len;

        if (i + len > r) {
            l = i - len;
            r = i + len;
        }
    }
    return vi(d.begin() + 1, d.begin() + n + 1);
}

pair<vi, vi > manacher(string &s) {
    string t;
    int n = (int) s.size();
    for (auto e:s) {
        t.pb('#');
        t.pb(e);
    }
    t += "#";
    vi res = odd_manacher(t);
    vi dOdd(n), dEven(n);
    
    //dEven[i] = len of longest even pal. centered around i (i is the right middle character)
    for (int i = 0; i < n; i++) {
        dOdd[i] = res[2 * i + 1] / 2;
        dEven[i] = (res[2 * i] - 1) / 2;
    }
    return {dOdd, dEven};
}