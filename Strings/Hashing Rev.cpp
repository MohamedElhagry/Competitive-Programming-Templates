const int p1 = 31, p2 = 37, MOD = 1e9 + 7;

const int N = 1e6 + 5;
int pw1[N], inv1[N], pw2[N], inv2[N];

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

void pre() {
    pw1[0] = inv1[0] = 1;
    pw2[0] = inv2[0] = 1;
    int invV1 = inv(p1);
    int invV2 = inv(p2);
    for (int i = 1; i < N; ++i) {
        pw1[i] = mul(pw1[i - 1], p1);
        inv1[i] = mul(inv1[i - 1], invV1);
        pw2[i] = mul(pw2[i - 1], p2);
        inv2[i] = mul(inv2[i - 1], invV2);
    }
}

struct Hash {
    vector<pi> h;
    int n;

    Hash(string &s) {
        n = s.size();
        h.resize(n);
        h[0].F = h[0].S = s[0] - 'a' + 1;
        for (int i = 1; i < n; ++i) {
            h[i].F = add(h[i-1].F,mul((s[i] - 'a' + 1), pw1[i]));
            h[i].S = add(h[i-1].S,mul((s[i] - 'a' + 1), pw2[i]));
        }
    }

    pi getRange(int l, int r) {
        assert(l <= r);
        assert(r < n);
        return {
                mul(sub(h[r].F, l ? h[l - 1].F : 0), inv1[l]),
                mul(sub(h[r].S,  l ? h[l - 1].S : 0), inv2[l])
        };
    }
};