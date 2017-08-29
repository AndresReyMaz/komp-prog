// Status: Time Limit Exceeded
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define all(x) x.begin(), x.end()
#define MAXN 10005
typedef vector<int> vi;


int n;
int tVisited = 0;
vi adj[MAXN];
vi sol;
bool visited[MAXN];
bool ansset;
bool recheck;
bool missing;

void dfs(int u, vi &a, int l){
	if(visited[u]){
		recheck = true;
		return;
	}
	visited[u] = true;
	tVisited++;
	//cout << "visiting " << u << " with length " << l << endl;
	l++;
	a.push_back(u);
	if(l == n){
		//we have reached the (possible) end of graph
		//therefore everyone should have been visited.
		if(tVisited != n)
			return;
		if(ansset && adj[u].size() != 0){
			//we had already found another solution!
			missing = true;
			return;
		}
		ansset = true;
		sol = a;
	}
	FORIT(i,adj[u])
		dfs(*i,a,l);
}



int main(){
	int t,h,a,b; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> h;
		recheck = missing = ansset = false;
		FOR(i,0,n+1) adj[i].clear(); //Clearing adjacency lists. Critical.
		//Reading the input
		FOR(i,0,h){ //Loading input. Critical.
			cin >> a >> b;
			adj[a].push_back(b);
		}

		cout << "Case #" << TC << ":";
		//Doing a dfs
		FOR(i,1,n+1){ //Running dfs on all nodes. O(n)*O(n)
			memset(visited, false, n+1);
			tVisited = 0;
			vi tmp;
			dfs(i, tmp, 0);
		}
		if(missing){
			cout << " missing hints"<<endl;
		}
		else if(recheck){
			cout << " recheck hints"<<endl;
		}
		else if(ansset){
			FOR(i,0,n){ //Printing answers. Critical. O(n)
				cout << " " << sol[i];
			}
			cout << endl;
		}
		else{
			cout << " missing hints"<<endl;
		}
	}
	return 0;
}