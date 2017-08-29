// Status: Accepted
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++)
#define MAXN 20006
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<long long> vll;

int LSOne(int x){ return x&(-x); }

ll query(const vll &tree, int b){
	ll sum = 0;
	for(;b > 0; b-= LSOne(b)) sum += (tree[b]%1000000007);
	return sum%1000000007;
}

void update(vll &tree, int i, int v, int n){
	for(;i <= n; i += LSOne(i)) tree[i] += (v);
}

void update(vll &tree, int l, int r, int v,int n){
	update(tree,l,v,n);
	update(tree,r + 1, -v,n);
}

int main(){
	int t,n,k,a,l,r,v; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> k;
		//Setup variables
		vll tree(n+1,0);
		//Read input
		char f;
		ll cnt=0;
		FOR(i,1,k+1){
			cin >> f;
			if(f == 'q'){
				cin >> a;
				cnt = cnt + (query(tree,a)%1000000007);
			}
			else if(f == 'i'){
				cin >> l >> r >> v;
				update(tree,l,r,v,n);
			}
		}
		cnt = cnt%1000000007;
		printf("Case #%i: %lli\n",TC,cnt);
	}
	return 0;
}