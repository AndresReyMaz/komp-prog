// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;

void printSol(const map<string,int> &nating, const map<string,int> &foring, const map<pair<string,string>,int> &pairs){
	//map<pair<string,string>,int>::iterator it1;
	for(auto it1 = pairs.begin(); it1 != pairs.end(); it1++){
		pair<string,string> p = it1->first;
		auto it2 = foring.find(p.first);
		int cf = it2->second;
		auto it3 = nating.find(p.second);
		int cn = it3->second;
		if(cn == cf && cn == it1->second){
			cout << "(" << (p.first) << ", " << (p.second) << ")" << endl;
		}
	}
}

int main(){
	int t,n,m; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		map <string,int> foring, nating;
		map <pair<string, string>, int> pairs;
		FOR(pz,0,n){
			string s; cin >> s;
			cin >> m;
			vector<string> tmp;
			FOR(i,0,m){
				//Reading foreign language ingredients
				cin >> s;
				tmp.push_back(s);
				
				map<string,int>::iterator it = foring.find(s);
				if (it != foring.end()){
					(it->second)++;
				}
				else{
					//Adding foreign language ingredient to map
					foring[s] = 1;
				}
			}
			cin >> m;
			FOR(i,0,m){
				//Reading native language ingredients
				cin >> s;
				map<string,int>::iterator it = nating.find(s);
				if (it != nating.end()){
					(it->second)++;
				}
				else{
					//Adding native language ingredient to map
					nating[s] = 1;
				}
				//Checking if pair exists; if not, creating; if so, adding 1 to occurrence count.
				FOR(k,0,tmp.size()){
					map <pair<string, string>, int>::iterator it = pairs.find(make_pair(tmp[k],s));
					if(it != pairs.end())
						(it->second)++;
					else
						pairs[make_pair(tmp[k],s)] = 1;
				}
			}
		}
		cout << "Case #" << TC << ": " << endl;
		printSol(nating,foring,pairs);
	}
	return 0;
}
