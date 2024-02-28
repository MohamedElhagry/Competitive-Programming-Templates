ll nCr(int n, int r) {
    if (r > n)
        return 0;
 
    ll &ret = dp[n][r];
    if (~ret)
        return ret;
    if (r == 0)return ret = 1;
    if (r == 1)return ret = n;
    if (n == 1)return ret = 1;
    return ret = nCr(n - 1, r - 1) + nCr(n - 1, r);
}