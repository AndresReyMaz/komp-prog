// Status: Accepted
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef pair<int, int> pii;

const int n = 10009;
vi adj[n];
int low[n]; int num[n];
int curnum = 0;

vector<pii> bridges;

void find_bridges(int u, int p){
	low[u] = num[u] = curnum++;
	FORIT(i,adj[u]) {
		if(*i == p) continue;
		if(num[*i] == -1){
			find_bridges(*i, u);
			low[u] = min(low[u], low[*i]);
		} else low[u] = min(low[u], num[*i]);

		if(low[*i] > num[u])
			bridges.push_back(make_pair(min(u,*i),max(u,*i)));
	}
}

int main(){
	int t,m,amount; cin >> t;
	FOR(TC, 1, t+1){
		cin >> amount >> m;
		bridges.clear();
		FOR(i,0,amount+1){
			num[i] = -1;
			adj[i].clear();
		}
		vector<pii> connections;
		map<pii, int> indexes;
		FOR(i,1,m+1){
			int a,b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
			pii val = make_pair(min(a,b),max(a,b));
			connections.push_back(val);
			indexes[val] = i;
		}
		
		FOR(i,1,amount+1) if(num[i] == -1)
			find_bridges(i, -1);
		cout << "Case #" << TC << ":";
		//cout << "Bridges:"<< endl;
		vi answer;
		FORIT(i,bridges){
			//cout << (*i).first << " --> " << (*i).second << endl;
			map<pii,int>::iterator it = indexes.find(*i);
			answer.push_back((*it).second);
		}
		sort(all(answer));
		FORIT(i,answer)
			cout << " " << *i;
		cout << endl;
	}
}