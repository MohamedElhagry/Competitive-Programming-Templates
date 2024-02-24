const ll OO = 1e18 + 5;
const ll maxN = 1e6 + 5;

struct Line {
    ll m, c;

    Line() : m(0), c(OO) {}

    Line(ll m, ll c) : m(m), c(c) {}
};

ll sub(ll x, Line l) {
    return x * l.m + l.c;
}

// Li Chao sparse
struct node {
    // range I am responsible for
    Line line;
    node *left, *right;

    node() {
        left = right = NULL;
    }

    node(ll m, ll c) {
        line = Line(m, c);
        left = right = NULL;
    }

    void extend(int l, int r) {
        if (left == NULL && l != r) {
            left = new node();
            right = new node();
        }
    }

    void add(Line toAdd, int l, int r) {
        assert(l <= r);
        int mid = (l + r) / 2;
        if (l == r) {
            if (sub(l, toAdd) < sub(l, line))
                swap(toAdd, line);
            return;
        }
        bool lef = sub(l, toAdd) < sub(l, line);
        bool midE = sub(mid+1, toAdd) < sub(mid+1, line);
        if(midE)
            swap(line, toAdd);
        extend(l, r);
        if(lef != midE)
            left->add(toAdd, l, mid);
        else
            right->add(toAdd, mid+1, r);
    }

    void add(Line toAdd) {
        add(toAdd, 0, maxN-1);
    }

    ll query(ll x, int l, int r) {
        int mid = (l + r) / 2;
        if (l == r || left == NULL)
            return sub(x, line);
        extend(l, r);
        if (x <= mid)
            return min(sub(x, line), left->query(x, l, mid));
        else
            return min(sub(x, line), right->query(x, mid+1, r));
    }

    ll query(ll x) {
        return query(x, 0, maxN-1);
    }

    void clear() {
        if (left != NULL) {
            left->clear();
            right->clear();
        }
        delete this;
    }
};