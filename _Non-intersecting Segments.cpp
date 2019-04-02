#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
int n;
bool fn(vector<ll> v1,vector<ll> v2)
{
	if(v1[1]==v2[1])
		return v1[0]<v2[0];
	else
		return v1[1]<v2[1];
}
int main()
{
	cin>>n;
	vector<ll>vect[n];
	for(int i=0;i<n;++i)
	{
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		vect[i].push_back(a);
		vect[i].push_back(b);
		vect[i].push_back(c);
		vect[i].push_back(d);
	}
	sort(vect,vect+n,fn);
	//for(int i=0;i<n;i++)
	//	cout<<vect[i][0]<<" "<<vect[i][1]<<endl;
	ll arr[n+1];
	int flag=1;
	if(n>1)
	{
		if(vect[0][1]==vect[1][1])
		flag=0;
	}
	for(int i=0;i<n;++i)
	{
		if(flag==1)
		    arr[i]=vect[i][3];
		else
			arr[i]=vect[i][2];
	}
	vector<ll> d(n+1,10000000000);
	for (int i=0;i<n;++i)
	{
		*lower_bound(d.begin(),d.end(),arr[i])=arr[i];
	}
	for (int i=0;i<=n;++i)
	{
		if (d[i]==10000000000)
		{
			cout<<i;return 0;}
		}