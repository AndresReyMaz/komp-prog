// Status: Accepted
#include <iostream>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
using namespace std;

int main(){
	int t,e,f,c,total,drank=0; cin >> t;
	FOR(TC,1,t+1){
		drank=0;
		cin >> e >> f >> c;
		total = e+f;
		while(total>=c){//While Tim can still buy soda
			drank += total/c;
			total = total/c + total%c;
		}
		cout << "Case #"<< TC<< ": " << drank << endl;
	}
	return 0;
}
