// Status: Accepted
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath> 
using namespace std;

int main(){
double x1,x2,x3,y1,y2,y3,r,a,b,c,A,ans,calcr;
cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> r;
a = sqrt(pow(x3-x2,2)+pow(y3-y2,2));
b = sqrt(pow(x3-x1,2)+pow(y3-y1,2));
c = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
A = sqrt(4*a*a*b*b-pow(a*a+b*b-c*c,2))/4;
calcr = A / ((a+b+c)/2);



if(calcr > r) ans = (calcr - r)/r;
else if(calcr < r) ans = (calcr - r)/r;
else ans = 0 ;
ans*=100;
//cout << a << " " << b << " " << c << endl;
//cout << calcr << " and " << r << endl;
cout << fixed << setprecision(7) << ans << endl;
return 0;
}
