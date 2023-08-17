vector <vector<ll>> IDN;

vector <vector<ll>> mul(vector <vector<ll>> &v1, vector <vector<ll>> &v2) {
    int n = v1.size(), m = v2[0].size();
    vector <vector<ll>> prod(n, vector<ll>(m));
    int iters = v1[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < iters; ++k) {
                (prod[i][j] += v1[i][k] * v2[k][j] % MOD) %= MOD;
            }
        }
    }
    return prod;
}

vector <vector<ll>> fastPowMats(vector <vector<ll>> &a, int n) {
    if (n == 0) 
        return IDN;
    vector <vector<ll>> res = fastPowMats(a, n / 2);
    res = mul(res, res);
    if (n & 1) 
        res = mul(res, a);
    return res;
}