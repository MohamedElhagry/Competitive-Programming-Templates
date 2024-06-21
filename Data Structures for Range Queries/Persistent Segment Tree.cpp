struct Vertex {
Vertex *l, *r;
int sum = 0;
Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
Vertex() : l(nullptr), r(nullptr) {}
Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
if (l) sum += l->sum;
if (r) sum += r->sum;
}
void addChild(){
l = new Vertex();
r = new Vertex();
}
};
struct Seg {
int n;
Seg(int n) {
this->n = n;
15
Vertex merge(Vertex x, Vertex y) {Vertex merge(Vertex x, Vertex y) {
Vertex ret;
ret.sum = x.sum + y.sum;
return ret;
}
Vertex *update(Vertex *v, int i, int lx, int rx) {
if (lx == rx)
return new Vertex(v->sum + 1);
int mid = (lx + rx) / 2;
if(!v->l)v->addChild();
if (i <= mid) {
return new Vertex(update(v->l, i, lx, mid), v->r);
} else {
return new Vertex(v->l, update(v->r, i, mid + 1, rx));
}
}
Vertex *update(Vertex *v, int i) {
return update(v, i, 0, n - 1);
}
Vertex query(Vertex *v, int l, int r, int lx, int rx) {
if (l > rx || r < lx)
return {};
if (l <= lx && r >= rx)
return *v;
if(!v->l)v->addChild();
int mid = (lx + rx) / 2;
return merge(query(v->l, l, r, lx, mid), query(v->r, l, r, mid + 1, rx));
}
Vertex query(Vertex *v, int l, int r) {
return query(v, l, r, 0, n - 1);
}
int getKth(Vertex *a, Vertex *b, int k, int lx, int rx) {
if (lx == rx) {
return lx;
}
if(!a->l)a->addChild();
if(!b->l)b->addChild();
int rem = b->l->sum - a->l->sum;
int mid = (lx + rx) / 2;
if (rem >= k)
return getKth(a->l, b->l, k, lx, mid);
else
return getKth(a->r, b->r, k - rem, mid + 1, rx);
}
int getKth(Vertex *a, Vertex *b, int k) {
return getKth(a, b, k, 0, n - 1);
}
}