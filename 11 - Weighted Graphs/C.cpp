// Status: Time Limit Exceeded
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#define MAX_V 1000
#define oo 100000000
#define FOR(a,b,c) for(int a = (b); a < c; a++)
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
using namespace std;
typedef vector<int> vi;

// f is size of the flow
int res[MAX_V][MAX_V], mf, f, s, t;
vi p; // stores the BFS spanning tree from s

void augment(int v, int minEdge){ // traverse BFS spanning tree from s->t
	if(v == s) {
		f = minEdge;
		return;
	}
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f;
		res[v][p[v]] += f;
	}
}

int main(){
	int ntc,n,k,m,l; cin >> ntc;
	FOR(TC,1,ntc+1){
		FOR(i,0,MAX_V) FOR(j,0,MAX_V) res[i][j] = 0;
		cin >> n >> k >> m >> l;
		s = 0;
		t = n + k + m + 1;
		FOR(i,1,n+1) // connecting fountains to master source
			res[s][i] = oo;
		FOR(i,n+k+1,n+k+m+1) // connecting wrapping stations to master sink
			res[i][t] = oo;
		FOR(i,0,l){ // Reading belts
			int v, w, c;
			cin >> v >> w >> c;
			if(v > w) swap(v,w);
			res[v][w] = max(res[v][w], c);
			res[w][v] = max(res[w][v], c);
		}
		mf = 0; // mf stands for max_flow
		while (1) {
			f = 0;
			vi dist(MAX_V, oo);
			dist[s] = 0;
			queue<int> q;
			q.push(s);
			p.assign(MAX_V, -1);
			while(!q.empty()) {
				int u = q.front(); q.pop();
				if(u == t) break;
				FOR(v,0,MAX_V)
					if(res[u][v] > 0 && dist[v] == oo)
						dist[v] = dist[u] + 1, q.push(v), p[v] = u;
			}
			augment(t, oo);
			if (f == 0) break;
			mf += f;
		}
		printf("Case #%d: %d\n", TC, mf);
	}
	return 0;
}