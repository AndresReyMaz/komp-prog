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
typedef long long ll;


int main(){
	ll t,d,n,s,cnt,in; cin >> t;
	FOR(TC,1,t+1){
		cin >> d >> n;
		s = 0;
		cnt = 0;
		ll mod[d];
		memset(mod,0,sizeof mod);
		mod[0]++;
		FOR(i,0,n){
			cin >> in;
			cnt = (cnt+in)%d;
			//pre[i] = cnt;
			mod[cnt%d]++;
		}
		/*FOR(i,0,n){
			printf("%d ",pre[i]);
		}*/
		//cout << endl;
		FOR(i,0,d){
			//printf("mod[%d] = %d\n",i,mod[i]);
			s+= mod[i]*(mod[i]-1)/2;
		}
		cout << "Case #" << TC << ": " << s << endl;
	}
	return 0;
}
