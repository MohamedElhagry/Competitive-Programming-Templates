 
set<int> adj[N];
 
void eulerPath(int start, vi &ans) {
    stack<int> st;
    st.push(start);
 
    while (!st.empty()) {
        int u = st.top();
        if (adj[u].empty()) {
            ans.push_back(u);
            st.pop();
            continue;
        } else {
            int v = *adj[u].begin();
            st.push(v);
            adj[u].erase(v);
            adj[v].erase(u);
        }
    }
}