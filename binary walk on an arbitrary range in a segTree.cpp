//query leftmost element not less than v
int binWalk(int ql, int qr, int v, int k = 1, int sl = 0, int sr = n - 1) {
        propagate(k, sl, sr);
        if (qr < sl || sr < ql)
            return -1;
        int mid = (sl + sr) / 2;
        if (ql <= sl && qr >= sr) {
            if (sl == sr)
                return tree[k] >= v ? sl : -1;

            propagate(k << 1, sl, mid);
            propagate(k << 1 | 1, mid + 1, sr);
            if (tree[k << 1] >= v)
                return binWalk(ql, qr, v, k << 1, sl, mid);
            if (tree[k << 1 | 1] >= v)
                return binWalk(ql, qr, v, k << 1 | 1, mid + 1, sr);
            return -1;
        }

        int left = binWalk(ql, qr, v, k << 1, sl, mid);
        if (left != -1)
            return left;
        int right = binWalk(ql, qr, v, k << 1 | 1, mid + 1, sr);
        if (right != -1)
            return right;
        return -1;
    }