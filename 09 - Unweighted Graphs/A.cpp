// Status: Accepted
#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <cstring>
#include <string>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); it++)
#define all(x) x.begin(), x.end()
#define MAXN 405
#define oo 1000000000
typedef vector<int> vi;
typedef pair<int, int> pii;

int n;
vi adj[MAXN];
vector<string> c[MAXN]; //the callers
int tVisited;
bool visited[MAXN];


//Returns true if is executable.
bool isExec(string name){
	if(name.length() > 9 && name.substr(name.length()-8,8) == ":PROGRAM")
		return true;
	return false;
}


void dfs(int u){
	if(visited[u])
		return;
	visited[u] = true;
	tVisited++;
	FORIT(i,adj[u])
		dfs(*i);
}

int main(){
	int t,k; cin >> t;
	FOR(TC,1,t+1){
		string method, caller;
		cin >> n;
		tVisited = 0;
		memset(visited,false,sizeof visited);
		vector<string> names;
		FOR(i,0,n){
			adj[i].clear();
			c[i].clear();
		}
		map<string,int> m;//k=method identifier, v=index of the order it originally appeared
		vi execs;
		FOR(i,0,n){
			// Just read the methods
			cin >> method >> k;
			m[method] = i;
			if(isExec(method)){
				//cout << " IS EXEC"<<endl;
				execs.push_back(i);
			}
			names.push_back(method);//Debug purposes only
			FOR(j,0,k){
				//Saving them in an array of vectors
				cin >> caller;
				c[i].push_back(caller);
			}
		}
		FOR(i,0,n){ //Now we create the graph
			FORIT(j,c[i])
				adj[m[(*j)]].push_back(i);
		}
		/*FOR(i,0,n){
			cout << names[i] << " calls:";
			FORIT(j,adj[i]){
				cout << " " << (*j);
			}
			cout << endl;
		}*/
		cout << "Case #" << TC << ": ";
		FORIT(u,execs){
			dfs(*u);
		}
		cout << (n-tVisited) << endl;
	}
	return 0;
}