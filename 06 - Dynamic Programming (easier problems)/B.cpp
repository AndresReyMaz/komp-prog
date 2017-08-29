// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXN 10005
#define oo 1000000000
using namespace std;
typedef vector<int> vi;

int gr[3][MAXN]; // The groceries. gr[0] is the i-th grocery type,
                // gr[1] is its weight, gr[2] is its calories. 
int n; // number of groceries available
int sol[105];
int dp[3005][MAXN];
int realn;

void ini(int m){
	FOR(i,0,m+5) FOR(j,0,realn+5) dp[i][j] = -1;
	memset(sol, 0, sizeof sol);
}

/* This function takes the total carrying capacity of Lea, as well as the
 * grocery item that we are currently observing, and returns
 * the maximum total calories retrievable with that capacity.
 */
int calories(int m, int ig){
	if(m == 0) return 0;
	if(m < 0) return -oo;
	if(ig >= realn /* && m > 0 */) return 0;
	if(dp[m][ig] != -1) return dp[m][ig];
	if(m < gr[1][ig]){// Can't carry this one.
		return dp[m][ig] = calories(m, ig + 1);
	}
	return dp[m][ig] = max(gr[2][ig] + calories(m - gr[1][ig], ig + 1), calories(m, ig + 1)); // we take it
}

/* This function extracts all the grocery items actually bought.
 */
void print_calories(int m, int ig){
	if(m == 0) return;
	if(m < 0) return;
	if(ig >= realn) return;
	if(dp[m][ig] == gr[2][ig] + calories(m - gr[1][ig],ig+1)){
		cout << " " << gr[0][ig];
		print_calories(m - gr[1][ig], ig+1);
		return;
	}
	print_calories(m, ig+1);
}

int main(){
	int t,m,p,l,s; cin >> t;
	FOR(TC,1,t+1){
		cin >> m >> n;
		
		int rindex = 0; // Real index in gr[][]
		FOR(i,1,n+1){
			
			cin >> p >> l >> s;
			int j = 0;
			while(j < p){
				gr[0][rindex + j] = i;
				gr[1][rindex + j] = l;
				gr[2][rindex + j] = s;
				j++;
				
			}
			rindex += j;
		}
		realn = rindex;
		ini(m);
		calories(m,0);
		cout << "Case #" << TC << ":";
		print_calories(m,0);
		cout << endl;
	}
	return 0;
}
