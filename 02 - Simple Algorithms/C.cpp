// Status: Accepted
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++)
#define MAXN 20006
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int pa[MAXN];
int rk[MAXN];
int cnt[MAXN];
int enemy[MAXN];

int uunion(int a, int b);
int ufind(int i){
	if(pa[i] != i)
		pa[i] = ufind(pa[i]);
	return pa[i];
}

void addXcnt(int i,int x){// Used to handle the count of how many elements are in this set. Takes x and adds it to cnt[(i's representative)]
if(pa[i] == i){
	cnt[i]+=x;
}
else
	addXcnt(pa[i],x);
}

void uenemize(int a, int b){ // A is the parent of B
	if(enemy[a] > 0 && enemy[b] < 0){
		// A has enemies but B does not

		return;
	}
	else if(enemy[b] > 0 && enemy[a] < 0){
		// B has enemies but A does not
		enemy[a] = ufind(enemy[b]);
		enemy[b] = -1;
		return;
	}
	else if(enemy[a] > 0 && enemy[b] > 0){
		// Both A and B have enemies
		uunion(enemy[a],enemy[b]);
		enemy[a] = ufind(enemy[a]);
		enemy[b] = -1;
	}
}

int uunion(int a, int b){
	a = ufind(a); b = ufind(b);
	if(a == b) return 0;
	if(rk[a] > rk[b]){
		//a is rep
		pa[b] = a;
		uenemize(a,b);
		addXcnt(a,cnt[b]);
		cnt[b] = 1;
	}
	else{
		//b is rep
		pa[a] = b;
		uenemize(b,a);
		addXcnt(b,cnt[a]);
		cnt[a] = 1;
	}
	if(rk[a] == rk[b]) rk[b]++;
	return 1;
}

int main(){
	int t,n,m,x,y; cin >> t;
	char c;
	FOR(TC,1,t+1){
		// Read the input
		cin >> n >> m;

		// Setting up environment
		FOR(i,0,n+1){
			pa[i] = i;
			cnt[i] = 1;
			rk[i] = 0;
			enemy[i] = -1;
		}

		// Reading all the interactions
		FOR(i,0,m){
			cin >> c >> x >> y;
			if(c=='F'){
				// Friendship
				// Join both subsets
				uunion(x,y);

				// The enemy of my enemy is my friend
				x = ufind(x);
				y = ufind(y);
				if(enemy[y] > 0 && enemy[ufind(enemy[y])] > 0)
					uunion(x,enemy[ufind(enemy[y])]);
				if(enemy[x] > 0 && enemy[ufind(enemy[x])] > 0)
					uunion(y,enemy[ufind(enemy[x])]);
			}
			else if(c=='A'){
				// Antipathy
				x = ufind(x);
				y = ufind(y);
				// Make all enemies of X friends of Y
				// If repX has enemies
				if(enemy[x] > 0 ){
					// Join repY with enemies of repX
					uunion(y,enemy[x]);
				}
				else
					enemy[x] = y;
				// Make all enemies of Y friends of X
				if(enemy[y] > 0 ){
					// Join repX with enemies of repY
					uunion(x,enemy[y]);
				}
				else
					enemy[y] = x;
			}
		}
		// FOR(i, 1, n+1){
		// 	printf("pa[%i] = %i\n",i,pa[i]);
		// 	printf("en[%i] = %i\n",i,enemy[i]);
		// }
		printf("Case #%i: ",TC);
		if(cnt[ufind(1)]*2 > n)
			cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}