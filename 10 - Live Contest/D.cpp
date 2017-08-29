// Status: Time Limit Exceeded
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define oo 1000000000
using namespace std;

int N;

bool check(string a, string b, int sta, int stb, int minToWin){
	if(stb + minToWin > N) return false;
	if(sta + minToWin > N) return false;
	for(int i = sta, j = stb, k = 0; k < minToWin; i++, j++,k++){
		if(!(abs(a[i]-b[j]) <= 1)) return false;
	}
	return true;
}

int main(){
	int t; cin >> t;
	string a,b;
	FOR(TC,1,t+1){
		cin >> N;
		double cmpN = (double)N;
		cin >> a;
		cin >> b;
		int minToWin = (int) ceil(cmpN/2.0);
		bool test = false;
		for(int i = 0; i < minToWin; i++){
			FOR(j,0,minToWin){
				if(check(a,b,i,j,minToWin)){
					test = true;
					break;
				}
			}
			if(test)
				break;
		}
		if(test)
			cout << "POSITIVE" << endl;
		else
			cout << "NEGATIVE" << endl;
	}
	return 0;
}
