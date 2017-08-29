// Status: Accepted
#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 200
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
using namespace std;

int n;

struct edge {
	int u, v;
	int weight;

	edge(int _u, int _v, int _w) : u(_u), v(_v), weight(_w) {}
};

int pa[MAXN], rk[MAXN];

int ufind(int i){
	if(pa[i] != i) pa[i] = ufind(pa[i]);
	return pa[i];
}

int uunion(int a, int b) {
	a = ufind(a); b = ufind(b);
	if(a==b) return 0;
	if(rk[a]>rk[b])
		pa[b] = a;
	else
		pa[a] = b;
	if(rk[a] == rk[b]) rk[b]++;
	return 1;
}

bool edge_cmp(const edge &a, const edge &b) {
	return a.weight < b.weight;
}

bool edge_cmp2(const edge &a, const edge &b) {
	if(a.u == b.u) return a.v < b.v;
	return a.u < b.u;
}

vector<edge> mst(int n, vector<edge> edges) {
	sort(edges.begin(), edges.end(), edge_cmp);
	FOR(i,0,n+1) pa[i] = i;
	vector<edge> res;
	FORIT(e,edges) if (ufind(e->u) != ufind(e->v)) {
		uunion(e->u, e->v);
		res.push_back(edge(min(e->u,e->v),max(e->u,e->v),e->weight));
	}
	sort(res.begin(), res.end(), edge_cmp2);
	return res;
}

int main(){
	int in,t; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		FOR(i,0,n+1) rk[n]= 0;
		vector<edge> input;
		FOR(i,1,n+1) FOR(j,1,n+1){
			cin >> in;
			input.push_back(edge(i,j,in));
		}
		vector<edge> ans = mst(n+1, input);
		cout << "Case #" << TC << ":" << endl;
		FORIT(it,ans){
			cout << it->u << " " << it->v << endl;
		}
	}
	return 0;
}