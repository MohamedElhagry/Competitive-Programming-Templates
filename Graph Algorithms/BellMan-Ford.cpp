const ll OO = 1e15;
int n;
struct Edge{
    int a, b, w;
    Edge(int a, int b, int w):a(a), b(b),w(w){}
};
//st and par and BFS are optional, just for finding negative cycles
ll BellManFord(vector<Edge>& edges, int src){
    vector<ll> d(n+1, OO);
    vi p(n+1, -1);
    d[src] = 0;

    bool change = true;
    //starts finds all negative cycles
    vi st;
    for(int itr = 1; itr<=n && change; ++itr){
        change = false;
        for(auto e:edges){
            if(d[e.a] != OO && d[e.a] + e.w < d[e.b]){
                change = true;
                d[e.b] = max(-OO, d[e.a] + e.w);
                p[e.b] = e.a;
                if(itr == n)
                    st.pb(e.b);
            }
        }
    }

    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    // to find the cycle for any node in st, just store the path of parents and
    // traverse it until you meet e again, however I only want to find if a negative cycle reaches
    // node n
    for(auto& e:st){
        for(int itr=0;itr<n; ++itr)
            e = p[e];
    }

    //BFS to find if a negative cycle reaches node n
    bool vis = BFS(st, n);
    if(vis)return -OO;

    return d[n];
}