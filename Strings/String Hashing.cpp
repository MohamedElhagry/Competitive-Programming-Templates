const int N = 1e6 + 5;
const int p1 = 31, p2 = 53, M1 = 1e9 + 7;

pair<ll, ll> h[N], pw[N];
void pre(string& s)
{
    h[0].F = h[0].S = s[0]-'a'+1;
    int n = (int)s.size();
    for(int i=1; i<n; i++){
        h[i].F = (h[i-1].F * p1 % M1 + (s[i]-'a'+1)) % M1;
        h[i].S = (h[i-1].S * p2 % M1 + (s[i]-'a'+1)) % M1;
    }

    pw[0].F  = pw[0].S = 1;
    for(int i=1; i<=n; i++)
    {
        pw[i].F = pw[i-1].F*p1 % M1;
        pw[i].S = pw[i-1].S*p2 % M1;
    }
}

//0<=i<=j<n
pair<ll,ll> getRangeHash(int i, int j)
{
    if(i == 0)
        return h[j];
    ll h1 = (h[j].F - (h[i-1].F * pw[j-i+1].F % M1) + M1) % M1;
    ll h2 = (h[j].S - (h[i-1].S * pw[j-i+1].S % M1) + M1) % M1;

    return {h1, h2};
}
