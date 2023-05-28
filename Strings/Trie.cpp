const int K = 26;

struct Trie {
    struct Node {
        int go[K];
        int freq;

        Node() {
            fill(go, go + K, -1);
            freq = 0;
        }
    };

    vector<Node> aut;

    Trie(vector<string> &pats) {
        aut.resize(1);
        for (auto &e:pats)
            add_string(e);
    }

    void add_string(string &s) {
        int u = 0; //cur node
        for (auto ch:s) {
            int c = ch - 'a';
            if (aut[u].go[c] == -1) {
                aut[u].go[c] = (int) aut.size();
                aut.emplace_back();
            }
            u = aut[u].go[c];
            aut[u].freq++;
        }
    }
};
