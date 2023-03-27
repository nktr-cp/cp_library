// RMQに答えるセグメントツリー
// 0-indexedだが区間が半閉区間であることに注意([a,b))
#pragma once

int const INF = __INT_MAX__;
struct SegmentTree {
private:
    int n;
    vector<int> node;

public:
    // O(N)
    // 元配列vをセグメント木で表現する
    SegmentTree(vector<int> v) {
        // 最下段のノード数は元配列のサイズ以上になる最小の2冪 -> これをnとおく
        // セグメント木全体で必要なノード数は2n-1個
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1, INF);

        // 最下段に値を入れた後に、下の段から順番に値を入れる
        // 値を入れるには、自分の子の2値を参照すれば良い
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = min(node[2*i+1], node[2*i+2]);
    }

    // O(log N)
    void update(int x, int val) {
        // 最下段のノードにアクセスする
        x += (n-1);

        // 最下段のノードを更新したら、あとは親に上って更新していく
        node[x] = val;
        while(x > 0) {
            x = (x-1) / 2;
            node[x] = min(node[2*x+1], node[2*x+2]);
        }
    }

    // O(log N)
    // 要求区間 [a, b) 中の要素の最小値を答える
    // k := 自分がいるノードのインデックス
    // 対象区間は [l, r) に当たる

    int getmin(int a, int b, int k=0, int l=0, int r=-1) {
        // 最初に呼び出された時の対象区間は [0, n)
        if(r < 0) r = n;

        // 要求区間と対象区間が交わらない -> 適当に返す
        if (r <= a || b <= l) return INF;

        // 要求区間が対象区間を完全に被覆 -> 対象区間を答えの計算に使う
        if(a <= l && r <= b) return node[k];

        // 要求区間が対象区間の一部を被覆 -> 子について探索を行う
        // 左側の子を vl ・ 右側の子をvrとしている
        // 新しい対象区間は、現在の対象区間を半分に割ったもの
        int vl = getmin(a, b, 2*k+1, l, (l+r)/2);
        int vr = getmin(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }

    
};