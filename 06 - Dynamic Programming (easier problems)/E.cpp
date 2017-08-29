// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXN 100005
#define oo 1000000000
using namespace std;
typedef vector<int> vi;

int dp[1005][1005];

int times(int n, int m){
	if(m == 1) return 1;
	if(n == 1) return m;
	if(dp[n][m] != -1) return dp[n][m];
	int best = oo; // Best strategy. Want to minimize.
	FOR(i,1,m+1){
		int wc = 0; // Amount of times Lea goes to kitchen in worst case
		if(i != m) // Case if cake is not done
			wc = max(wc, times(n, m-i));
		if(i != 1) // Case if cake is burned
			wc = max(wc, times(n-1, i-1));
		best = min(best, wc+1);
	}
	return dp[n][m] = best;
}

int main(){
	int t,n,m; cin >> t;
	FOR(i,0,1005) FOR(j,0,1005) dp[i][j] = -1;
	FOR(TC,1,t+1){
		cin >> n >> m;
		cout << "Case #" << TC << ": " << times(n,m) << endl;
	}
	return 0;
}
