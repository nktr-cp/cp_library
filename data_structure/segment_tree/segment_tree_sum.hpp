// 区間和クエリに答えるセグメントツリー
// 0-indexedだが区間が半閉区間であることに注意([a,b))
#pragma once

struct SegmentTree{
private:
    int n;
    vector<int> node;
public:
    SegmentTree(vector<int> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1, 0);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = node[i*2+1] + node[i*2+2];
    }

    void add(int k, int val) {
        k += (n-1);
        node[k] += val;

        while(k > 0) {
            k = (k-1)/2;
            node[k] = node[2*k+1] + node[2*k+2];
        }
    }

    int getsum(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        if(b <= 1 || r <= a) return 0;
        if(a <= 1 && r <= b) return node[k];

        int vl = getsum(a, b, 2*k+1, l, (l+r)/2);
        int vr = getsum(a, b, 2*k+2, (l+r)/2, r);
        return vl + vr;
    }
};