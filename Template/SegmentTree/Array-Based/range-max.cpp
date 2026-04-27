#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree;

    vector<long long> lazySet; // 赋值懒标记
    vector<bool> hasSet;       // 是否存在赋值标记

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
        lazySet.resize(4 * n);
        hasSet.resize(4 * n, false);
    }

    void build(vector<long long>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(arr, node << 1, l, mid);
        build(arr, node << 1 | 1, mid + 1, r);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }

    void applySet(int node, long long val) {
        tree[node] = val;
        lazySet[node] = val;
        hasSet[node] = true;
    }

    void pushDown(int node) {
        if (hasSet[node]) {
            applySet(node << 1, lazySet[node]);
            applySet(node << 1 | 1, lazySet[node]);
            hasSet[node] = false;
        }
    }

    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (ql <= l && r <= qr) {
            applySet(node, val);
            return;
        }

        pushDown(node);

        int mid = (l + r) >> 1;
        if (ql <= mid) update(node << 1, l, mid, ql, qr, val);
        if (qr > mid)  update(node << 1 | 1, mid + 1, r, ql, qr, val);

        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }

    long long query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        pushDown(node);

        int mid = (l + r) >> 1;
        long long res = LLONG_MIN;

        if (ql <= mid) res = max(res, query(node << 1, l, mid, ql, qr));
        if (qr > mid)  res = max(res, query(node << 1 | 1, mid + 1, r, ql, qr));

        return res;
    }
};


int main() {
    vector<long long> arr = {1, 3, 5, 7, 9, 11};
    int n = arr.size();

    SegmentTree st(n);
    // initialize the seg tree with arr[0:n-1]
    st.build(arr, 1, 0, n - 1);

    // query the max within range [1:4]
    cout << st.query(1, 0, n - 1, 1, 4) << endl; 

    // update the range [1:3] with the new value 100
    st.update(1, 0, n - 1, 1, 3, 100);

    cout << st.query(1, 0, n - 1, 1, 4) << endl;
}
