const ll OO = 1e15;
const int N = 2500 + 5;
vector<pair<int,ll>> adj[N];
//st and par are optional, just for finding negative cycles
vi st;
int n;
bool SPFA(int src, vector<ll>& d){
    fill(d.begin(), d.end(), OO);
    vi cnt(n+1), par(n+1, -1);
    vector<bool> inQ(n+1, false);
    queue<int> q;

    d[src] = 0;
    q.push(src);
    inQ[src] = true;
    while(!q.empty()){
        int p = q.front(); q.pop();
        inQ[p] = false;

        for(auto e:adj[p]){
            int to = e.F;ll w = e.S;
            if(d[p] + w < d[to]){
                d[to] = max(-OO, d[p] + w);
                par[to] = p;
                if(!inQ[to]){
                    inQ[to] = true;
                    if(++cnt[to] > n)
                        st.pb(to);
                    else
                        q.push(to);
                }
            }
        }
    }

    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    for(auto &e:st)for(int i=0; i<n; i++)e = par[e];

    return st.empty();
}