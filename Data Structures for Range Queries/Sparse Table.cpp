const int N = 1e5 + 5;
const int K = 19;
int a[N], mn[K][N], bigPow[N], n;

void con() {
    for (int k = 0; k < K; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            if (k == 0)
                mn[k][i] = a[i];
            else
                mn[k][i] = min(mn[k - 1][i], mn[k - 1][i + (1 << (k - 1))]);
        }
    }

    for(int i=2; i<=n; i++)
        bigPow[i] = bigPow[i/2]+1;
}

int query(int l, int r) {
    int len = r - l + 1;
    int k = bigPow[len];

    return min(mn[k][l], mn[k][r - (1 << k) + 1]);
}
