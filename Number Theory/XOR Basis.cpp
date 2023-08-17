const int LG = 60 + 1;
//basis[i] contains a basis whose highest bit is i
ll basis[LG];

void insert(ll x) {
    for (int b = LG - 1; b >= 0; --b) {
        //dimension is 0
        if (((1ll << b) & x) == 0)
            continue;

        //basis is not occupied, just put it here
        if (basis[b] == 0) {
            basis[b] = x;
            return;
        }

        //subtract this basis from x
        x ^= basis[b];
    }
}