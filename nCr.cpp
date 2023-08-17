const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
ll fact[N], modInv[N];

ll fastExp(ll x, ll n)
{
    if(n == 0)
        return 1;
    ll u = fastExp(x, n/2);
    u = u * u % MOD;
    if(n & 1)
        u = u * x % MOD;
    return u;
}

// modInv[i] = fact[i]^-1 % MOD
void preprocess()
{
    fact[0] = 1;
    for(ll i =1; i<N; i++)
        fact[i] = fact[i-1] * i % MOD;

    modInv[N-1] = fastExp(fact[N-1], MOD - 2) % MOD;
    for(ll i=N-2; i>=0;i--)
        modInv[i] = (i+1) * modInv[i+1] % MOD;
}

ll modInvF(ll x)
{
    return fastExp(x, MOD - 2);
}

ll nCr(int n, int r)
{
    if(r > n)
        return 0;

    // return ( n! / ((n-r)! * r!) ) % MOD
    return (fact[n] * modInv[n-r] % MOD) * modInv[r] % MOD;
}