// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define all(x) x.begin(), x.end()
#define FOR(i,a,b) for(int i = (a); i < b; i++) 

using namespace std;
typedef vector<int> vi;
int N,K;
vi A,zcnt,ncnt;

int LSOne(int x){ return x&(-x); }

// returns sum(0,i)
int qry(const vi &tree, int i){
	return (i == 0) ? 0 : tree[i] + qry(tree, i - LSOne(i));
}

// returns sum(a,b)
int count(const vi &tree, int a, int b){
	return qry(tree,b) - qry(tree,a-1);
}

// Product command.
char p(const vi &nt, const vi &zt, int a, int b){
	if(a > b || a < 0 || b > N) return -1;
	if(count(zt,a,b) > 0) return '0';
	if(count(nt,a,b)%2!=0) return '-';
	return '+';
}

void change(vi &tree, int i, int dif){
	for(;i <= N; i += LSOne(i)) tree[i] += dif;
}

int update(vi &nt, vi &zt, int i, int newV){
	if(i > N || i < 0) return -1;
	int oldV = A[i];
	A[i] = newV;
	if(oldV == 0){
		// Subtract 1 to z
		change(zt, i, -1);
	}
	if(oldV < 0){
		// Subtract 1 to n
		change(nt, i, -1);
	}
	if(newV == 0){
		// Add 1 to z
		change(zt, i, 1);
	}
	if(newV < 0){
		// Add 1 to n
		change(nt, i, 1);
	}
	return 0;
}


int main(){
	int in;
	while(scanf("%i %i", &N, &K)!=EOF){
	vi n(N+1), z(N+1); // z keeps the number of 0s for each node and node's "children"
	A.clear(); zcnt.clear(); ncnt.clear();
	A.push_back(0); zcnt.push_back(0); ncnt.push_back(0);
	int zc, nc = 0;
	FOR(i,1,N+1){
		cin >> in;
		A.push_back(in);
		nc += (in < 0);
		ncnt.push_back(in < 0);
		zc += (in == 0);
		zcnt.push_back(in == 0);
	}
	
	// building the tree
	FOR(x,1,N+1){
		zc = 0;
		nc = 0;
		FOR(i,x-LSOne(x)+1,x+1){
			nc += ncnt[i];
			zc += zcnt[i];
		}
		n[x] = nc;
		z[x] = zc;
	}

	FOR(i,0,K){
		char l; cin >> l;
		if(l == 'P'){
			int I, J; cin >> I >> J;
			cout << p(n,z,I,J);
		}
		else if(l =='C'){
			int I, V; cin >> I >> V;
			update(n,z,I,V);
			
		}
		/*
	FOR(i,1,N+1){
		printf("A[%i] = %i\n",i,A[i]);
	}
	FOR(i,1,N+1){
		printf("z[%i] = %i\n",i,z[i]);
	}
	cout << endl;
	FOR(i,1,N+1){
		printf("n[%i] = %i\n",i,n[i]);
	}*/
	}
	cout << endl;
}
	
	return 0;
}
