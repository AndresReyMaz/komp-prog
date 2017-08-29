// Status: Time Limit Exceeded
#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define FOR(i,a,b) for(ll i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;

ll n, m;

int main(){
	cin >> n >> m;
	vector<pair<ll, ll> > sch(n);
	ll a, s;
	FOR(i,0,n){
		cin >> a >> s;
		sch[i] = make_pair(a,s);
	}
	bool added[n];
	memset(added, 0, sizeof added);
	sort(all(sch));
	ll cnt = 0;
	FOR(i,0,n){//300001
		if(!added[i]){
			added[i] = true;
			cnt++;
			ll cur = i;
			//cout << "Building a set starting on "<< sch[cur].first << " and ending on " << sch[cur].second + sch[cur].first << endl;
			while(cur != n-1){//300001 - firstloop
				//Check if the next one is saveable. If not, break.
				ll j = cur + 1;
				if(!(sch[j].first <= sch[cur].first + sch[cur].second + m))
					break;
				//Binary search the first next researcher whose schedule doesn't overlap with cur
				ll lo = cur+1;
				ll hi = n-1;
				while(lo < hi){//log(3000000)
					ll m = (lo + hi) / 2;
					if(sch[m].first >= sch[cur].first + sch[cur].second){
						hi = m;
					} else {
						lo = m + 1;
					}
				}
				bool onefound = false;
				j = hi;
				ll mx = j;
				//ll mxlng = sch[j].first + sch[j].second; 
				ll endOfInac = sch[cur].first + sch[cur].second + m;
				while(j < n && sch[j].first <= endOfInac){
					if(!added[j] && sch[j].first >= sch[cur].first + sch[cur].second/* && mxlng <= sch[j].first + sch[j].second*/){
						mx = j;
						//mxlng = sch[j].first + sch[j].second;
						onefound = true;
					}
					j++;
					if(onefound) break;
				}
				if(onefound){
					cur = mx;
					added[mx] = true;
				} else break;
			}
		}
	}
	cout << (n - cnt) << endl;
	return 0;
}