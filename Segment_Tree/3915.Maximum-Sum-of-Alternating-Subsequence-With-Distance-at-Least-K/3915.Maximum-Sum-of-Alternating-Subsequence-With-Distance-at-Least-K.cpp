using ll = long long;

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


class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, int k) {
        int n = nums.size();
        ll maxv = 100000;
        SegmentTree segUp(maxv), segDown(maxv);
        vector<ll>up(n), down(n);
        ll ret = 0;

        for (int i=0; i<n; i++) {
            if (i-k>=0) {
                int v = nums[i-k];
                segUp.update_range_val(v, v, up[i-k], 1, 1, maxv);
                segDown.update_range_val(v, v, down[i-k], 1, 1, maxv);
            }

            int v = nums[i];
            ll bestDown = segDown.query_range_max(1, v-1, 1,1,maxv);
            if (bestDown == LLONG_MIN)
                up[i] = v;
            else
                up[i] = bestDown + v;

            ll bestUp = segUp.query_range_max(v+1, maxv, 1,1,maxv);
            if (bestUp == LLONG_MIN)
                down[i] = v;
            else
                down[i] = bestUp + v;

            ret = max({ret, up[i], down[i]});

        }

        return ret;
    }
};
