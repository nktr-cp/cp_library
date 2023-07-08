struct Matrix2x2 {
    // a, bが上の行, c, dが下の行
   long a, b, c, d;
};
 
void show(Matrix2x2 A) {
    cout << '[' << endl
         << A.a << ' ' << A.b << endl
         << A.c << ' ' << A.d << endl
         << ']' << endl;
}
 
// return C = A*B
Matrix2x2 mult(Matrix2x2 A, Matrix2x2 B) {
    Matrix2x2 C = {};
    C.a = (A.a % MOD * B.a % MOD) % MOD + (A.b % MOD * B.c % MOD) % MOD;
    C.b = (A.a % MOD * B.b % MOD) % MOD + (A.b % MOD * B.d % MOD) % MOD;
    C.c = (A.c % MOD * B.a % MOD) % MOD + (A.d % MOD * B.c % MOD) % MOD;
    C.d = (A.c % MOD * B.b % MOD) % MOD + (A.d % MOD * B.d % MOD) % MOD;
    return C;
}
 
Matrix2x2 expt(Matrix2x2 A, long p) {
    Matrix2x2 result = {1, 0, 0, 1};
    while (p > 0) {
        if (p & 1) {
            result = mult(result, A);
        }
        A = mult(A, A);
        p >>= 1;
    }
    return result;
}