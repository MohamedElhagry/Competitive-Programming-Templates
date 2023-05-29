
ll fact[N], modInv[N];

ll fastExp(ll x, ll n)
{
    if(n == 0)
        return 1;
    ll u = fastExp(x, n/2);
    u = u*u % mod;
    if(n & 1)
        u = u * x % mod;
    return u;
}

// modInv[i] = fact[i]^-1 % mod
void preprocess()
{
    fact[0] = 1;
    for(ll i =1; i<N; i++)
        fact[i] = fact[i-1] * i % mod;

    modInv[N-1] = fastExp(fact[N-1], mod-2) % mod;
    for(ll i=N-2; i>=0;i--)
        modInv[i] = (i+1) * modInv[i+1] % mod;
}

ll modInvF(ll x)
{
    return fastExp(x, mod-2);
}

ll nCr(int n, int r)
{
    if(r > n)
        return 0;

    // return ( n! / ((n-r)! * r!) ) % mod
    return (fact[n] * modInv[n-r] % mod) * modInv[r] % mod;
}
