//LCA
#include <bits/stdc++.h>

 
#define _ ios::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
using namespace std;
const int OO = 1e9;
 
const int N = 2e5 + 5;
const int LG = 20;
 
int anc[N][20], p[N], d[N], n, q;
vi adj[N];
 
void dfs(int i, int par)
{
    p[i] = par;
    d[i] = d[par]+1;
    for(auto e:adj[i])
    {
        if(e == par)
            continue;
        dfs(e, i);
    }
}
 
//need par, depth
void preprocess()
{
    // k is 2^k anc
    for(int k=0;k<LG; k++)
    {
        for(int i=1; i<=n; i++)
        {
            if(k == 0)
                anc[i][k] = p[i];
            else
                anc[i][k] = anc[anc[i][k-1]][k-1];
        }
    }
}
 
int binaryLift(int x, int jump)
{
    for(int b=0; b<LG; b++)
    {
        if(jump & (1 << b))
            x = anc[x][b];
    }
    return x;
}
 
int LCA(int a, int b)
{
    if(d[a] > d[b])
        swap(a, b);
 
    // guaranteed that b is deeper
    //make same depth
    int diff = d[b] - d[a];
    b = binaryLift(b, diff);
 
    if(a == b)
        return a;
 
    for(int bit=LG-1; bit>=0; bit--)
    {
        if(anc[a][bit]==anc[b][bit])
            continue;
        a = anc[a][bit];
        b = anc[b][bit];
    }
 
    return p[a];
}