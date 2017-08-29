// Status: Accepted
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#define eps (1e-9)
#define ABOVE 1
#define BELOW 2
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define FORIT(it,s) for(__typeof(s.begin()) it=s.begin(); it!=s.end(); ++it)
using namespace std;
typedef double coord;

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

struct side{
	pt p1, p2;
	side() : p1(pt()), p2(pt()) {};
	side(coord x1,coord y1,coord x2,coord y2):p1(pt(x1,y1)),p2(pt(x2,y2)){};
};

bool operator==(const pt& p1, const pt& p2){
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator==(const side& s1, const side& s2){
	return s1.p1 == s2.p1 && s1.p2 == s2.p2;
}

bool operator!=(const side& s1, const side& s2){
	return !(s1==s2);
}

bool eq(double a, double b){
	return (abs(a-b)<eps);
}
// returns if a is less than b
bool lth(double a, double b){
	return (a<b-eps);
}

bool gth(double a, double b){ return lth(b,a); }

// returns if a is less or equal than b
bool leq(double a, double b){
	return (a<b+eps);
}

bool geq(double a, double b){ return leq(b,a); }

//   isHorizontal
bool isH(side s){
	return eq(s.p1.y,s.p2.y);
}

bool isV(side s){
	return eq(s.p1.x,s.p2.x);
}

side findSide(pt endpoint, side doesNotMatch, vector<side>& sides){
	FOR(i,0,sides.size()){
		if(endpoint == sides[i].p1 || endpoint == sides[i].p2){
			if(sides[i] != doesNotMatch)
				return sides[i];
		}
	}
}

vector<side> findSequence(vector<side>& sides){
	vector<side> seq;
	seq.push_back(sides[0]);
	side prev = sides[0];
	//int i = 1;
	int j = 1;
	while(seq.size()!=sides.size()){
		prev = seq[j-1];
		FOR(i,0,sides.size()){
			if(/*prev.p1 == sides[i].p1 || prev.p1 == sides[i].p2 || */prev.p2 == sides[i].p1 || prev.p2 == sides[i].p2){
				if(prev != sides[i] && sides[i] != seq[j-2]){
					seq.push_back(sides[i]);
					j++;
					break;
				}
			}
		}
	}
	return seq;
}

bool willWeAdd(pt p, pt endpoint, side doesNotMatch, vector<side>& sides, bool above){
	side otherSide = findSide(endpoint, doesNotMatch,sides);
	//cout << "We are checking whether the side ("<<otherSide.p1.x<<","<<otherSide.p1.y<<"),("<<otherSide.p2.x<<","<<otherSide.p2.y<<")"<<endl;
	bool above2 = geq(otherSide.p1.y,p.y) && geq(otherSide.p2.y,p.y);
	if(above2 == above) return true;
	else return false;
}

bool changeOfPos(int formerPos, pt p, pt newpt){
	if(formerPos == ABOVE)
		return p.y > newpt.y;
	return p.y < newpt.y;
}

bool sol(pt p, vector<side>& sides){
	int pos = sides[0].p1.y > p.y ? ABOVE : BELOW;
	int count = 0;
	FOR(i,0,sides.size()){

		side s = sides[i % sides.size()];
		cout << "testing the side that goes from "<<s.p1.x<<","<<s.p1.y<<" to "<<s.p2.x<<","<<s.p2.y<<endl;
		if(changeOfPos(pos,p,s.p2)){
			cout << "There was a change of position!"<<endl;
			pos = pos == ABOVE ? BELOW : ABOVE;
			if(s.p2.x < p.x){
				cout << "and that affected the count"<<endl;
				count++;
			}
		}
	}
	return count%2!=0;
}

bool crossesDown(pt p, side s){
	// if it starts below it, then ignore.
	if(geq(p.y, s.p1.y)) return false;
	// else we assume it starts above it.
	if(geq(p.y, s.p2.y)) return true;
	return false;
}

bool crossesUp(pt p, side s){
	// if it starts above it, then ignore.
	if(lth(p.y, s.p1.y)) return false;
	// else we assume it starts below it.
	if(lth(p.y, s.p2.y)) return true;
	return false;
}

bool sol2(pt p, vector<side>& sides){
	int pos = sides[0].p1.y > p.y ? ABOVE : BELOW;
	int numIntersects = 0;
	FOR(i,0,sides.size()){
		side s = sides[i];
		if(crossesUp(p,s) || crossesDown(p,s)){
			coord actualx = s.p1.x + (s.p2.x-s.p1.x)*((p.y-s.p1.y)/(s.p2.y-s.p1.y));
			if(gth(actualx, p.x))
				numIntersects++;
		}
	}
	return numIntersects%2==0 ? false : true;
}

bool isInside(pt p, vector<side>& sides){
	int numAbove = 0;
	int numIntersects = 0;
	int numCornerIntersects = 0;
	//cout << "we have a total of "<<sides.size()<< " sides"<< endl;
	FOR(i,0,sides.size()){
		side s = sides[i];
		//cout << endl <<"Checking the side with points ("<<s.p1.x<<","<<s.p1.y<<"), ("<<s.p2.x<<","<<s.p2.y<<")"<<endl;
		// Case 1: the line segment is entirely 'below' p
		if(lth(s.p1.y,p.y) && lth(s.p2.y,p.y)){
			//cout << "case1"<<endl;
			continue;
		}
		// Case 2: the line segment is entirely 'above' p
		if(gth(s.p1.y,p.y) && gth(s.p2.y,p.y)){
			//cout << "case2"<<endl;
			continue;
		}
		// Case 2.5: the line segment is vertical but the end is not the same y as p.y
		if(eq(s.p1.x,s.p2.x) && !eq(s.p1.y,p.y) && !eq(s.p2.y,p.y)){
			numIntersects++;
			continue;
		}
		// Case 3: the line segment is horizontal at y of p
		if(eq(s.p1.y,s.p2.y) && eq(s.p1.y,p.y)){
			//cout << "case3.";
			// Case 3.1: the line segment is before p
			if(leq(s.p1.x,p.x) && leq(s.p2.x,p.x)){
				numCornerIntersects+=2;
				//cout <<"1"<<endl;
			}
			//Case 3.2: the line segment is after p
			else{
				//cout <<"2"<<endl;
			}
		}
		else{
			//Case 4: the line segment is not horizontal and has an x at p.y
			//cout << "case4.";
			coord actualx = s.p1.x + (s.p2.x-s.p1.x)*((p.y-s.p1.y)/(s.p2.y-s.p1.y));
			if(eq(s.p1.x,s.p2.x)) actualx = s.p1.x;
			//cout <<"("<<actualx<<")";
			//Case 4.1: actualx is before x
			if(lth(actualx,p.x)){
				//cout << endl << "it turns out that "<<actualx<<"<"<<p.x<<endl;
				//cout <<"1.";

				//Case 4.1.1: actualx is also either s.p1.x or s.p2.x, but the segment is not vertical
				if(eq(actualx,s.p1.x)/* && !eq(s.p1.x,s.p2.x)*/){
					if(!willWeAdd(p,s.p1,s,sides,gth(s.p2.y,p.y))){
						if(eq(s.p1.x,s.p2.x))
							numIntersects++;
						else
							numCornerIntersects++;
					}
					//cout<<"1"<<endl;
				}
				else if(eq(actualx,s.p2.x)/*&& !eq(s.p1.x,s.p2.x)*/){
					if(!willWeAdd(p,s.p2,s,sides,gth(s.p1.y,p.y))){
						if(eq(s.p1.x,s.p2.x))
							numIntersects++;
						else
							numCornerIntersects++;
					}
					//cout<<"1"<<endl;
				}
				//Case 4.1.2: actualx is neither s.p1.x or s.p2.x
				else{ 
					//cout <<"2"<<endl;
					numIntersects++;
				}
			}
			//Case 4.2: actualx is after x
			else{
				//cout<<"2"<<endl;
			}
		}
		//cout << "as it stands: "<<numIntersects<<", "<<numCornerIntersects<<endl;
	}
	return (((numIntersects + numCornerIntersects/2)%2)!= 0 ? true : false);
}

int main(){
	int t,n,x1,x2,y1,y2,xim,yim; cin >> t;
	FOR(TC,1,t+1){
		cin >> xim >> yim >> n;
		
		pt impact = pt(xim,yim);
		
		vector<side> vs(n);
		FOR(i,0,n){
			cin >> x1 >> y1 >> x2 >> y2;
			vs[i] = (side(x1,y1,x2,y2));
			//cout << crossesUp(impact,vs[i]) << " " << crossesDown(impact,vs[i])<<endl;
		}
		
		
		vector<side> seq = findSequence(vs);
		/*FOR(i,0,n)
			cout << seq[i].p1.x << " "<<seq[i].p1.y<<" "<<seq[i].p2.x<<" "<<seq[i].p2.y<<endl;
		
		cout << endl;
		*/
		cout << "Case #" << TC << ": ";
		if(sol2(impact,seq)) cout << "jackpot" << endl;
		else cout << "too bad" << endl;
		
	}
	return 0;
}