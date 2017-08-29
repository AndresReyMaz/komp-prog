// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;

int n,m;

bool pairCompare(const pair<int, double>& firstElem, const pair<int,double>& secondElem) {
  return firstElem.second < secondElem.second;

}
int main(){
	cin >> n >> m;
	vector<pair<int, double> > dishes;
	string a;
	int s; double t;
	FOR(i,0,n){
		cin >> a >> s >> t;
		dishes.push_back(make_pair(s,t));
	}
	sort(all(dishes),pairCompare);
	//cout << "sorted dishes are " << endl;

	double cnt = 0.0;
	for(int i = n-1; i >= 0; i--){
		if(m == 0) break;
		if(dishes[i].first <= m){
			// Take all of this plate
			cnt += ((double)dishes[i].first) * dishes[i].second;
			m -= dishes[i].first;
		}
		else{
			cnt += ((double)m) * dishes[i].second;
			break;
		}
	} 
	printf("%.7lf\n",cnt);
	return 0;
}
