int sparse[N][LG];

void build() {
    for (int i = 0; i < n; i++)
        sparse[i][0] = a[i];
    for (int k = 1; k < LG; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            sparse[i][k] = min(sparse[i][k - 1], sparse[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int query(int l, int r) {
    int length = r - l + 1;
    int k = 31 - __builtin_clz(length); //gets the largest power of two that is smaller than or equal to the number 
    return min(sparse[l][k], sparse[r - (1 << k) + 1][k]);
} 