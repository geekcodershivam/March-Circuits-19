#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define N 100005
#define en '\n'
ll inf = 1e16;
ll mod = 1e9 + 7;
 
 
ll abs1(ll x) {
  if (x < 0)
    return -x;
  return x;
}
ll power(ll x, ll n, ll mod) {
  ll res = 1;
  x %= mod;
  while (n) {
    if (n & 1)
      res = (res * x) % mod;
    x = (x * x) % mod;
    n >>= 1;
  }
  return res;
}
 
ll dp[20][1 << 4][11][2][3][5][7][3]; 
 
ll f(ll x) {
  if (x == 2)
    return 0;
  if (x == 3)
    return 1;
  if (x == 5)
    return 2;
  if (x == 7)
    return 3;
  assert(false);
}
ll compute(ll mask, ll curr, ll prev1, ll mod2, ll mod3, ll mod5, ll mod7) {
 
  if (__gcd(curr, prev1) == 1 && prev1 != 10)
    return 0;
  for (ll i = 0; i < 4; i++) {
    if (mask & (1 << i)) {
      if (i == 0) {
        if (mod2)
          return 0;
      } else if (i == 1) {
        if (mod3)
          return 0;
      } else if (i == 2) {
        if (mod5)
          return 0;
      } else {
        if (mod7)
          return 0;
      }
    }
  }
  return 1;
} 
 
ll recur(string &s, ll len1, ll indx, ll mask = 0, ll prev1 = 10, ll mod2 = 0,
         ll mod3 = 0, ll mod5 = 0, ll mod7 = 0, ll small = 1) {
 
  if (indx == len1 - 1 && small == 2) 
    return 0;
 
  if (indx >= len1)
    return 0;
 
  if (dp[indx][mask][prev1][mod2][mod3][mod5][mod7][small] != -1)
    return dp[indx][mask][prev1][mod2][mod3][mod5][mod7][small];
 
  ll sum1 = 0;
  ll st = (indx == 0) ? 1 : 0;
  ll limitFor1 = s[indx] - '0';
  for (ll i = st; i <= 9; i++) {
 
 
    if (__gcd(i, prev1) == 1 && prev1 != 10)
      continue;
    ll currMask = 0;
    if (i == 2 or i == 3 or i == 5 or i == 7)
      currMask = mask | (1 << f(i));
    else
      currMask = mask;
    int nmod2, nmod3, nmod5, nmod7;
 
    nmod2 = (mod2 * 10 + i) % 2;
    nmod3 = (mod3 * 10 + i) % 3;
    nmod5 = (mod5 * 10 + i) % 5;
    nmod7 = (mod7 * 10 + i) % 7;
 
    if (small == 0) {
 
      sum1 += compute(currMask, i, prev1, nmod2, nmod3, nmod5,
                      nmod7); 
      sum1 += recur(s, len1, indx + 1, currMask, i, nmod2, nmod3, nmod5, nmod7,
                    0); 
    }
    if (small == 1) {
      if (!(indx == len1 - 1 && i > limitFor1))
        sum1 += compute(currMask, i, prev1, nmod2, nmod3, nmod5,
                        nmod7); 
 
      if (i < limitFor1)
        sum1 +=
            recur(s, len1, indx + 1, currMask, i, nmod2, nmod3, nmod5, nmod7,
                  0); 
      if (i == limitFor1)
        sum1 +=
            recur(s, len1, indx + 1, currMask, i, nmod2, nmod3, nmod5, nmod7,
                  1);
      if (i > limitFor1)
        sum1 +=
            recur(s, len1, indx + 1, currMask, i, nmod2, nmod3, nmod5, nmod7,
                  2); 
    }
    if (small == 2) {
      sum1 += compute(currMask, i, prev1, nmod2, nmod3, nmod5,
                      nmod7); 
      sum1 += recur(s, len1, indx + 1, currMask, i, nmod2, nmod3, nmod5, nmod7,
                    2);
    }
  }
 
  dp[indx][mask][prev1][mod2][mod3][mod5][mod7][small] = sum1;
  return sum1;
}
 
ll solve(ll n) {
  if (n <= 0)
    return 0;
  string s = to_string(n);
 
  memset(dp, -1, sizeof(dp));
  return recur(s, s.length(), 0);
}
 
bool check(ll x) {
  if (x == 2 or x == 3 or x == 5 or x == 7)
    return true;
  return false;
}
 
ll brute(ll n) {
  ll res = 0;
  for (ll i = 1; i <= n; i++) {
    vector<ll> arr, arr2;
    ll curr = i;
    while (curr) {
 
      arr.push_back(curr % 10);
      if (check(curr % 10)) {
        arr2.push_back(curr % 10);
      }
    }
    reverse(arr.begin(), arr.end());
 
    ll flag = 0;
    for (ll i = 0; i < arr.size() - 1; i++) {
      if (__gcd(arr[i], arr[i + 1]) == 1) {
        flag = 1;
        break;
      }
    }
 
    for (ll x : arr2) {
      if (i % x != 0)
        flag = 1;
    }
    res += (flag == 0);
  }
  return res;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  ll l, r;
  cin >> l >> r;
  cout << solve(r) - solve(l - 1) << en;
  return 0;
}