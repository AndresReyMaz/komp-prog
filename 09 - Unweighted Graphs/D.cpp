// Status: Accepted
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <stack>
#include <cstring>
#include <string>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define all(x) x.begin(), x.end()
#define MAXN 100005
#define MAXM 100005
#define oo 1000000000
typedef vector<int> vi;
typedef pair<int, int> pii;

int n;
vi points;
vi adj[MAXN];
vi inLoop;
vi cantTake;
bool visited2[MAXN];
int dupl[MAXN];
bool fnd[MAXN];
int low[MAXN]; int num[MAXN]; int comp[MAXN];
int curnum;
int ccomp = curnum = 0;
stack<int> st;

void scc(int u) {
	st.push(u); low[u] = num[u] = curnum++;
	FORIT(i,adj[u])
		if(num[*i] == -1){
			scc(*i); low[u] = min(low[u],low[*i]);
		} else if (comp[*i] == -1)
			low[u] = min(low[u],num[*i]);
	
	if (num[u] == low[u]) {
		while (true) {
			int cur = st.top(); st.pop();
			comp[cur] = ccomp;
			if (cur == u) break;
		}
		ccomp++;
	}
}

void ini(){
	points.clear();
	inLoop.clear();
	cantTake.clear();
	FOR(i,0,n+1){
		comp[i] = num[i] = -1;
		dupl[i] = fnd[i] = false;
		adj[i].clear();
		visited2[i] = false;
	}
}

void dfs2(int u){
	if(visited2[u])
		return;
	visited2[u] = true;
	cantTake.push_back(u);
	FORIT(i,adj[u])
		dfs2(*i);
}

int main(){
	int t,a,b,m,in; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> m;
		ini();
		int sum = 0;
		// Reading input
		points.push_back(0);
		FOR(i,1,n+1){
			cin >> in;
			sum += in;
			points.push_back(in);
		}
		FOR(i,0,m){
			cin >> a >> b;
			adj[a].push_back(b);
		}

		// Performing scc
		FOR(i,1,n+1) if (num[i] == -1)
			scc(i);
		// Now we have the comp[] array. iterate and find duplicates.
		FOR(i,1,n+1){
			if(fnd[comp[i]] == true){
				dupl[comp[i]] = true;
			}
			fnd[comp[i]] = true;
		}

		// Now we know which are scc. Add those to inLoop
		FOR(i,1,n+1){
			if(dupl[comp[i]]){
				inLoop.push_back(i);
				//cout << i << " has been added to inLoop"<<endl;
			}
		}
		FORIT(i,inLoop)
			dfs2(*i);

		int sumCantTake = 0;
		FORIT(i,cantTake){
			//cout << "Adding " << points[*i] << " to sumCantTake" << endl;
			sumCantTake += points[*i];
		}
		cout << "Case #" << TC << ": " << (sum - sumCantTake) << endl;
	}
	return 0;
}