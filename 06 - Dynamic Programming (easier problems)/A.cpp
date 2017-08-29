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

int dp[MAXN]; // The minumum amount of coins it takes to make amount [i]
int denom[105]; // The denominations of the coins
int n; // Total number of coin denominations
int sol[105]; // The actual amount of each coin denomination needed

void ini(){
  memset(dp, -1, sizeof dp);
  memset(sol, 0, sizeof sol);
  dp[0] = 0;
}

/* This function takes the money amount c and returns the minimum number
 * of coins it takes to make it.
 */
int change(int c){
  if(c == 0) return 0;
  if(c < 0)  return oo;
  if(dp[c] != -1) return dp[c];
  int ret = oo;
  FOR(i,0,n){
    ret = min(1 + change(c - denom[i]), ret);
  }
  return dp[c] = ret;
}

/* The following function calculates the amount of coins needed of each 
 * kind for the minimal answer.
 */
void print_change(int c){
  if(c == 0) return;
  if(c < 0) return;
  FOR(i,0,n){
    if(dp[c] == 1 + change(c - denom[i])){
      sol[i]++;
      print_change(c - denom[i]);
      break;
    }
  }
}

int main(){
	int t,c; cin >> t;
	FOR(TC,1,t+1){
    ini();
    cin >> n >> c;
		FOR(i,0,n){
      cin >> denom[i];
    }
    change(c);
    print_change(c);
		cout << "Case #" << TC << ":";
    FOR(i,0,n){
      cout << " " << sol[i];
    }
    cout << endl;
	}
	return 0;
}
