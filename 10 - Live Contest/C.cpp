// Status: Accepted
#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXC 10005
#define MAXN 105
#define oo 1000000000
#define ENDPOINT 1
#define TURNER 2
#define EMPTY 0
#define LASER 3
#define N 0
#define E 1
#define S 2
#define W 3
#define snd second
#define fst first
#define mp(i,j) make_pair(i,j)
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;

int n;

bool visited[100][100][4];
int m[100][100];

void ini(){
	FOR(i,0,100) FOR(j,0,100){
		FOR(k,0,4)
		 visited[i][j][k] = false;
		 m[i][j] = EMPTY;
	 }
	 FOR(i,0,100){
		 m[0][i] = ENDPOINT;
		 m[i][0] = ENDPOINT;
		 m[i][n+1] = ENDPOINT;
		 m[n+1][i] = ENDPOINT;
	 }
}

void printboard(){
	cout << endl;
	FOR(i,0,n + 2){
		FOR(j,0,n+2)
			cout << m[j][i];
		cout << endl;
	}
	cout << endl;
}

pii solve(int x, int y, int d){
	//cout << "point (" << x<< "," << y <<  "), d = " << d << endl;
	if(visited[x][y][d])
		return mp(0,0);
	if(m[x][y] == ENDPOINT)
		return mp(x,y);
	if(m[x][y] == LASER)
		m[x][y] = ENDPOINT;
	if(m[x][y] == TURNER){
		visited[x][y][d] = true;
		if(d == N)
			return solve(x+1, y, E);
		if(d == E)
			return solve(x, y-1, S);
		if(d == S)
			return solve(x-1, y, W);
		if(d == W)
			return solve(x,y+1, N);
	}
	if(d == N)
		return solve(x, y+1, N);
	if(d == E)
		return solve(x+1, y, E);
	if(d == S)
		return solve(x, y-1, S);
	if(d == W)
		return solve(x-1,y, W);
}

int dir(int x, int y){
	if(x == 0)
		return E;
	if(y == 0)
		return N;
	if(x == n+1)
		return W;
	if(y == n+1)
		return S;
	return -1;
}

int main(){
	int x,y,r,t; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> r;
		ini();
		FOR(i,0,r){
			cin >> x >> y;
			m[x][y] = TURNER;
		}
		cin >> x >> y;
		m[x][y] = LASER;
		//printboard();
		pii ans = solve(x,y,dir(x,y));
		cout << ans.fst << " " << ans.snd << endl;
	}
	return 0;
}

