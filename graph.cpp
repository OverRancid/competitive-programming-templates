//OverRancid#0590
#include <bits/stdc++.h>    //Parental Advisory
using namespace std;       //Explicit Content

/*
Binary Lifting
*/
static const int N = 2e5+1;
static const int l = 64-__builtin_clzll(N);
vector<vector<int>> adj(N), up(N, vector<int>(l+1, -1));

void dfs (int v = 1, int p = -1) {
    int i;
    up[v][0] = p;
    for (i=1; i<=l; i++)
        if (up[v][i-1] != -1) 
            up[v][i] = up[up[v][i-1]][i-1];

    for (int u: adj[v]) 
        if (u != p)
            dfs(u, v);
}


/*
LCA using Biary Lifting
    int n, l;
    vector<vector<int>> adj;

    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up;
*/

void dfs (int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }
    tout[v] = ++timer;
}

bool is_ancestor (int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess (int root = 1) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n+1));
    up.assign(n+1, vector<int>(l + 1));
    dfs(root, root);
}



//Cut Edge
//Offline
/*
    vector<vector<int>> adj(n+1);
    vector<bool> visited(n+1, false);
    vector<int> tin(n+1, -1), low(n+1, -1);
    int timer = 0;
*/

void dfs(int v, int p = -1){
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for(int to: adj[v]){
        if(to==p){
            continue;
        }   
        if(visited[to]){
            low[v] = min(low[v], tin[to]);
        }
        else{
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if(low[to] > tin[v]){
                is_bridge(v, to);
            }
        }
    }
}

//Single Source Shortest Path

/*
    vector<vector<int, int>> adj(n+1);
    vector<int> dist(n+1, 1e8), pi(n+1, -1);
*/

void dijkstra(int s){
    d[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({0, s});
    while(!q.empty()){
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();

        if(d_v != d[v]){
            continue;
        }

        for(pair<int, int> edge: adj[v]){
            int u = edge.first;
            int w = edge.second;

            if(d[v] + w < d[u]){
                d[u] = d[v] + w;
                pi[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

//LCA using Segment Tree
struct LCA {
    vector<int> height, euler, first, segtree;
    vector<bool> visited;
    int n;

    LCA(vector<vector<int>> &adj, int root = 0) {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        visited.assign(n, false);
        dfs(adj, root);
        int m = euler.size();
        segtree.resize(m * 4);
        build(1, 0, m - 1);
    }

    void dfs(vector<vector<int>> &adj, int node, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (auto to : adj[node]) {
            if (!visited[to]) {
                dfs(adj, to, h + 1);
                euler.push_back(node);
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) {
            segtree[node] = euler[b];
        } else {
            int mid = (b + e) / 2;
            build(node << 1, b, mid);
            build(node << 1 | 1, mid + 1, e);
            int l = segtree[node << 1], r = segtree[node << 1 | 1];
            segtree[node] = (height[l] < height[r]) ? l : r;
        }
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L)
            return -1;
        if (b >= L && e <= R)
            return segtree[node];
        int mid = (b + e) >> 1;

        int left = query(node << 1, b, mid, L, R);
        int right = query(node << 1 | 1, mid + 1, e, L, R);
        if (left == -1) return right;
        if (right == -1) return left;
        return height[left] < height[right] ? left : right;
    }

    int lca(int u, int v) {
        int left = first[u], right = first[v];
        if (left > right)
            swap(left, right);
        return query(1, 0, euler.size() - 1, left, right);
    }
};

//MST
/*
Prim's:
    vector<vector<pair<int, int>>> adj;
    adj[u].push_back({weight, v});
*/
int prim () {
    int n = adj.size()-1, i;
    int answer = 0;
    vector<pair<int, int>> min_e(n+1, make_pair(INT64_MAX, -1));
    min_e[1].first = 0;
    set<pair<int, int>> q;
    q.insert({0, 1});
    vector<bool> selected(n+1, false);

    for (i=1; i<=n; i++) {
        if (q.empty()) {
            return -1;
        }
        int v = q.begin()->second;
        selected[v] = true;
        answer += q.begin()->first;
        q.erase(q.begin());

        for (pair<int, int> e: adj[v]) {
            if (!selected[e.second] && e.first < min_e[e.second].first) {
                q.erase({min_e[e.second].first, e.second});
                min_e[e.second] = {e.first, v};
                q.insert({e.first, e.second});
            }
        }
    }

    return answer;
}

struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}