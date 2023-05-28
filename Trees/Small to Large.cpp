int col[N], sz[N], colFreq[N], bigChild[N];
vi adj[N];
ll ans[N];
map<int,ll> freqSum;
vi* cols[N];

void upd(int x, bool add)
{
    ll& ref = freqSum[colFreq[x]];
    ref -= x;
    if(ref == 0)
        freqSum.erase(colFreq[x]);

    if(add)
        ++colFreq[x];
    else
        --colFreq[x];

    freqSum[colFreq[x]] += x;
}

void preSize(int u, int par)
{
    sz[u] = 1;int mx = 0;
    for(auto e:adj[u])
    {
        if(e == par)continue;
        preSize(e, u);
        sz[u] += sz[e];
        if(sz[e] > mx){
            mx = sz[e]; bigChild[u] = e;
        }
    }
}

void solve(int i, int par, bool keep)
{

    for(auto e:adj[i])
    {
        if(e == par || e == bigChild[i])continue;
            solve(e, i, false);
    }
    if(bigChild[i]) solve(bigChild[i], i, true);


    if(bigChild[i])
        cols[i] = cols[bigChild[i]];
    else
        cols[i] = new vi();
    cols[i]->pb(col[i]);
    upd(col[i], true);

    for(auto e:adj[i])
    {
        if(e == par || e == bigChild[i])continue;
        for(auto e2:*cols[e])
        {
            cols[i]->pb(e2);
            upd(e2, true);
        }
    }

    ans[i] = freqSum.rbegin()->second;
    if(keep)return;
    for(auto e:*cols[i])
        upd(e, false);
}
