// Status: Time Limit Exceeded
#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#define FOR(i,a,b) for(ll i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define SPLIT 4
#define ROW1 0
#define ROW2 1
using namespace std;
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef vector<ll> vll;

ll n;
ll racks[2][1000007];

struct wpair{
	int l1;
	int l2;
	ll w;
	short dist;
	wpair(int a, int b, ll c, short d) : l1(a), l2(b), w(c), dist(d) {};
};

bool wcompare(wpair w1, wpair w2){ return w1.w < w2.w; }

int main(){
	cin >> n;
	//memset(loc,-1,sizeof loc);
	vector<wpair> pairs;
	map<ll, ll> locs;//<weight amount, location in pairs> 
	ll in;
	int nadded = 0;
	FOR(i,0,n){
		cin >> in;
		racks[ROW1][i] = in;
		map<ll,ll>::iterator it;
		it = locs.find(in);
		if(it == locs.end()){
			pairs.push_back(wpair(i,-1,in,ROW1));
			locs[in] = nadded;
			nadded++;
		}else{
			pairs[locs[in]].l2 = i;
		}
	}
	FOR(i,0,n){
		cin >> in;
		racks[ROW2][i] = in;
		map<ll,ll>::iterator it;
		it = locs.find(in);
		if(it == locs.end()){
			pairs.push_back(wpair(i,-1,in,ROW2));
			locs[in] = nadded;
			nadded++;
		}else if(pairs[locs[in]].dist == ROW2){
			pairs[locs[in]].l2 = i;
		}
		else{
			pairs[locs[in]].dist = SPLIT;
			pairs[locs[in]].l2 = i;
		}
	}
	sort(all(pairs),wcompare);
	ll ans = 0;
	for(ll i = n-1; i >= 0; i--){
		wpair w1 = pairs[i];
		if(w1.dist == SPLIT){
			ans = w1.w;
			break;
		}
		bool getout = false;
		FOR(j,w1.l1+1,w1.l2){
			//cout << "Comparing " << racks[w1.dist][j] << " with " << w1.w << endl;
			if(racks[w1.dist][j] > w1.w){
				ans = w1.w;
				getout = true;
				break;
			}
		}
		if(getout) break;
	}
	cout << ans << endl;
	return 0;
}