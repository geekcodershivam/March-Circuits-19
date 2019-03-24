#include<bits/stdc++.h>
#define lli long long int
using namespace std;

bool sieve[31640] = {0};
vector<int> primes;

/**
 * Using Sieve of Eratosthenes to find all primes
 * upto sqrt(10^9).
 *
 * Constant time = O(31640)
 */
void preprocess()
{
	primes.push_back(2);
	for(int i=3; i<31640; i+=2)
	{
		if(sieve[i] == 0)
		{
			primes.push_back(i);
			for(int j=i+i; j<31640; j+=i)
				sieve[j] = 1;
		}
	}
}

/**
 * Find Prime Factorization of n.
 */
vector<pair<int, int> > prime_factorization(int n)
{
	vector<pair<int, int> > ans;
	for(int i=0;i<primes.size() and n!=1; i++)
	{
		int count = 0;
		while( n % primes[i] == 0)
		{
			n /= primes[i];
			count ++;
		}
		if(count != 0)
			ans.push_back({primes[i], count});
	}
	if(n != 1)
		ans.push_back({n, 1});
	return ans;
}


/**
 * Find Prime Factorization of n.
 */
vector<pair<int, int> > prime_factorization_without_sieve(int n)
{
	vector<pair<int, int> > ans;
	int count = 0;
	while( n % 2 == 0)
	{
		n /= 2;
		count++;
	}
	if(count != 0)
		ans.push_back({2, count});


	for(int i=3; i<=sqrt(n); i+=2)
	{
		int count = 0;
		while( n % i == 0)
		{
			n /= i;
			count++;
		}
		if(count != 0)
			ans.push_back({i, count});

	}

	if(n != 1)
		ans.push_back({n, 1});
	return ans;
}

/** 
 * Returns highest power of prime p that divides x!
 */
lli highest_power_of_p(lli p, lli x)
{
	lli ans = 0;

	// Calculate ans = x/p + x/(p^2) + x/(p^3) + .... 
	while(x)
	{
		x/=p;
		ans+=x;
	}
	return ans;
}

int main()
{
	cin.sync_with_stdio(false);
	// preprocess();
	lli t, n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		vector<pair<int, int>> factors = prime_factorization_without_sieve(n+1);
		bool possible = true;
		for(auto factor: factors)
		{
			lli p = factor.first;
			lli power = factor.second;

			if( p == 2)
				power--;

			lli hpp = highest_power_of_p(p, n-1);
			if(hpp < power)
			{
				possible = false;
				break;
			}

		}
		if(possible)
			cout<<"YES"<<"\n";
		else
			cout<<"NO"<<"\n";
	}

}