// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;

int l, n, d;

int main(){
	int t, in; cin >> t;
	FOR(TC,1,t+1){
		cin >> l >> n >> d;
		if(n == 0){
			cout << "Case #" << TC << ": impossible" << endl;
			continue;
		}
		bool possible = true;
		vi sl(n);
		FOR(i,0,n){
			cin >> sl[i];

		}
		sort(sl.begin(), sl.end());

		int cnt = 0;
		// Testing if the beginning and end of street is lit
		if(sl[0] - d > 0 || sl[n-1] + d < l){
			possible = false;

		}
		else{
			
			int cover = 0;
			FOR(i,0,n){
				if(cover >= l) break;
				if(sl[i] - d > cover){
					possible = false;
					break;
				}
				if(i < n-1 && sl[i+1] - d <= cover){
					// We can keep going
					
				}
				else{
					
					// We found the last lamp
					cnt++;
					cover = sl[i] + d;
				}
				if(i == n-1){
					if(cover < l){
						possible = false;
					}
					//else cnt++;
				}
			}
		}
		cout << "Case #" << TC << ": ";
		if(possible)
			cout << cnt << endl;
		else cout << "impossible" << endl;
	}
	return 0;
}

