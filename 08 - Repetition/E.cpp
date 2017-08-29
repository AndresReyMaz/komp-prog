// Status: Time Limit Exceeded
#include <iostream>
#include <string>
#include <utility>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXC 10005
#define MAXN 105
#define oo 1000000000
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;

int dp[1000005];



int LSOne(int x){ return x&(-x); }



int query(const vi &tree, int ind){
	if(ind == 0) return 0;
	if(dp[ind] != -1) return dp[ind];
	return dp[ind] = tree[ind] + query(tree, ind - LSOne(ind));
}

int query(const vi &tree, int i, int j){
	return query(tree, j) - query(tree, i-1);
}

vi build_BIT(const vi &A, int n){
	vi tree;
	tree.push_back(0);
	FOR(x,1,n+1){
		int cnt = 0;
		FOR(i,x-LSOne(x)+1,x+1)
			cnt += A[i];
		tree.push_back(cnt);
	}
	return tree;
}

bool satisfies(const vi &tree, int n, int len, int k){
	if(k + len <= n){
		// Fits!
		return (query(tree,k,len) >= 0);
	}
	else{
		int overflow = (k + len) - n;
		int test = query(tree, k, n) + query(tree, overflow);
		return (test >= 0);
	}
}

int sol(const vi &tree, int n){
	int ntSt = 0; // Keeps count of all the cycle shifts that do NOT satisfy
	FOR(k,1,n+1){
		FOR(len,1,n+1){
			if(!satisfies(tree,n,len,k)){
				ntSt++;
				break;
			}
		}
	}
	return n - ntSt;
}

int main(){
	int t,n,in; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		FOR(i,0,n+1) dp[i] = -1;
		vi A; A.push_back(0);
		bool allPos = true;
		bool allNeg = true;
		FOR(i,1,n+1){
			cin >> in;
			A.push_back(in);
			if(in < 0) allPos = false;
			if(in > 0) allNeg = false;
		}
		if(allNeg){
			cout << "Case #" << TC << ": " <<0 << endl;
			continue;
		}
		if(allPos){
			cout << "Case #" << TC << ": " <<n << endl;
			continue;
		}
		vi tree = build_BIT(A,n);
		//FOR(i,1,n+1) cout << tree[i] << " ";
		//cout << endl;
		cout << "Case #" << TC << ": " <<sol(tree,n) << endl;
	}
	return 0;
}
