void KMP(string &s, vi &fail) {
    n = (int) s.size();
    for (int i = 1; i < n; i++) {
        int j = fail[i - 1];
        while (j > 0 && s[j] != s[i])
            j = fail[j - 1];
        if (s[j] == s[i])
            ++j;
        fail[i] = j;
    }
}

void constructAut(string &s, vi &fail) {
    // for each fail function value (i is not an index)
    for (int i = 0; i < n; i++) {
        // for each each possible transition
        for (int c = 0; c < ALPHA; c++) {
            if (i > 0 && s[i] != 'a' + c)
                aut[i][c] = aut[fail[i - 1]][c];
            else
                aut[i][c] = i + (s[i] == 'a' + c);
        }
    }
}