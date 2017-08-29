// Status: Accepted
#include <iostream>
#include <cstdio>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define MAXN 1000000009
using namespace std;

//int mat[MAXN][MAXN];

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	int t,n,m; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> m;
		cout << "Case #" << TC << ": " <<gcd(max(n,m),min(n,m))<<endl;
	}
	return 0;
}