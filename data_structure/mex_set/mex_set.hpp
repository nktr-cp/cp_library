// 区間を set で管理するテクニック
// 複数要素あるときはmap<int,int>か何かをつかってeraseを制御すればよい
// https://rsk0315.hatenablog.com/entry/2022/02/05/043902

#pragma once

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#include <atcoder/segtree>

bool op(bool a, bool b) { return a && b; }
bool e() { return true; }
bool f(bool x) { return x; }

class set_mex {
  int len = 0;
  atcoder::segtree<bool, op, e> seg;
  std::set<int> elts;
  int mex_ = 0;

public:
  set_mex() = default;

  void insert(int i) {
    elts.insert(i);
    if (i < len) {
      seg.set(i, true);
      mex_ = calc_mex();
    }
    while (len == mex_) {
      rebuild(std::max(1, 2 * len));
    }
  }

  void erase(int i) {
    elts.erase(i);
    if (i < len) {
      seg.set(i, false);
    }
    mex_ = calc_mex();
  }

  int mex() {
    return mex_;
  }

private:
  void rebuild(int new_len) {
    len = new_len;
    seg = atcoder::segtree<bool, op, e>(std::vector(new_len, false));
    for (auto i: elts) {
      if (i < new_len) {
        seg.set(i, true);
      }
    }
    mex_  = calc_mex();
  }

  int calc_mex() {
    return seg.max_right<f>(0);
  }
};

