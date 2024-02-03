using vd = valarray<complex<double>>;

vd FFT(const vd &a, bool inv = false) {
    int m = a.size();
    if (m == 1) {
        return vd(a[0], 1);
    }

    vd even = a[slice(0, m / 2, 2)];
    vd odd = a[slice(1, m / 2, 2)];
    even = FFT(even, inv);
    odd = FFT(odd, inv);

    vd ret(m);
    complex<double> omg = exp(complex<double>(0, 2 * M_PI / m * (inv ? -1 : 1)));
    complex<double> yMul = complex<double>(1, 0);
    for (int j = 0; j < m / 2; ++j) {
        ret[j] = even[j] + yMul * odd[j];
        ret[j + m / 2] = even[j] - yMul * odd[j];
        yMul *= omg;
    }
    return ret;
}

vd IFFT(const vd &a) {
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
