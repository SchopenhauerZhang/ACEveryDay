#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <random>
#include <cmath>
#include <ctime>
#include <functional>
#include <algorithm>
#include <complex>
#include <numeric>
#include <limits>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <map>
#include <set>
using namespace std;
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define MP(x, y) make_pair((x),(y))
#define FI first
#define SE second
#define LOWB(x) (x & (-x))
#define UNIQUE(a) sort(ALL(a)), (a).erase(unique(ALL(a)), (a).end())
#define HEIGHT(n) (sizeof(int) * 8 - __builtin_clz(n)) //height of range n segment tree
#define INF 1e9
#define INF_LL 4e18
#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*-----------------------------------*/
#define N 100010
int n, k, a[N], b[N];

bool check(ll num) {
  ll rest = k;
  for (int i=0; i<n; i++) {
    if ((ll)a[i] * num > (ll)b[i]) {
      ll need = (ll)a[i] * num - b[i];
      if (need > rest) return false;
      rest -= need;
    }
  }
  return true;
}

ll solve() {
  ll l=0, r=0, best=0;
  for (int i=0; i<n; i++) r = max(r, (ll)(b[i]+k) / a[i]);
  while (l <= r) {
    ll mid = (l + r) >> 1;
    if (check(mid)) {
      best = mid;
      l = mid + 1;
    } else r = mid - 1;
  }
  return best;
}

int main() {
  cin >> n >> k;
  for (int i=0; i<n; i++) scanf("%d", &a[i]);
  for (int i=0; i<n; i++) scanf("%d", &b[i]);
  cout << solve() << endl;
  return 0;
}
