// Centroid Decomposition
const int N = 2e5+1;
int sz[N], n, k, freq[N];
vi adj[N];
bool rem[N];

void preSize(int i, int par)
{
    sz[i] = 1;
    for(auto e:adj[i])
    {
        if(e == par || rem[e])continue;
        preSize(e, i);
        sz[i] += sz[e];
    }
}
int getCen(int u, int par, int subSz)
{
    int mxSz = subSz - sz[u];
    int ret = -1;
    for(auto e:adj[u])
    {
        if(e.F == par || rem[e.F])
            continue;

        ret = max(ret, getCen(e.F, u, subSz));
        mxSz = max(mxSz, sz[e.F]);
    }
    if(mxSz <= subSz / 2)
        ret = u;
    return ret;
}

ll solve(int u, int par, int d)
{
    ll ans = (k >= d ? freq[k-d]:0);
    for(auto e:adj[u])
    {
        if(e == par || rem[e])continue;
        ans += solve(e, u, d+1);
    }
    return ans;
}

void update(int u, int par, int d, int inc)
{
    freq[d] += inc;
    for(auto e:adj[u])
    {
        if(e == par || rem[e])continue;
        update(e, u, d+1, inc);
    }
}

ll getAns(int u)
{
    ll ans = 0;
    for(auto e:adj[u])
    {
        if(rem[e])continue;
        ans += solve(e, u, 1);
        update(e, u, 1, 1);
    }
    return ans;
}

// get centroid and root on it and decompose for children
ll decompose(int u)
{
    preSize(u, 0);
    int cen = getCen(u, 0, sz[u]);
    freq[0] += 1;
    ll ans = getAns(cen);
    update(cen, 0, 0, -1);
    rem[cen] = true;
    for(auto e:adj[cen])
    {
        if(!rem[e])
            ans += decompose(e);
    }
    return ans;
}