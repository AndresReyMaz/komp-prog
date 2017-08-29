// Status: Accepted
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
#define FOR(i,a,b) for(int i = (a); i < b; i++) 
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int arrptr;

struct btree{
	btree *left, *right;
	char val;
	btree(int v) : val(v), left(NULL), right(NULL) { }
};


btree *parseTree(string s){
	stack<btree*> pStack;
	btree *root = new btree(' ');
	pStack.push(root);
	btree *curTree = root;
	int sl = s.length();
	FOR(i,0,sl){
		if(s[i] == '('){
			curTree->left = new btree(' ');
			pStack.push(curTree);
			curTree = (curTree->left);
		}
		else if(isalpha(s[i])){
			curTree->val = s[i];
			btree *parent = pStack.top();pStack.pop();
			curTree = parent;
		}
		else if(s[i] == ')'){
			curTree = pStack.top();pStack.pop();
		}
		else{//is operator
			curTree->val = s[i];
			curTree->right = new btree(' ');
			pStack.push(curTree);
			curTree = (curTree->right);
		}
	}
	return root;
}
/*
void inOrder(btree *tree){
	if(tree == NULL) return;
	if(tree->val == ' '){
		cout << "tree = ";
	}
	else if(isalpha(tree->val)){
		cout << (tree->val);
	}
	else{
		cout << (tree->val);
	}
	inOrder(tree->left);
	inOrder(tree->right);
}
*/
ll solve(const vi &A,btree *tree){
	if(tree == NULL){
		//cout << "ERROR IN THE TREE" << endl;
		return -10000;
	}
	if(isalpha(tree->val)){
		ll ret = A[arrptr];
		arrptr++;
		return ret;
	}
	if(tree->val == '+'){
		return solve(A,tree->left) + solve(A,tree->right);
	}
	else if(tree->val == '*'){
		return solve(A,tree->left) * solve(A,tree->right);
	}
	else if(tree->val == '-'){
		return solve(A,tree->left) - solve(A,tree->right);
	}
}

int main(){
	int t,n,in,l; cin >> t;
	ll m;
	FOR(TC,1,t+1){
		//Reading input
		cin >> n;
		vi A(n);
		FOR(i,0,n){
			cin >>in;
			A[i] = in;
		}
		cin >> m;
		string ans="NO",ln;
		cin >> ln;
		btree *tree = parseTree(ln);
		//inOrder(tree);
		//cout << endl;
		l = ln.size();
		if(n == 1 && A[0] == m){
			ans = "YES";
		}
		else{
			sort(A.begin(),A.end());
			do{
				arrptr = 0;
				if(solve(A,tree) == m){
					ans = "YES";
					break;
				}
			} while(next_permutation(A.begin(),A.end()));
		}
		cout << "Case #" << TC << ": " << ans << endl;
	}
	return 0;
}
