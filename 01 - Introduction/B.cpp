// Status: Accepted
#include <iostream>
#include <string>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
using namespace std;


int main(){
	int t,N,K,P; cin >> t;
	FOR(TC,1,t+1){
		// read data
		P=0;
		string ins;
		cin >> K >> N;
		string names[N+1];
		int pa[N+1][K];
		FOR(i,1,N+1){
			cin >> names[i];
			FOR(j,0,K){
				cin >> pa[i][j];
			}
		}
		// check each paper
		
		FOR(cur,1,N+1){
			bool broken = false;
			int cnt = 0;
			FOR(i,1,N+1){
				bool foundForRow = false;
				FOR(j,0,K){
					if(pa[i][j] == cur){// found review
						cnt++;
						if(foundForRow){
							P++;
							broken = true;
							break;
						}
						foundForRow = true;
						if(names[i] == names[cur]){
							P++;
							broken = true;
							break;
						}

					}
				}
				if (broken) break;
			}
			if (broken) continue;
			if(cnt != K) P++;
		}
		cout << "Case #" << TC << ": ";
		if(P==0) cout << "NO";
		else cout << P;
		cout << " PROBLEM";
		if(P!=1) cout << "S";
		cout << " FOUND" << endl; 
	}
	return 0;
}
