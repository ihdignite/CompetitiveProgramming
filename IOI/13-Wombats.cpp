#include "wombats.h"
#include <bits/stdc++.h>
using namespace std;

const int r=5e3, c=200, bs=20, bc=r/bs, sts=512;
int h[r][c-1], v[r][c], st[sts][c][c];

void solve(int a[c], int (*b)[c], int d[c], int l1=0, int r1=c-1, int l2=0, int r2=c-1) {
	if(l1>r1)
		return;
	int m1=(l1+r1)/2, m2=r2;
	for(int i=l2; i<=r2; ++i) {
		if(a[i]+b[i][m1]<=d[m1]) {
			d[m1]=a[i]+b[i][m1];
			m2=i;
		}
	}
	solve(a, b, d, l1, m1-1, l2, m2);
	solve(a, b, d, m1+1, r1, m2, r2);
}

void upd(int l1, int r1, int i=1, int l2=0, int r2=bc-1) {
	if(l2==r2) {
		memset(st[i], 0x3f, sizeof(st[i]));
		for(int j=0; j<c; ++j) {
			st[i][j][j]=0;
			for(int k=l2*bs; k<(l2+1)*bs; ++k) {
				for(int l=1; l<c; ++l)
					st[i][j][l]=min(st[i][j][l-1]+h[k][l-1], st[i][j][l]);
				for(int l=c-1; l; --l)
					st[i][j][l-1]=min(st[i][j][l]+h[k][l-1], st[i][j][l-1]);
				for(int l=0; l<c; ++l)
					st[i][j][l]+=v[k][l];
			}
		}
		return;
	}
	int m2=(l2+r2)/2;
	if(l1<=m2)
		upd(l1, r1, 2*i, l2, m2);
	if(m2<r1)
		upd(l1, r1, 2*i+1, m2+1, r2);
	memset(st[i], 0x3f, sizeof(st[i]));
	for(int j=0; j<c; ++j)
		solve(st[2*i][j], st[2*i+1], st[i][j]);
}

void init(int r, int c, int h[5000][200], int v[5000][200]) {
	memset(::h, 0x3f, sizeof(::h));
	for(int i=0; i<r; ++i)
		for(int j=0; j<c-1; ++j)
			::h[i][j]=h[i][j];
	for(int i=0; i<r-1; ++i)
		for(int j=0; j<c; ++j)
			::v[i][j]=v[i][j];
	upd(0, bc-1);
}

void changeH(int p, int q, int w) {
	h[p][q]=w;
	upd(p/bs, p/bs);
}

void changeV(int p, int q, int w) {
	v[p][q]=w;
	upd(p/bs, p/bs);
}

int escape(int a, int b) {
	return st[1][a][b];
}
