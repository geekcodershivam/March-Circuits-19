#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x,y,w;
    int xmax=-1000000,xmin=1000000;
    int ymax=-1000000,ymin=1000000;
    long int xsum=0,ysum=0;
    cin >> n;
    for(int i=0;i<n;i++){
        
        cin >> x>> y >> w;
        xsum+=x;
        ysum+=y;
        if(x>xmax)
        xmax=x;
        if(y>ymax)
        ymax=y;
        if(x<xmin)
        xmin=x;
        if(y<ymin)
        ymin=y;
    }
    // cout<< xmax;
    // cout<<endl;
    // cout<<ymax<<" "<<xmin << " "<<ymin;
    int xx=(xsum)/n;
    int yy=(ysum)/n;
    int r=abs(((xmax+xmin)/2)+((ymax+ymin)/2));
    cout<< xx<<" "<<yy <<" "<< r <<"\n";
    
}