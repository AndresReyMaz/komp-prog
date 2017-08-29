// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++)
#define RIGHT '9'
#define DOWN '1'
#define RD '3'
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;

/*
 * The words are all kept in a matrix where
 * the column is the length of the word and
 * the row is the (i-1)th word of that length 
 * that we have received so far.
 * 
 * The total count of words of each length are
 * kept in the array n[].
 * 
 */ 
char cw[260][260];
int p[260][260];//protected
int rght[260][260];
int down[260][260];
int n[260];
string words[203][260];
int rows=0,cols=0,am=0;


// Returns true if the cell is the start of a word going down.
bool dstrt(int i, int j){
	return (i+1 != rows && cw[i+1][j] != '+' && cw[i+1][j] != DOWN && cw[i+1][j] != RD);
}

// Returns true if the cell is the start of a word going right.
bool rstrt(int i, int j){
	return (j+1 != cols && cw[i][j+1] != '+' && cw[i][j+1] != RIGHT && cw[i][j+1] != RD);
}

// Returns the length of the word starting at (i,j) with direction dir.
int gsize(char dir, int i, int j){
	int idif = 1, jdif = 0;
	if(dir == RIGHT)
		swap(idif,jdif);
	int cnt = 0;
	while(i < rows && j < cols && cw[i][j] != '+'){
		cnt++;
		if(cw[i][j] == '_')
			cw[i][j] = dir;
		else cw[i][j] = RD;
		i+=idif;
		j+=jdif;
	}
	return cnt;
}

// Reads the input
void input(){
	cin >> cols >> rows >> am;
	char c;
	memset(rght,0,sizeof(rght));
	memset(down,0,sizeof(down));
	memset(p,0,sizeof(p));
	memset(n,0,sizeof(n));
	FOR(i,0,rows){
		FOR(j,0,cols){
			cin >> c;
			cw[i][j] = c;
		}
	}
	FOR(i,0,rows){
		FOR(j,0,cols){
			if(cw[i][j] != '+'){
				if(dstrt(i,j)){
					down[i][j] = gsize(DOWN, i, j);
					
				}
				if(rstrt(i,j)){
					rght[i][j] = gsize(RIGHT, i, j);
					
				}
			}
		}
	}
	string in;
	FOR(i,0,am){
		cin >> in;
		int l = in.length();
		words[n[l]][l] = in;
		n[l]++;
		
	}
}

void remWord(int dir, int i, int j, int l){
	// OK MAKE TWO CASES
	if(dir == RIGHT){
		while(l--){
			p[i][j]--;
			if(p[i][j] <= 0)
				cw[i][j] = RIGHT;
			j++;
		}
	}
	else{// DOWN
		while(l--){
			p[i][j]--;
			if(p[i][j] <= 0)
				cw[i][j] = DOWN;
			i++;
		}
	}
}

// Tries to place down word there and returns success/failure
bool placeWord(int dir, int i, int j, string w){
	int idif = 1, jdif = 0;
	if(dir == RIGHT)
		swap(idif,jdif);
	int cptr = 0, l = w.length();
	string orspaces = "";
	while(cptr < l){
		if(isalpha(cw[i][j]) && cw[i][j] !=  w[cptr])// Found a letter already there that doesn't match for this word
			break;
		orspaces += cw[i][j];
		cw[i][j] = w[cptr];
		i+=idif;
		j+=jdif;
		cptr++;
	}
	if(cptr == l) return true;
	// Erasing word
	while(cptr > 0){
		cptr--;
		i-=idif;
		j-=jdif;
		cw[i][j] = orspaces[cptr];
	}
	return false;
}

// Adds 1 to the 'protected' field.
void makep(int dir, int i, int j, int l){
	int idif = 1, jdif = 0;
	if(dir == RIGHT)
		swap(idif,jdif);
	while(l--){
		p[i][j]++;
		i+=idif;
		j+=jdif;
	}
}

void printgrid(){
	//cout << endl;
	FOR(i,0,rows){
		FOR(j,0,cols)
			cout << cw[i][j];
		cout << endl;
	}
	cout << endl;
}

bool solve(int i, int j){
	if(i == rows - 1 && j == cols -1) return true; // reached end of crossword board
	if(j == cols) return solve(i+1,0);// Reached end of row
	if(down[i][j] != 0 && rght[i][j] != 0){
		// SPECIAL CASE: two words start here
		FOR(w,0,n[down[i][j]]){
			// Try this word
			if(placeWord(DOWN, i, j, words[w][down[i][j]])){
				makep(DOWN,i,j,words[w][down[i][j]].length());
				FOR(w2,0,n[rght[i][j]]){
					if(placeWord(RIGHT, i, j, words[w2][rght[i][j]])){
						//cout << "WORDS PLACED SUCCESSFULLY" << endl;
						//printgrid();
						makep(RIGHT,i,j,words[w2][rght[i][j]].length());
						if(solve(i,j+1)) return true;
						remWord(RIGHT,i,j,words[w2][rght[i][j]].length());
					}
				
				}
				remWord(DOWN,i,j,words[w][down[i][j]].length());
				//printgrid();
			}
		}
	}
	else if(down[i][j] != 0){
		//cout << "We need a word of length="<<down[i][j] << endl; 
		// Iterate thru all possible words
		FOR(w,0,n[down[i][j]]){
			//string curw = words[w][down[i][j]];
			//cout << "Trying with word " << curw << endl;
			//cout << "TRYING TO PLACE WORD DOWN HERE" << endl;
			if(placeWord(DOWN, i, j, words[w][down[i][j]])){
				//cout << "WORD PLACED SUCCESSFULLY" << endl;
				//printgrid();
				makep(DOWN,i,j,words[w][down[i][j]].length());
				if(solve(i,j+1)) return true;
				//cout << "REMOVING WORD" << endl;
				remWord(DOWN,i,j,words[w][down[i][j]].length());
				//printgrid();
			}
		}
		return false;
	}
	else if(rght[i][j] != 0){
		FOR(w,0,n[rght[i][j]]){
			// Now check for spaces going right
			//cout << "TRYING TO PLACE WORD RIGHT HERE" << endl;
			if(placeWord(RIGHT, i, j, words[w][rght[i][j]])){
				//cout << "WORD PLACED SUCCESSFULLY" << endl;
				//printgrid();
				makep(RIGHT,i,j,words[w][rght[i][j]].length());
				if(solve(i,j+1)) return true;
				//cout << "REMOVING WORD" << endl;
				
				remWord(RIGHT,i,j,words[w][rght[i][j]].length());
				//printgrid();
			}
		}
		return false;
	}
	else return solve(i,j+1);
	return false;
}

void printall(){
	FOR(i,0,rows){
		FOR(j,0,cols)
			cout << cw[i][j];
		cout << endl;
	}
	cout << endl;
	FOR(i,0,rows){
		FOR(j,0,cols)
			cout << rght[i][j];
		cout << endl;
	}
	cout << endl;
	FOR(i,0,rows){
		FOR(j,0,cols)
			cout << down[i][j];
		cout << endl;
	}
}

int main(){
	int t; cin >> t;
	FOR(TC,1,t+1){
		input();
		solve(0,0);
		cout << "Case #" << TC << ":" <<endl;
		printgrid();
		
	}
}
