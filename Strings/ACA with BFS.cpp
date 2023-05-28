const int K = 26;

struct ACA {
    struct Node {
        int nxt[K];
        //list of patterns ending here
        vi pats;
        //suff link
        int link;
        //memoize which state to go to when given char c from this state
        int go[K];

        Node() {
            fill(nxt, nxt + K, -1);
            fill(go, go + K, -1);
            link = -1;
            pats = vi();
        }
    };

    vector<Node> aut;

    ACA(vector<string> &pats) {
        aut.resize(1);
        int id = 0;
        for (auto &e:pats)
            add_string(e, id++);
        build();
    }

    void add_string(string &s, int id) {
        int u = 0; //cur node
        for (auto ch:s) {
            int c = ch - 'a';
            if (aut[u].nxt[c] == -1) {
                aut[u].nxt[c] = (int) aut.size();
                aut.emplace_back();
            }
            aut[u].go[c] = aut[u].nxt[c];
            u = aut[u].nxt[c];
        }
        aut[u].pats.pb(id);
    }

    void build() {
        queue<int> q;
        int cur = 0;
        aut[cur].link = 0;
        for (int i = 0; i < K; i++) {
            int nxt = aut[cur].nxt[i];
            if (~nxt) {
                q.push(nxt);
                aut[nxt].link = cur;
            } else
                aut[cur].go[i] = 0;
        }

        while (!q.empty()) {
            cur = q.front();q.pop();
            int link = aut[cur].link;
            for (int i = 0; i < K; i++) {
                if (!~aut[cur].go[i]){
                    aut[cur].go[i] = aut[link].go[i];
                }
                else {
                    int next = aut[cur].go[i];
                    int nextLink = aut[link].go[i];
                    aut[next].link = nextLink;
                    aut[next].pats.insert(aut[next].pats.end(), aut[nextLink].pats.begin(), aut[nextLink].pats.end());
                    q.push(aut[cur].go[i]);
                }
            }
        }
    }
};