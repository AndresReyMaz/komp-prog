// Status: Accepted
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++)
#define MAXN 20006
#define MD 1000000007
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<long long> vll;


int LSOne(int x){ return x&(-x); }
int n,cur;


void change(vi &tree, int i, int dif){
	for(;i <= n; i += LSOne(i)) tree[i] += dif;
}

int sum(const vi &tree, int i){
	return (i == 0) ? 0 : tree[i] + sum(tree, i - LSOne(i));
}

// Finds first existing ball in range [a,b]
int bsearch(const vi &tree, int a, int b){
	int lo = a, hi = b;
	while(lo < hi){
		int mid = (lo + hi) / 2;
		if(sum(tree,mid) - sum(tree,lo - 1) > 0){
			hi = mid;
		}
		else
			lo = mid + 1;
	}
	return hi;
}
// Returns next spot (irrespective of whether there is a ball there or not)
int nxt(int i){ return (i == n) ? 1 : i+1; }

int main(){
	int in;
	cin >> n;
	vi tree(n+1);
	vi arr(n+1);

	arr[0] = 0; tree[0] = 0;
	//Building the tree. Contains sum of all individual elements (all 1s)
	FOR(x,1,n+1){
		int cnt = 0;
		arr[x] = 1;
		FOR(i,x-LSOne(x)+1,x+1){
			cnt+= arr[i];
		}
		tree[x] = cnt;
	}
	/*
	FOR(i,1,n+1){
		printf("tree[%i] = %i\n",i,tree[i]);
	}
	*/
	//Reading the input
	FOR(i,1,n+1){
		cin >> in;
		arr[in] = i;
	}
	//Juggling the balls
	long long cnt = 0;
	cur = 1; //Starting at ball no.1
	FOR(i,1,n+1){
		in = arr[i];
		//cout << "cur is now " << cur << " and we want to drop " << in << endl;
		int s2 = sum(tree,in);
		if(cur == in){
			//We're already at the ball we need to drop
			//cout << "We're already at the ball we need to drop" << endl;
		}
		else{
			int s1 = sum(tree,cur);
			
			if(cur < in)
				cnt += min(s2-s1, (sum(tree,n)-s2)+s1); // Counterclockwise vs clockwise
			else
				cnt += min(s1-s2, (sum(tree,n)-s1)+s2); // Clockwise vs counterclockwise
			
		}
		change(tree,in,(-1));
		cnt++; // 1 for ball drop
		//Special case: ball dropped was the last one
		if(in == n){
			cur = bsearch(tree,1,in-1);
		}
		else{
			//Try to see if next ball has been dropped yet
			int s3 = sum(tree, in+1);
			if(s3 - (sum(tree,in)) > 0){
				cur = in+1;
			} else {
				// Find next available ball with binary search
				if(sum(tree,n) - s3 > 0){
					//The next ball is somewhere in the range [in+1,n]
					cur = bsearch(tree,in+1,n);
				} else {
					//The next ball is somewhere in the range [1,in-1]
					cur = bsearch(tree,1,in-1);
				}
			}
		}
		/*
		FOR(i,1,n+1){
			if(sum(tree,i) - sum(tree,i-1) > 0) cout << i << " ";
		}
		
		cout << "cnt = " << cnt << endl;
		*/
	}

	cout << cnt << endl;
	/*
	FOR(i,1,n+1){
		printf("tree[%i] = %i\n",i,tree[i]);
	}
	*/
	return 0;
}
