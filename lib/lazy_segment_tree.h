#include <lib/common.h>

class LazySegmentTree {
public:
    ll n;
    vl a;

    struct node {
        ll sum;

        node() {sum = 0; }
        node(ll val) {
            sum = val;
        }
    };

    // CHANGE ME!
    node merge(node l, node r) {
        node temp;
        temp.sum = l.sum + r.sum;
        return temp;
    }

	vl lazy;
	vector<node> tr;

    // CHANGE ME!
	void push(int l, int r, int idx) {
		if(lazy[idx]) {
			tr[idx].sum += (r - l + 1) * lazy[idx];

			if(l != r) {
				lazy[2 * idx + 1] += lazy[idx];
				lazy[2 * idx + 2] += lazy[idx];
			}

			lazy[idx] = 0;
		}
	}

	void init(int l, int r, int idx) {
		if(l == r) {
			tr[idx] = node(a[l]);
			return;
		}

		int mid = (l + r) >> 1;
		init(l, mid, 2 * idx + 1);
		init(mid + 1, r, 2 * idx + 2);

		tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
	}

    template <typename T>
    LazySegmentTree(const vector<T>& arr) : a(arr), lazy(4 * arr.size()), tr(4 * arr.size()) {
        n = a.size();
        init(0, n, 0);
    }

	void update(int qL, int qR, ll val, int l, int r, int idx) {
		push(l, r, idx);

		if(qL > r || l > qR) {
			return;
		}

		if(qL <= l && r <= qR) {
			lazy[idx] += val;
			push(l, r, idx);
			return;
		}

		int mid = (l + r) >> 1;
		update(qL, qR, val, l, mid, 2 * idx + 1);
		update(qL, qR, val, mid + 1, r, 2 * idx + 2);

		tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
	}

    void update(int qL, int qR, ll val) {
        update(qL, qR, val, 0, n, 0);
    }

	node query(int qL, int qR, int l, int r, int idx) {
		push(l, r, idx);

		if(l > qR || r < qL) {
			return node();
		}

		if(qL <= l && r <= qR) {
			return tr[idx];
		}

		int mid = (l + r) >> 1;
		return merge(query(qL, qR, l, mid, 2 * idx + 1), query(qL, qR, mid + 1, r, 2 * idx + 2));
	}

    node query(int qL, int qR) {
        return query(qL, qR, 0, n, 0);
    }
};

int main() {
    vl v{1, 3, 4, 2, 5, 9, 2};
    LazySegmentTree st(v);
    print("query from 3, 6", st.query(3, 6).sum);
    print("query from 3, 5", st.query(3, 5).sum);
    st.update(3, 6, 10);
    print("query from 3, 5", st.query(3, 5).sum);
    return 0;
}