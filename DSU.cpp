#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    DSU () {
        __init__(0);
    }
    DSU (int v) {
        __init__(v);
    }

    int findSet (int v) {
        if (v == parent[v])
            return v;
        return parent[v] = findSet(parent[v]);
    }

    bool isSame (int u, int v) {
        return findSet(u) == findSet(v);
    }

    void unionSet (int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u != v) {
            if (rnk[u] < rnk[v]) {
                swap(u, v);
            }
            parent[v] = u;
            if (rnk[u] == rnk[v]) {
                rnk[u]++;
            }
        }
    }

    void resize (int v) {
        __init__(v);
    }

private:
    vector<int> parent;
    vector<int> rnk;
    void __init__ (int v) {
        parent.assign(v, 0);
        rnk.assign(v, 0);
        for (int i=1; i<v; i++) {
            parent[i] = i;
        }
    }
};

vector<int> parent;
vector<int> rnk;

void make_set(int v){
    parent[v] = v;
    rnk[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rnk[a] < rnk[b])
            swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b])
            rnk[a]++;
    }
}