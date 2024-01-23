#include <bits/stdc++.h>

#define pb push_back
#define F first
#define S second
#define MP make_pair
#define all(x) x.begin(),x.end()
#define Hagry ios::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vb = vector<bool>;
using vll = vector<ll>;
using vpi = vector<pair<int, int>>;
using vvi = vector<vector<int>>;

// assuming nodes are zero based
struct SCC {
    vvi adj, adjRev, comps;
    vpi edges;
    vi revOut, compOf;
    vb vis;
    int N;

    void init(int n) {
        N = n;
        adj.resize(n);
        adjRev.resize(n);
        vis.resize(n);
        compOf.resize(n);
    }

    void addEdge(int u, int v) {
        edges.pb(make_pair(u, v));
        adj[u].pb(v);
        adjRev[v].pb(u);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (auto v:adj[u])
            if (!vis[v])
                dfs1(v);
        revOut.pb(u);
    }

    void dfs2(int u) {
        vis[u] = true;
        comps.back().pb(u);
        compOf[u] = comps.size() - 1;
        for (auto v:adjRev[u])
            if (!vis[v])dfs2(v);
    }

    void gen() {
        fill(all(vis), false);
        for (int i = 0; i < N; ++i) {
            if (!vis[i])
                dfs1(i);
        }
        reverse(all(revOut));
        fill(all(vis), false);
        for (auto node:revOut) {
            if (vis[node])continue;
            comps.pb(vi());
            dfs2(node);
        }
    }

    vvi generateCondensedGraph() {
        vvi adjCon(comps.size());
        for (auto edge:edges)
            if (compOf[edge.F] != compOf[edge.S])
                adjCon[compOf[edge.F]].pb(compOf[edge.S]);
        return adjCon;
    }
};

// usage: for negating varaibles pass ~x
// -1-2*x transforms ~x into 2*x + 1
struct TwoSat {
    int N;
    vpi edges;
 
    void init(int _N) {
        N = _N;
    }
 
    int addVar() { return N++; }
 
    // x or y, edges will be refined in the end
    void either(int x, int y) {
        x = max(2 * x, -1 - 2 * x);
        y = max(2 * y, -1 - 2 * y);
        edges.pb({x, y});
    }
 
    void implies(int x, int y) {
        either(~x, y);
    }
 
    void must(int x) {
        either(x, x);
    }
 
    void XOR(int x, int y) {
        either(x, y);
        either(~x, ~y);
    }
 
    // void atMostOne exists in kactl
    vb solve(int _N = -1) {
        if (_N != -1) N = _N;
        SCC scc;
        scc.init(2 * N);
        for (auto e:edges) {
            scc.addEdge(e.F ^ 1, e.S);
            scc.addEdge(e.S ^ 1, e.F);
        }
        scc.gen();
        for (int i = 0; i < 2 * N; ++i) {
            if (scc.compOf[i] == scc.compOf[i ^ 1])return {};
        }
        vvi &comps = scc.comps;
        vi &compOf = scc.compOf;
        vi tmp(comps.size());
        for (int i = comps.size()-1; ~i; --i) {
            if (!tmp[i]) {
                tmp[i] = 1;
                for (auto e:comps[i])
                    tmp[compOf[e ^ 1]] = -1;
            }
        }
        vb ans(N);
        for (int i = 0; i < N; ++i)
            ans[i] = tmp[compOf[2 * i]] == 1;
        return ans;
    }
};