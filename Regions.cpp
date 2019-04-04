#include <bits/stdc++.h>
using namespace std;
#define LL long long
LL ext_gcd ( LL A, LL B, LL *X, LL *Y ){
    LL x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}
 
inline LL modInv ( LL a, LL m ) {
    LL x, y;
    ext_gcd( a, m, &x, &y );
    x %= m;
    if ( x < 0 ) x += m;
    return x;
}
inline LL bigmod ( LL a, LL p, LL m ) {
    LL res = 1 % m, x = a % m;
    while ( p ) {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m; p >>= 1;
    }
    return res;
}
const LL mod = 1000000007;
#define MAXN 1000000 //1e6
LL fact[MAXN+5],ifact[MAXN+5];
LL nCr(LL n, LL r) {
    if(r > n || n < 0 || r < 0) return 0;
	
	LL res,up,down;
	up = fact[n];
    down = (ifact[r] * ifact[n-r]) % mod;
	res = (up * down) % mod;
	return res;
} 
int main() {
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    ifact[0] = 1;
    for(int i = 1; i <= MAXN; i++) {
        ifact[i] = modInv(fact[i],mod);
    }
    int testCase;
    cin >> testCase;
    assert(testCase >= 1 && testCase <= 50);
    while(testCase--) {
        LL n,m,k,len;
        LL ans = 0, freeZero,x,y,tmp,ways;
        cin >> n >> m >> k >> len;
        assert(n >= 2 && n <= 1000000);
        assert(m >= 2 && m <= 1000000);
        assert(k >= 1 && k <= 100000);
        assert(len >= 1 && len <= n);
        for(LL i = k; i+i >= k; i--) {
            
            //first index is 0
            freeZero = n-1-( i * (len-1) );
            x = nCr(freeZero+1, i);
            y = nCr(i,k-i);
            tmp = ( bigmod(m, i+i-k, mod) * bigmod( nCr(m,2), k-i, mod ) ) % mod;
            ways = (tmp * x) % mod;
            ways = (ways * y) % mod;
            ans = (ans + ways) % mod;
            //first index is 1
            freeZero = n - ( i * (len-1) );  
            x = nCr(freeZero-1, i-1);
            ways = (tmp * x) % mod;
            ways = (ways * y) % mod;
            ways = (ways * (len-1)) % mod;  
            ans = (ans + ways) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}