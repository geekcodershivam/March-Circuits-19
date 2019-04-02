#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define N 100005
#define en endl
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
 
ll bit[N];
void update(ll indx, ll val, ll n) {
  while (indx <= n) {
    bit[indx] += val;
    indx += (indx) & (-indx);
  }
}
 
ll query(ll indx) {
  if (indx <= 0)
    return 0;
  ll res = 0;
  while (indx >= 1) {
    res += bit[indx];
    indx -= (indx) & (-indx);
  }
  return res;
}
 
int main() {
  ios::sync_with_stdio(false); cin.tie(NULL); cout.precision(10);
  ll n, l, r;
  cin >> n >> l >> r;
 
  ll arr[n + 5];
  for (ll i = 1; i <= n; i++)
    cin >> arr[i];
 
  ll pre[n + 5];
  pre[0] = 0;
  for (ll i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + arr[i];
  }
 
  ll dp[n + 5];
  memset(dp, 0, sizeof(dp));
  memset(bit, 0, sizeof(bit));
  for (ll i = 1; i <= n; i++) {
    ll right1 = upper_bound(pre, pre + i + 1 , pre[i] - l) - pre;
    right1--;
 
    ll left1 = lower_bound(pre, pre + i + 1 , pre[i] - r) - pre;
 
    right1 = min(right1, i - 1);
 
    if (left1 > right1)
      continue;
 
    dp[i] = query(right1) - query(left1 - 1);
    if (left1 == 0) {
      dp[i]++;
    }
    dp[i] = (dp[i] % mod + mod) % mod;
    update(i, dp[i], n);
  }
 
  cout << dp[n]<< en;
 
  return 0;
}