// Status: Accepted
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

bool fixd[13];
vi v(13);

int c(char c){ return c - 'A' + 1; }
char i(int i){ return (i-1) + 'A';}

void readInput(){
	char buf[12];
	scanf("%s",buf);
	if(buf[4] != 'x'){
		fixd[c(buf[4])] = true;
		v[1] = c(buf[4]);
	}
	scanf("%s",buf);
	for(int i = 2, j = 1; i < 6; i++, j+=2){
		if(buf[j] != 'x'){
			fixd[c(buf[j])] = true;
			v[i] = c(buf[j]);
		}
	}
	scanf("%s",buf);
	if(buf[2] != 'x'){
		fixd[c(buf[2])] = true;
		v[6] = c(buf[2]);
	}
	if(buf[6] != 'x'){
		fixd[c(buf[6])] = true;
		v[7] = c(buf[6]);
	}
	scanf("%s",buf);
	for(int i = 8, j = 1; i < 12; i++, j+=2){
		if(buf[j] != 'x'){
			fixd[c(buf[j])] = true;
			v[i] = c(buf[j]);
		}
	}
	scanf("%s",buf);
	if(buf[4] != 'x'){
		fixd[c(buf[4])] = true;
		v[12] = c(buf[4]);
	}
}

bool solve(int i){
	// Check end points here
	if(i == 13){
		if(v[5]+v[7]+v[10]+v[12] == 26 && v[2]+v[6]+v[9]+v[12] == 26)
			return true;
		else return false;
	}
	else if(i == 12){
		if(v[1]+v[4]+v[7]+v[11] != 26) return false;
		if(v[8]+v[9]+v[10]+v[11] != 26) return false;
	}
	else if(i == 9){
		if(v[1]+v[3]+v[6]+v[8] != 26) return false;
	}
	else if(i == 6){
		if(v[2]+v[3]+v[4]+v[5] != 26) return false;
	}
	if(v[i] == -1){
		FOR(j,1,13){
			if(!fixd[j]){
				//cout << "Trying to place a " << j << " in v[" << i << "]" << endl;
				v[i] = j; fixd[j] = true;
				if(solve(i+1)) return true;
				v[i] = -1; fixd[j] = false;
			}
		}
	}
	else return solve(i+1);
	return false;
}

void printStar(){
	// Still have to call c() for each of v[i]
	printf("....%c....\n",i(v[1]));
	printf(".%c.%c.%c.%c.\n",i(v[2]),i(v[3]),i(v[4]),i(v[5]));
	printf("..%c...%c..\n",i(v[6]),i(v[7]));
	printf(".%c.%c.%c.%c.\n",i(v[8]),i(v[9]),i(v[10]),i(v[11]));
	printf("....%c....\n",i(v[12]));
}

int main(){
	int t; cin >> t;
	FOR(TC,1,t+1){
		v.clear();
		FOR(i,0,13){
			fixd[i] = false;
			v[i] = -1;
		}
		readInput();
		solve(1);
		/*FOR(i,1,13){
			cout << v[i] << " ";
		}*/
		cout << "Case #" << TC << ":"<<endl;
		printStar();
	}
	return 0;
}