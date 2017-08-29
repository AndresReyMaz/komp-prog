// Status: Wrong Answer
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define all(x) x.begin(), x.end()
#define MAXN 300
#define oo 100000000000000
typedef vector<long long> vi;
typedef long long ll;

int n;
ll dist[MAXN][MAXN];
ll weight[MAXN][MAXN];
bool occurred[104];

void ini(){
	FOR(i,0,n+1) FOR(j,0,n+1){
		dist[i][j] = oo;
		weight[i][j] = oo;
	}
	FOR(i,0,104) occurred[i] = false;
}

void floyd_warshall(){
	FOR(i,1,n+1) FOR(j,1,n+1) dist[i][j] = i == j ? 0 : weight[i][j];

	FOR(k,1,n+1) FOR(i,1,n+1) FOR(j,1,n+1)
		dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main(){
	ll t,s,m,a,b,c,si; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> m >> s;
		ini();
		FOR(i,0,m){
			cin >> a >> b >> c;
			if(c > weight[a][b]) continue;
			weight[a][b] = c;
			weight[b][a] = c;
		}
		floyd_warshall();
		ll curmin = oo;
		vi sol;
		FOR(i,0,s){
			cin >> si;
			if(occurred[si]) continue;
			occurred[si] = true;
			if(si == 1){
				curmin = 0;
				sol.clear();
				sol.push_back(1);
			}
			else if(curmin > dist[1][si]){
				curmin = dist[1][si];
				sol.clear();
				sol.push_back(si);
			}
			else if(curmin == dist[1][si]){
				sol.push_back(si);
			}
		}
		sort(all(sol));
		cout << "Case #" << TC << ": " << curmin;
		FORIT(it,sol)
			cout << " " << *it;
		cout << endl;
	}
	return 0;
}