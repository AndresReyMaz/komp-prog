// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;

double pay(double arr[], int fcost, double prob,int sz){
	double ans = 0;
	FOR(i,1,sz+1){
		ans += arr[i] * pow(prob,i);
	}
	return ans - fcost;
}

int main(){
	int t,n,b; cin >> t;
	FOR(TC, 1, t+1){
		cin >> n >> b;
		double sum=0,a;
		double arr[n+1];
		FOR(i,1,n+1){
			cin >> arr[i];
		}
		double prob = 0;
		double hi = 1;
		double EPS = 1e-10;
		double lo = 0;
		int cnt = 0;
		while(hi - lo > EPS && cnt < 50){
			double mid = (lo +hi ) /2.0;
			if(pay(arr, b, mid, n) < 0){
				lo = mid;
			}
			else
				hi = mid;
			cnt++;
		}
		
		printf("Case #%i: %0.10lf\n",TC,hi);
	}
	
	return 0;
}
