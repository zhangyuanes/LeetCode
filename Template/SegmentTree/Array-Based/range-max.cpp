#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    void build(vector<long long>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    // 单点赋值
    void update_point(int idx, long long val, int node, int l, int r) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update_point(idx, val, node * 2, l, mid);
        else update_point(idx, val, node * 2 + 1, mid + 1, r);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    // 区间赋值（逐点更新实现）
    void update_range_val(int ql, int qr, long long val, int node, int l, int r) {
        if (ql > r || qr < l) return;

        if (l == r) {
            tree[node] = val;
            return;
        }

        int mid = (l + r) / 2;
        update_range_val(ql, qr, val, node * 2, l, mid);
        update_range_val(ql, qr, val, node * 2 + 1, mid + 1, r);

        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    // 区间最大值查询
    long long query_range_max(int ql, int qr, int node, int l, int r) {
        if (ql > r || qr < l) return LLONG_MIN;

        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;
        return max(
            query_range_max(ql, qr, node * 2, l, mid),
            query_range_max(ql, qr, node * 2 + 1, mid + 1, r)
        );
    }
};


int main() {
    vector<long long> arr = {1, 3, 5, 7, 9, 11};
    int n = arr.size();

    SegmentTree st(n);
    // initialize the seg tree with arr[0:n-1]
    st.build(arr, 1, 0, n - 1);

    // query the max within range [1:4]
    cout << st.query(1, 4, 1, 0, n-1) << endl; 

    // update the range [1:3] with the new value 100
    st.update(1, 3, 100, 1, 0, n-1);

    cout << st.query(1, 4, 1, 0, n-1) << endl;
}
