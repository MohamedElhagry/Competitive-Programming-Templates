using vd = valarray<complex<double>>;
using cd = complex<double>;

const double PI = acos(-1);

int reverse(int x, int lg){
    int res = 0;
    for(int i=0; i<lg; ++i){
        if(x & (1 << i))
            res |= 1 << (lg-1-i);
    }
    return res;
}

vd FFT(vd& a, bool inv = false) {
    int m = a.size();
    int lg = 0;
    while((1 << lg) < m)
        ++lg;

    for(int i=0; i<m; ++i){
        if(i < reverse(i, lg))
            swap(a[i], a[reverse(i, lg)]);
    }

    for(int len = 2; len <= m; len <<= 1){
        cd omg = exp(complex<double>(0, 2*PI/len * (inv ? -1:1)));
        for(int i=0; i<m; i += len){
            cd curOmg = 1;
            for(int j=0; j<len/2; ++j){
                cd e = a[i + j], o = a[i + j + len/2] * curOmg;
                a[i + j] = e + o;
                a[i + j + len/2] = e - o;
                curOmg *= omg;
            }
        }
    }
    return a;
}

vd IFFT(vd& a) {
    vd ret = FFT(a, true);
    double m = a.size();
    ret /= m;
    return ret;
}

vector<ll> mul(vector<ll> const &a, vector<ll> const &b) {
    int m = 1;
    while (m < a.size() + b.size())
        m <<= 1;
    vd A(m), B(m);
    for (int i = 0; i < m; ++i) {
        if (i < a.size()) A[i] = a[i];
        if (i < b.size()) B[i] = b[i];
    }

    A = FFT(A);
    B = FFT(B);
    vd C = A * B;
    C = IFFT(C);

    vector<ll> ret(m);
    for (int i = 0; i < m; ++i)
        ret[i] = round(C[i].real());
    return ret;
}