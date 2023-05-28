struct item{
    int key, prio, cnt;
    item *l, *r;
    item(){}
    item(int key) :key(key), prio(rand()), l(nullptr), r(nullptr), cnt(1){ }
};
typedef item* pnode;

struct Treap{
    item* root;

    int cnt (pnode t) {
        return t ? t->cnt : 0;
    }

    void upd_cnt (pnode t) {
        if (t)
            t->cnt = 1 + cnt(t->l) + cnt (t->r);
    }

    void split (pnode t, int key, pnode & l, pnode & r) {
        if (t == nullptr)
            l = r = nullptr;
        else if (t->key <= key)
        {
            split (t->r, key, t->r, r);  l = t;
        }
        else{
            split (t->l, key, l, t->l);  r = t;
        }

        upd_cnt(t);
    }

    void merge (pnode & t, pnode l, pnode r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prio > r->prio)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;

        upd_cnt(t);
    }

    void insert (pnode & t, pnode it) {
        if (!t)
            t = it;
        else if (it->prio > t->prio)
            split (t, it->key, it->l, it->r),  t = it;
        else
            insert (t->key <= it->key ? t->r : t->l, it);

        upd_cnt(t);
    }

    void erase (pnode & t, int key) {
        if (t->key == key) {
            pnode th = t;
            merge (t, t->l, t->r);
            delete th;
        }
        else
            erase (key < t->key ? t->l : t->r, key);

        upd_cnt(t);
    }

    int orderOf(pnode t, int key)
    {
        pnode l, r;
        split(t,key, l,r);
        int ans = l->cnt;
        merge(t,l,r);
        return ans;
    }

    int orderOf(int key)
    {
        return orderOf(root, key);
    }

    void erase(int num)
    {
        erase(root, num);
    }

    void insert (int num)
    {
        insert( root, new item(num));
    }
};

const int N = 4e5 + 5;
Treap inds[N];
