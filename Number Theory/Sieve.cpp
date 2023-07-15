const int N = 1e6 + 5;
int SPF[N];
void sieve()
{
    for(int x=1; x<N; x++)
        SPF[x] = x;
 
    for(ll x=2; x< N; x++)
    {
        if(SPF[x] != x)
            continue;
        for(ll i = x*x; i<N; i+=x)
        {
            if(SPF[i] != i)
                continue;
            SPF[i] = (int)x;
        }
    }
}
 
map<int,int> factorize(int x)
{
    map<int,int> facts;
    while(x > 1)
    {
        int p = SPF[x];
        facts[p]++;
        x /= p;
    }
    return facts;
}