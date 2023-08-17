ll powmod(ll x, ll y) {
    x %= MOD;
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return ans;
}

ll add(ll a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

ll sub(ll a, ll b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

ll mul(ll a, ll b) { return a * b % MOD; }

ll inv(ll a) { return powmod(a, MOD - 2); }