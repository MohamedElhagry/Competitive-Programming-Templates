
ll fact[N];

void preprocess()
{
    fact[0] = 1;
    for(ll i=1; i<N; i++)
        fact[i] = i * fact[i-1] % mod;
}

ll fastExp(ll x, ll n)
{
    if(n == 0)
        return 1;
    ll u = fastExp(x, n/2);
    u = u * u % mod;
    if(n & 1)
        u = u * x % mod;
    return u;
}

ll modInv(ll x)
{
    return fastExp(x, mod-2) % mod;
}

ll nCr(int n, int r)
{
    if(n < r)
        return 0;
    return (fact[n] * modInv(fact[r]) % mod) * modInv(fact[n-r]) % mod;
}
