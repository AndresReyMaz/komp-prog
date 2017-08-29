// Status: Time Limit Exceeded
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


int n,m;

struct rng{
	int vs, ve;
	int size; //in slots
	int loc;
	rng(int s, int e, int l) : vs(s), ve(e), loc(l), size((ve-vs) + 1){}
};

vector<rng> stck;
int qry(int x){
	if(x > n || x < 1) return -1;
	if(stck[0].vs == x) return 0;
	int rloc = 0, ans = -2;
	vector<rng>::iterator it;
	for(it = stck.begin(); it < stck.end(); it++){
		bool found = false;
		rng i = *it;
		if((*it).vs == (*it).ve && (*it).vs == x){
			//Single value found
			rng tmp((*it).vs,(*it).ve,(*it).loc);
			stck.erase(it);
			stck.insert(stck.begin(),tmp);
			return rloc;
		}
		else if((*it).vs == x){
			//Value found at start
			found = true;
			(*it).vs++;
			(*it).size--;
			ans = rloc;
		}
		else if((*it).ve == x){
			//Value found at end

			found = true;
			(*it).ve--;
			(*it).size--;
			ans = rloc + (*it).size;
		}
		else if((*it).vs < x && (*it).ve > x){
			//Value found in middle somewhere
			found = true;
			ans = rloc + (x-(*it).vs);
			int tmpve = (*it).ve;
			(*it).ve = x - 1;
			(*it).size = (*it).ve - (*it).vs + 1;
			rng sndhlf(x+1,tmpve,0);
			if(it+1 == stck.end())
				stck.push_back(sndhlf);
			else
				stck.insert(it+1, sndhlf);

		}

		// Adding new element
		if(found){
			rng tmp(x,x,0);
			stck.insert(stck.begin(),tmp);
			return ans;
		}
		rloc += (*it).size;
	}
	return -1;
}



int main(){
	int t,in; cin >> t;
	FOR(TC,1,t+1){
		cin >> n >> m;
		stck.clear();
		stck.push_back(rng(1,n,0));
		FOR(k,0,m){
			cin >> in;
			/*for(rng i : stck){
				printf("rng[%i,%i] has size %i\n",i.vs,i.ve,i.size);
			}*/
			cout << qry(in) << " ";
		}
		cout << endl;
	}
	return 0;
}