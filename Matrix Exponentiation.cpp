int mod;
vvi idn;

vvi mul(vvi &v1, vvi &v2) {
    int n = v1.size(), m = v2[0].size();
    vvi prod = vvi(n, vector<ll>(m));

    int iters = v1[0].size();

    FOR(i, 0, n) {
        FOR(j, 0, m) {
            FOR(k, 0, iters) {
                prod[i][j] += v1[i][k] * v2[k][j] % mod;
                prod[i][j] %= mod;
            }
        }
    }

    return prod;
}

vvi fastPowMats(vvi a, int n) {
    if (n == 0)
        return idn;

    vvi rest = fastPowMats(a, n / 2);
    rest = mul(rest, rest);
    if (n & 1)
        rest = mul(rest, a);

    return rest;
}

