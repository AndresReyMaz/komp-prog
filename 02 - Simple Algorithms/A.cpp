// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXN 10005
using namespace std;
typedef vector<int> vi;

int pa[MAXN];
int rk[MAXN];

int ufind(int i){
	if(pa[i] != i) pa[i] = ufind(pa[i]);
	return pa[i];
}

int uunion(int a, int b){
	a = ufind(a); b = ufind(b);
	if(a==b) return 0;
	if(rk[a] > rk[b])
		pa[b] = a;
	else
		pa[a] = b;
	if(rk[a] == rk[b]) rk[b]++;
	return 1;
}

int main(){
	int t,a,b,c,d,e,f,g; cin >> t;
	FOR(TC,1,t+1){
		cin >> a >> b >> c;
		int mny[a];
		bool marr[a];
		FOR(i,0,a+1) pa[i] = i;
		memset(rk,0,sizeof rk);
		memset(marr,1,sizeof marr);
		FOR(i,1,a){
			cin >> mny[i];
		}
		FOR(i,0,b){
			cin >> d >> e;
			if(d == e) continue;
			uunion(d,e);
		}
		FOR(i,0,c){
			cin >> f >> g;
			if(f==g) continue;
			marr[f] = marr[g] = 0;
			uunion(f,g);
		}
		int mxmny = -1;
		FOR(i,1,a){
			//cout << i << " is " << marr[i] << " and has $ " << mny[i] << endl;
			if(marr[i] && mxmny < mny[i]){
				//cout << "Testing " << i << endl;
				if(ufind(i) != ufind(a)){
					
					mxmny = mny[i];
				}
			}
		}
		cout << "Case #" << TC << ": ";
		if(mxmny >= 0) cout << mxmny << endl;
		else cout << "impossible" << endl;
	}
	return 0;
}
