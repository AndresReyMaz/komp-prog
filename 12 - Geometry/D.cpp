// Status: Accepted
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#define eps (1e-9)
#define ABOVE 1
#define BELOW 2
#define oo 100000000
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
using namespace std;
typedef int coord;

struct pt{
	coord x,y;
	pt() : x(0), y(0){};
	pt(coord _x, coord _y) : x(_x), y(_y){};
	pt operator+(const pt& p){
		return pt(x+p.x,y+p.y);
	}
	pt operator-(const pt& p){
		return pt(x-p.x,y-p.y);
	}
	coord operator*(const pt& p){
		return x*p.x+y*p.y;
	}
};

bool operator<(const pt& p,const pt& p1){
	pair<coord,coord> b = make_pair(p.x,p.y);
	pair<coord,coord> a = make_pair(p1.x,p1.y);
	return a<b;
}

struct side{
	pt p1, p2;
	side() : p1(pt()), p2(pt()) {};
	side(coord x1,coord y1,coord x2,coord y2):p1(pt(x1,y1)),p2(pt(x2,y2)){};
};

pt intrsct(side v, side h){
	if(v.p1.y >= h.p1.y && v.p2.y >= h.p1.y) return pt(oo,0);
	if(v.p1.y <= h.p1.y && v.p2.y <= h.p1.y) return pt(oo,0);
	if(h.p1.x >= v.p1.x && h.p2.x >= v.p1.x) return pt(oo,0);
	if(h.p1.x <= v.p1.x && h.p2.x <= v.p1.x) return pt(oo,0);
	return pt(v.p1.x,h.p1.y);
}

set<pt> sol(vector<side>& vs,vector<side>& hs){
	set<pt> ans;
	FOR(i,0,vs.size()){
		FOR(j,0,hs.size()){
			//cout << "Checking"<<endl;
			pt p = intrsct(vs[i],hs[j]);
			//cout << "the answer is "<<p.x << ", "<< p.y<<endl;
			if(p.x != oo)
				ans.insert(p);
		}
	}
	return ans;
}

int main(){
	int t,n; cin >> t;
	FOR(TC,1,t+1){
		cin >> n;
		coord x1,x2,y1,y2;
		vector<side> vs;
		vector<side> hs;
		FOR(i,0,n){
			cin >> x1 >> y1 >> x2 >> y2;
			if(x1 == x2) // side is vertical
				vs.push_back(side(x1,y1,x2,y2));
			else
				hs.push_back(side(x1,y1,x2,y2));
		}
		cout << "Case #" << TC << ":" << endl;
		set<pt> st = sol(vs,hs);
		for(auto it = st.begin(); it != st.end(); ++it)
			cout << (*it).x << " " << (*it).y << endl;
	}
	return 0;
}