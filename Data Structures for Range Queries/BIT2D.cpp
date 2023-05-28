struct BIT2D
{
    vector<vector<ll>> tree;

    BIT2D(int _n = N){
        tree.resize(_n+2, vector<ll>(_n+2));
    }
    ll get(int i, int j)
    {
        ++i; ++j;
        ll sum = 0;
        for(int x=i; x >= 1; x -= x&-x){
            for(int y=j; y>=1; y -= y&-y){
                sum += tree[x][y];
            }
        }
        return sum;
    }
    void update(int i, int j, ll v)
    {
        ++i; ++j;
        for(int x=i; x < tree.size(); x += x&-x){
            for(int y=j; y < tree.size(); y += y&-y){
                tree[x][y] += v;
            }
        }
    }
    ll query(int x1, int y1, int x2, int y2)
    {
        return get(x2,y2) - get(x1-1, y2) - get(x2, y1-1) + get(x1-1, y1-1);
    }

};