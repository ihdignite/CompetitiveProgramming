#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e6;
int n, m, p[mxN], q[mxN];
ll a[mxN+1], b[mxN+1], s[mxN], t[mxN], ans, lz[1<<21];
vector<array<ll, 2>> e[mxN+1];
array<ll, 2> st[1<<21];

void app(int i, ll x) {
	st[i][0]+=x;
	st[i][1]+=x;
	lz[i]+=x;
}

void psh(int i) {
	app(2*i, lz[i]);
	app(2*i+1, lz[i]);
	lz[i]=0;
}

void upd1(int l1, int r1, ll x, int i=1, int l2=0, int r2=m) {
	if(l1<=l2&&r2<=r1) {
		app(i, x);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd1(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd1(l1, r1, x, 2*i+1, m2+1, r2);
	st[i][0]=min(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
}

void upd2(int l1, int r1, ll x, int i=1, int l2=0, int r2=m) {
	if(st[i][0]>=x)
		return;
	if(l1<=l2&&r2<=r1&&st[i][0]==st[i][1]) {
		app(i, x-st[i][0]);
		return;
	}
	int m2=(l2+r2)/2;
	psh(i);
	if(l1<=m2)
		upd2(l1, r1, x, 2*i, l2, m2);
	if(m2<r1)
		upd2(l1, r1, x, 2*i+1, m2+1, r2);
	st[i][0]=min(st[2*i][0], st[2*i+1][0]);
	st[i][1]=max(st[2*i][1], st[2*i+1][1]);
}

ll qry(int l1, int i=1, int l2=0, int r2=m) {
	if(l2==r2)
		return st[i][0];
	int m2=(l2+r2)/2;
	psh(i);
	return l1<=m2?qry(l1, 2*i, l2, m2):qry(l1, 2*i+1, m2+1, r2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> a[i+1] >> s[i] >> p[i], a[i+1]+=a[i];
	for(int i=0; i<m; ++i) {
		cin >> b[i+1] >> t[i] >> q[i], b[i+1]+=b[i];
		ans+=q[i];
		e[upper_bound(a, a+n+1, t[i]-b[i+1])-a].push_back({i, -q[i]});
	}
	memset(st, 0xfe, sizeof(st));
	upd2(0, 0, 0);
	e[0].push_back({0, 0});
	for(int i=0; i<=n; ++i) {
		if(i) {
			int j=upper_bound(b, b+m+1, s[i-1]-a[i])-b;
			if(j)
				e[i].push_back({j-1, p[i-1]});
		}
		sort(e[i].begin(), e[i].end());
		if(!e[i].size()||e[i].back()[0]^m)
			e[i].push_back({m, 0});
		for(int j=0; j<e[i].size(); ++j) {
			upd1(0, e[i][j][0], e[i][j][1]);
			if(j+1<e[i].size())
				upd2(e[i][j][0], e[i][j+1][0], qry(e[i][j][0]));
		}
	}
	cout << ans+qry(m);
}
