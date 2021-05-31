#include <bits/stdc++.h>
using namespace std;
int n;
int a[100];
long long f[100];
int main()
{
	while (~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		long long ans=0;
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		if (a[i]>a[j])ans++;
		
		for(int i=1;i<=n;i++)
		{
			f[i]=1;
			for(int j=1;j<i;j++)
			if (a[i]>a[j])f[i]+=f[j];
			ans+=f[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
