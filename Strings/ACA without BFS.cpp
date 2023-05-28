const int K = 26;

struct ACA {
    struct Node {
        int nxt[K];
        //id of pattern
        int wordId;
        vi patsEndingHere;
        int p;
        char prevC;
        //suff link
        int link;
        //memoize which state to go to when given char c from this state
        int go[K];

        Node(int p = -1, char ch = '$') : p(p), prevC(ch) {
            fill(nxt, nxt + K, -1);
            fill(go, go + K, -1);
            wordId = -1;
            link = -1;
            patsEndingHere = vi();
        }
    };

    vector<Node> aut;

    ACA() {
        aut.resize(1);
    }

    void add_string(string &s, int id) {
        int u = 0; //cur node
        for (auto ch:s) {
            int c = ch - 'a';
            if (aut[u].nxt[c] == -1) {
                aut[u].nxt[c] = (int) aut.size();
                aut.emplace_back(u, ch);
            }
            u = aut[u].nxt[c];
        }
        aut[u].wordId = id;
    }

    //get suff_link memoized
    int get_link(int node) {
        if (aut[node].link == -1) {
            if (node == 0 || aut[node].p == 0)
                aut[node].link = 0;
            else
                aut[node].link = go(get_link(aut[node].p), aut[node].prevC);
        }
        return aut[node].link;
    }

    //traverse this u with this char
    int go(int u, char ch) {
        int c = ch - 'a';
        if (aut[u].go[c] == -1) {
            if (aut[u].nxt[c] != -1)
                aut[u].go[c] = aut[u].nxt[c];
            else
                aut[u].go[c] = u == 0 ? 0 : go(get_link(u), ch);
        }
        return aut[u].go[c];
    }

    void build(vector<string> &pats) {
        int id = 0;
        for (auto &e:pats)
            add_string(e, id++);

        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int p = q.front();
            q.pop();

            if (~aut[p].wordId)
                aut[p].patsEndingHere.pb(aut[p].wordId);
            int link = get_link(p);
            if (link != p)
                for (auto e:aut[link].patsEndingHere)
                    aut[p].patsEndingHere.pb(e);
            for (int i = 0; i < K; i++) {
                if (~aut[p].nxt[i])
                    q.push(aut[p].nxt[i]);
            }
        }
    }
};