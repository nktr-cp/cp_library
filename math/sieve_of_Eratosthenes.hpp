#pragma once
// 1 以上 N 以下の整数のうちの素数を返す
vector<long long> Eratosthenes(long long N) {
    // テーブル
    vector<bool> isprime(N+1, true);
    
    // 0, 1 は予めふるい落としておく
    isprime[0] = isprime[1] = false;

    // ふるい
    for (int p = 2; p <= N; ++p) {
        // すでに合成数であるものはスキップする
        if (!isprime[p]) continue;

        // p 以外の p の倍数から素数ラベルを剥奪
        for (long long q = p * 2; q <= N; q += p) {
            isprime[q] = false;
        }
    }

    vector<long long> primes;
    // 1 以上 N 以下の整数が素数かどうか
    for(long long i=2; i<=N; i++) {
        if(isprime[i]) primes.push_back(i);
    }

    return primes;
}