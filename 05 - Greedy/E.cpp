// Status: Accepted
#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define FOR(i,a,b) for(ll i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef vector<ll> vll;

ll a[4][4];

int n, m;

void cleara(){
	FOR(i,0,4){
		FOR(j,0,4){
			a[i][j] = 0;
		}
	}
}

void fixa(){
	a[0][1]+=a[1][0];
	a[1][0]=0;
	a[0][2]+=a[2][0];
	a[2][0]=0;
	a[0][3]+=a[3][0];
	a[3][0]=0;
	a[1][2]+=a[2][1];
	a[2][1]=0;
	a[1][3]+=a[3][1];
	a[3][1]=0;
	a[2][3]+=a[3][2];
	a[3][2]=0;
}

void printa(){
	FOR(i,0,4){
		FOR(j,0,4){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

vll getnond(){
	vll tmp(6);
	tmp[0] = a[0][1];
	tmp[1] = a[0][2];
	tmp[2] = a[0][3];
	tmp[3] = a[1][2];
	tmp[4] = a[1][3];
	tmp[5] = a[2][3];
	sort(all(tmp));
	return tmp;
}

vll getdiag(){
	vll tmp(4);
	tmp[0] = a[0][0];
	tmp[1] = a[1][1];
	tmp[2] = a[2][2];
	tmp[3] = a[3][3];
	sort(all(tmp));
	return tmp;
}

vll getmdiag(){
	vll tmp(4);
	FOR(i,0,4) tmp[i] = 0;
	return tmp;
}

vll getmnond(){
	vll tmp(6);
	FOR(i,0,3) tmp[i] = -10;
	FOR(i,3,6) tmp[i] = 10;
	return tmp;
}

// Returns the value of multiplying each index of a with its corresponding index of b
ll val(const vll &a, const vll &b){
	ll s =  a.size();
	ll tmp = 0;
	FOR(i,0,s){
		tmp += a[i]*b[i];
	}
	return tmp;
}

int ind(char c){
	if(c == 'A') return 0;
	if(c == 'C') return 1;
	if(c == 'T') return 2;
	if(c == 'G') return 3;
	return -1;
}


int main(){
	ll t; cin >> t;
	FOR(TC,1,t+1){
		cleara();
		cin >> n >> m;
		vs human(n);
		FOR(i,0,n){
			cin >> human[i];
		}
		int len = human[0].length();
		string mouse;
		FOR(j,0,m){
			cin >> mouse;
			FOR(i,0,n){
				int ptr = 0;
				while(ptr < len){
					a[ind((human[i])[ptr])][ind(mouse[ptr])]++;
					ptr++;
				}
			}
		}
		fixa();
		//cout << "Case #" << TC << ": " << endl;
		//printa();
		vll diag = getdiag();
		vll nond = getnond();
		// Base case to save ourselves the work
		vll mnond = getmnond();
		vll mdiag = getmdiag();
		ll ans = val(nond,mnond);
		if(!ans){
			cout << "Case #" << TC << ": 0" << endl;
			break;
		}
		do{
			ll oldans = ans;
			if(mnond[3] > -10)
				mnond[3]--;
			//else mnond[4]--;
			if(mdiag[3] < 10) mdiag[3]+=2;
			else if(mdiag[2] < 10) mdiag[2]+=2;
			else if(mdiag[1] < 10) mdiag[1]+=2;
			else mdiag[0]+=2;

			ans = val(nond,mnond) + val(diag,mdiag);
			if(ans < oldans){
				ans = oldans;
				break;
			}
		}while(mdiag[0] < 10);
		cout << "Case #" << TC << ": " << ans << endl;
	}
	return 0;
}