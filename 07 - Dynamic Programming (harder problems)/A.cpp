// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXN 105
#define oo 1000000000
using namespace std;
typedef vector<int> vi;

int m;
int p[MAXN][MAXN];
int dp[MAXN][MAXN];

int sell(int i, int cpusLeft){
	if(i == m) return 0;
	if(cpusLeft == 0) return 0;
	if(dp[i][cpusLeft] != -1) return dp[i][cpusLeft];
	int ans = sell(i+1,cpusLeft);
	FOR(k,0,cpusLeft){
		ans = max(ans, p[i][k] + sell(i+1,cpusLeft-(k+1)));
	}
	return dp[i][cpusLeft] = ans;
}

int main(){
	int c;
	cin >> c >> m;
	FOR(i,0,m){
		FOR(j,0,c){
			cin >> p[i][j];
		}
	}
	FOR(i,0,MAXN) FOR(j,0,MAXN) dp[i][j] = -1;
	cout << sell(0,c) << endl;
	return 0;
}
