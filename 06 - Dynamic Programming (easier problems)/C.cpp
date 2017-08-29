// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXN 100005
#define oo 1000000000
#define PETRA 0
#define JAN 1
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;

double n;
int tJan;

pii dp[1005][505];

void ini(){
	FOR(i,0,n+1){
		FOR(j,0,n/2+3){
			FOR(k,0,2){
				dp[i][j] = make_pair(-1,-1);
			}
		}
	}
}

struct gdi{
	int p, j;
	gdi(int pe, int ja) : p(pe), j(ja) { }
};

bool cmp(const gdi &g1, const gdi &g2){
	if(g1.p == g2.p) return g2.j > g1.j;
	return g1.p > g2.p;
}

/* Takes the vector of goodies and the position in it, as well as the
 * number of goodies Jan still needs to take. Returns a pair that has
 * the optimal solution for Jan.
 * 
 * IMPORTANT! The goodies vector *MUST* be sorted in order of the 
 * preference of Petra (i.e. the one she would take first, if we follow
 * her strategy).
 */
pii divGdis(const vector<gdi> &vg, int i, int left, int turn){
	if(i == n) return make_pair(0,0);
	if(dp[i][left].second != -1) return dp[i][left]; /////////////////////////////////
	
	if(turn == PETRA){// This turn must go to Petra.
		pii ans = divGdis(vg,i+1,left,JAN);
		ans.first += vg[i].p;
		return dp[i][left] = ans;
	}
	// else if(turn == JAN)>>> All the following
	
	
	pii ans = make_pair(0,0);
	if(n - i == left){// Petra already took all the candies she can
		//cout << "Giving remaining candies to Jan" << endl;
		ans = divGdis(vg, i + 1, left - 1,JAN);
		ans.second += vg[i].j;
		//cout << "Returning (" << ans.first << "," << ans.second << ")" << endl;
		return dp[i][left] = ans;
	}
	
	// Try to give the current candy to Jan
	pii try1 = divGdis(vg, i + 1, left - 1,PETRA);
	try1.second += vg[i].j;
	ans = try1;
	
	// Try to give the current candy to Petra
	pii try2 = divGdis(vg, i + 1, left,JAN);
	try2.first += vg[i].p;
	if(try2.second == ans.second){
		if(try2.first > ans.first)
			ans = try2;
	}
	else if(try2.second > ans.second){
		ans = try2;
	}
	return dp[i][left] = ans;
	
}

int main(){
	int t,p,j; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		ini();
		vector<gdi> vg;
		string name;
		cin >> name;
		FOR(i,0,n){
			cin >> p >> j;
			vg.push_back(gdi(p,j));
		}
		sort(all(vg),cmp);
		/*FOR(i,0,n){
			cout << vg[i].p << " and " << vg[i].j << endl;
		}*/
		pii ans = make_pair(-1,-1);
		if(name == "Jan"){
			tJan = (int)ceil(n/2); // Total of goodies Jan has to get
			ans = divGdis(vg,0,tJan,JAN);
		}
		else if(name == "Petra"){
			tJan = (int)floor(n/2); // Total of goodies Jan has to get
			ans = divGdis(vg,0,tJan,PETRA);
		}
		cout << "Case #" << TC << ": " << ans.first << " " << ans.second << endl;
		//cout << endl;
	}
	return 0;
}
