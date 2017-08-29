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

int dp[10000];

struct tourn{
	int a,b,p;
	tourn(int st, int en, int mo) : a(st), b(en), p(mo) { } 
};

// Compares tournament according to the finishing day.
bool cmp(const tourn &t1, const tourn &t2){
	return t1.b < t2.b;
}

// Returns true if both tournaments have overlapping dates.
bool ov(const tourn &t1, const tourn &t2){
	return (!(t1.b < t2.a || t2.b < t1.a));
}

// Takes it, which is the i-th tournament. Returns the profit of all the
// tournaments lesser than i.
int max_prize(const vector<tourn> &vt, int it){
	if(it == 0) return vt[0].p;
	if(dp[it] != -1) return dp[it];
	int ret = -oo;
	ret = max(ret, max_prize(vt, it-1));
	for(int i = it; i >= 0; i--){
		// Find latest-ending tournament earlier than current one that 
		// doesn't overlap.
		if(!ov(vt[it], vt[i])){
			ret = max(ret, vt[it].p + max_prize(vt,i));
			break;
		}
		ret = max(ret, vt[it].p);
	}
	return dp[it] = ret;
}

int main(){
	int t,n,a,b,p; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		memset(dp, -1, sizeof dp);
		vector<tourn> vt;
		FOR(i,0,n){
			cin >> a >> b >> p;
			vt.push_back(tourn(a,b,p));
		}
		sort(all(vt),cmp);
		//FOR(i,0,n)
		//	cout << vt[i].a << " " << vt[i].b << " " << vt[i].p << endl;
		cout << "Case #" << TC << ": " << max_prize(vt,n-1) << endl;
	}
	return 0;
}
