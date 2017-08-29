// Status: Accepted
#include <iostream>
#include <string>
#include <utility>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
#define MAXC 10005
#define MAXN 105
#define oo 1000000000
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;

int n;

struct farmer{
	int iq;
	int w;
	farmer(int i, int we) : iq(i), w(we) { }
};

bool cmp(const farmer &f1, const farmer &f2){
	if(f1.iq == f2.iq) return f1.w > f2.w;
	return f1.iq < f2.iq;
}

int solve(vector<farmer> &vf){
	vector<farmer> a;
	FOR(i,0,n) a.push_back(farmer(-1,-1));
	int ans = 1;
	a[0] = vf[0];
	//cout << "So far so good " << endl;
	for(vector<farmer>::iterator i = vf.begin()+1; i != vf.end(); i++){
		if((*i).w > a[0].w)// 
			a[0] = *i;
		else if((*i).w < a[ans-1].w){\
			//cout << "Hey guess what it's true that (" << (*i).iq <<"," <<(*i).w<<") > ("<<a[ans-1].iq<<","<<a[ans-1].w<<")"<<endl;
			//cout << "DEBUG2" << endl;
			a[ans++] = *i;
		}
		else{
			//cout << "Else runs " << endl;
			int lo = -1, hi = ans - 1;
			while(hi-lo > 1){
				int m = lo+(hi-lo)/2;
				if((*i).w > vf[m].w) // i <= vf[m]
					hi = m;
				else
					lo = m;
			}
			a[hi] = *i;
		}
	}
	return ans;
}

vi LIS(vi A){
	int N = A.size();
	vi pre(N,-1),erg;
	map<int,int> m;
	map<int,int>::iterator k,l;
	FOR(i, 0,N) if(m.insert(pii(A[i],i)).second) {
		l = k = m.find(A[i]);
		if(l == m.begin()) pre[i] = -1;
		else pre[i] = (--l)->second;
		if((++k)!=m.end()) m.erase(k);
	}
	for(int j = (--(k = m.end()))->second;j!=-1;j=pre[j])
		erg.push_back(A[j]);
	return erg;
}


int main(){
	int t,iq,w; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		vector<farmer> vf;
		FOR(i,0,n){
			cin >> iq >> w;
			vf.push_back(farmer(iq,w));
		}
		sort(all(vf),cmp);
		/*FOR(i,0,n){
			cout << vf[i].iq << " & "<< vf[i].w << endl;
		}*/
		vi myvect;
		for(int i = n-1; i >= 0; i--){
			myvect.push_back(vf[i].w);
		}
		cout << "Case #" << TC << ": "<<LIS(myvect).size() << endl;
	}
	return 0;
}
