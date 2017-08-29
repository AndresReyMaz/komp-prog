// Status: Accepted
#include <iostream>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;

char m[500][500];
bool vdie[500][500];
bool vdots[500][500];
int w,h;

bool inlims(int i, int j){
	return i >= 0 && i < h && j >= 0 && j < w;
}

void analyzedot(int i, int j){
	vdots[i][j] = true;
	vdie[i][j] = true;
	//we just have to mark entire dot as visited
	j--;
	if(inlims(i,j) && m[i][j] == 'X' && !vdots[i][j])
		analyzedot(i,j);
	j++; i--;
	if(inlims(i,j) && m[i][j] == 'X' && !vdots[i][j])
		analyzedot(i,j);
	j++; i++;
	if(inlims(i,j) && m[i][j] == 'X' && !vdots[i][j])
		analyzedot(i,j);
	j--; i++;
	if(inlims(i,j) && m[i][j] == 'X' && !vdots[i][j])
		analyzedot(i,j);
}

int analyzedie(int i, int j){
	vdie[i][j] = true;
	int cnt= 0;
	if(m[i][j] == 'X' && !vdots[i][j]){
		analyzedot(i,j);
		cnt++;
	}
	//check left
	j--;
	if(inlims(i,j) && m[i][j] != '.' && !vdie[i][j]){
		cnt+=analyzedie(i,j);
	}
	//check up
	j++; i--;
	if(inlims(i,j) && m[i][j] != '.' && !vdie[i][j]){
		cnt+=analyzedie(i,j);
	}
	//check right
	j++; i++;
	if(inlims(i,j) && m[i][j] != '.' && !vdie[i][j]){
		cnt+=analyzedie(i,j);
	}
	//check down
	j--; i++;
	if(inlims(i,j) && m[i][j] != '.' && !vdie[i][j]){
		cnt+=analyzedie(i,j);
	}
	return cnt;
}

int main()
{
	

	int t; cin >> t;
	char c;
	
	vi ans;
	
	
	FOR(TC,1,t+1){
		ans.clear();
		cin >> w >> h;
		FOR(i,0,h){ FOR(j,0,w){//reading the image
			cin >> c;
			m[i][j]=c;
			vdie[i][j]=vdots[i][j]=0;
		}}
		/*FOR(i,0,h){ FOR(j,0,w){
			cout << m[i][j];
		}
		cout << endl;}*/
		FOR(i,0,h){ FOR(j,0,w){
			if(m[i][j] != '.' && !vdie[i][j]){//Enter analyze mode
				ans.push_back(analyzedie(i,j));
				
			}
		}}
		sort(all(ans));
		cout << "Case #" << TC << ":";
		FOR(i,0,ans.size()){
			cout << " " << ans[i];
		}
		cout << endl;
	}


	
	return 0;
}

