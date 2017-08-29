// Status: Accepted
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define oo 1000000000
#define N 16
using namespace std;


int main(){
	int t,g1,g2; cin >> t;
	string t1,t2;
	FOR(TC,1,t+1){
		map<string, int> won;
		bool ansfound = false;
		string winner;
		FOR(i,0,N){
			cin >> t1 >> t2 >> g1 >> g2;
			if(ansfound) continue;
			if(g1 > g2){
				if(won.find(t1) != won.end()){ // already in map
					won[t1] += 1;
					if(won[t1] == 4){
						ansfound = true;
						winner = t1;
						continue;
					}
				}
				else{
					won[t1] = 1;
				}
			}
			else{
				if(won.find(t2) != won.end()){ // already in map
					won[t2] += 1;
					if(won[t2] == 4){
						ansfound = true;
						winner = t2;
						continue;
					}
				}
				else{
					won[t2] = 1;
				}
			}
		}
		cout << "Case #" << TC << ": " << winner << endl;
	}
	return 0;
}
