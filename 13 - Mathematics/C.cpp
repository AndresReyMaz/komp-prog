// Status: Accepted
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
#define all(x) x.begin(), x.end()
#define MAXN 1000000009
using namespace std;
typedef vector<int> vi;

vi pr;

bool isPrime[10000000];

/*vector<int>*/void eratosthenes(int n){
	bool *isMarked = new bool[n+1];
	memset(isMarked, 0, n+1);
	memset(isPrime, 0, 10000000);
	//vector<int> primes;
	int i = 2;
	for(; i*i <= n; ++i)
		if(!isMarked[i]) {
			isPrime[i] = true;
			//primes.push_back(i);
			for(int j = i; j<= n; j+=i)
				isMarked[j] = true;
		}
	for(; i<= n; i++)
		if(!isMarked[i]){
			//primes.push_back(i);
			isPrime[i] = true;
		}
	//return pr = primes;
}

/*
bool testPrime(int x){
	if(x == 1) return false;
	for(int i = 0; i*i <= x;i++){
		if(x%pr[i] == 0){
			//cout << x << endl;
			return false;
		}
		if(pr[i]*pr[i] > x) break;
	}
	return true;
}
*/
bool testPrime(vi v){
	int x = 0;
	FOR(i,0,v.size()){
		x*=10;
		x += v[i];
	}
	//cout << "Testing the number "<< x << endl;
	//cout << isPrime[x]<<endl;
	return isPrime[x];
	//return testPrime(x);
}

vi removeZeros(vi v){
	int i = 0;
	while(v[i] == 0) i++;
	vi ans;
	for(;i<(v.size());i++)
		ans.push_back(v[i]);
	return ans;
}

int indexOfLastDiff(vi v1, vi v2){
	FOR(i,0,v1.size()){
		if(v1[i] != v2[i]) return i;
	}
	return v1.size()-1;
}

int main(){
	int t,n; cin >> t;
	eratosthenes(10000000);
	FOR(TC,1,t+1){
		string m;
		cin >> n >> m;
		vi vals;
		set<vi> acc;
		int cnt = 0;
		FOR(i,0,n)
			vals.push_back(m[i]);
		sort(all(vals));
		bool runonce = false;
		vi oldvals;
		int oldIndex = 0;
		do{
			if(runonce){
				oldIndex = indexOfLastDiff(oldvals,vals);
			}
			FOR(i,0,n){		
				FOR(j,oldIndex+1,n+1-i){
					vi test;
					for(int l = 0; l < j; l++){
						test.push_back(vals[l+i]-'0');
					}
					test = removeZeros(test);
					if(acc.find(test) == acc.end() && testPrime(test)){
						cnt++;
						acc.insert(test);
					}
				}
			}
			runonce = true;
			oldvals = vals;
		}while(next_permutation(all(vals)));
		cout << "Case #" << TC << ": " << cnt<< endl;
	} 
	return 0;
}