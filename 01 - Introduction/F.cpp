// Status: Accepted
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;



int main(){
	int P,K,p,q; cin >> P;
	while(P--){
		scanf("%i %i/%i",&K,&p,&q);
		if(q == 1){
			q = p +1;
			p = 1;
		}
		else if (q == 2){
			q = p;
			p = 2;
		}
		else if(p < q){
			int tmp = q;
			q = q - p;
			p = tmp;
		}
		else if(p>q){
			int dep = 0;
			while(p > q){
				dep++;
				p = p-q;
			}
			if(q == 1){
				q = p +1;
				p = 1;
			}
			else if (q == 2){
				q = p;
				p = 2;
			}
			else if(p < q){
				int tmp = q;
				q = q - p;
				p = tmp;
			}
			q += p * dep;
		}
		printf("%i %i/%i\n",K,p,q);
	}
	return 0;
}