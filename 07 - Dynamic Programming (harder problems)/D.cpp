// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXC 10005
#define MAXN 105
#define oo 1000000000
using namespace std;
typedef vector<int> vi;

int n,m,finalIndex,myFinalCardIndex;
int cards[MAXC]; //true if this is a position of a chosen card.
int myPicks[MAXN];
double dp[MAXC];

// Initializes arrays
void ini(){
	memset(cards, 0, sizeof cards);
	int curCardIndex = m;
	FOR(i,0,n){
		cards[curCardIndex] = myPicks[i];
		if(i < n-1) curCardIndex += myPicks[i];
	}
	myFinalCardIndex = curCardIndex;
	finalIndex = curCardIndex + myPicks[n-1] - 1; //The last index where there could possibly be a card
	FOR(i,0,finalIndex) dp[i] = -1.0;
}

double prob(int ind){
	if(cards[ind] > 0) return 1.0;
	if(ind > myFinalCardIndex) return 0.0;
	if(dp[ind] != -1.0) return dp[ind];
	// The card is unknown:
	double ans = 0.0;
	FOR(i,2,12){
		if(ind + i > finalIndex) break;
		if(i == 10) ans += prob(ind + 10) * 4/13;
		else ans += prob(ind + i)/13;
	}
	return dp[ind] = ans;
}

double sol(){
	double acc = 0.0;
	FOR(i,1,11){
		acc += prob(i)/10;
	}
	return acc;
}

// Parses the card and returns its numerical value
int parseString(string s){
	if(s.length() > 1) return 10;
	char c = s[0];
	if(c == 'A') return 11;
	if(isalpha(c)) return 10;
	return c - '0';
}

int main(){
	int t; cin >> t;
	string s;
	FOR(TC,1,t+1){
		cin >> n >> m;
		FOR(i,0,n){
			cin >> s;
			myPicks[i] = parseString(s);
		}
		ini();
		cout << "Case #" << TC << ": ";
		printf("%.10f\n", sol());
	}
	return 0;
}
