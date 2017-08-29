// Status: Accepted
#include <iostream>
#include <cstdio>
#include <cstring>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define MAX_N 50009
using namespace std;
char T[MAX_N], P[MAX_N];
int b[MAX_N], n, m;

void kmpPreprocess() {
	int i = 0, j = -1; b[0] = -1;
	while (i < m) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}

int kmpSearch() {
	int i = 0, j = 0;
	int cnt = 0;
	while (i < n) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == m) {
			cnt++;
			j = b[j];
		}
	}
	return cnt;
}

int main(){
	int t; cin >> t;
	FOR(TC,1,t+1){
		scanf("%s",T);
		scanf("%s",P);
		m = strlen(P);
		n = strlen(T);
		kmpPreprocess();
		cout << "Case #" << TC << ": " << kmpSearch() << endl;
	}
	return 0;
}