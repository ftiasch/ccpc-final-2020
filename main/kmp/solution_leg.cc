#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=1;i<=n;++i)
#define N 2111111
char a[N],b[N];
int nxt[N],f[N];
int v[N],flag,base[N];
void getnxt(int n,char *a)
{
	int i,j;
	for(nxt[0]=j=(-1),i=1;i<n;nxt[i++]=j){
		while (~j&&a[j+1]!=a[i])j=nxt[j];
		if (a[j+1]==a[i])j++;
	}
}
void kmp(int n,char *a,int m,char *b)
{
	for(int i=0;i<m;i++)v[i]=0;
	int i,j;
	getnxt(n,a);
	for(j=-1,i=0;i<m;i++){
		while (~j&&a[j+1]!=b[i])j=nxt[j];
		if (a[j+1]==b[i])j++;
		if (j==n-1)
		{
			if (i-n>=0 && i!=m-1)v[i-n]=1;
			j=nxt[j];
			flag=1;
		}
	}
}
int dfs(int x)
{
	if (x==-1)return 0;
	if (f[x]!=-1)return f[x];
	if (v[x])return f[x]=x+1;
	return f[x]=dfs(nxt[x]);
}
char s[N];
int main()
{
	while (~scanf("%s%s",a,b))
	{
		int n=strlen(a);
		int m=strlen(b);
		for(int i=0;i<n;i++)s[i]=a[i];
		for(int i=0;i<m;i++)s[n+i]=b[i];
		getnxt(n+m,s);
		int now=n+m-1;
		while (now!=-1 && (now>=m||now>=n-1))now=nxt[now];
		for(int i=0;i<n;i++)base[i]=now+1;
		//for(int i=0;i<n;i++)cout<<base[i]<<" "; puts("");
		kmp(m,b,n,a);
		//for(int i=0;i<n;i++)cout<<v[i]<<" "; puts("");
		getnxt(n,a);
		//for(int i=0;i<n;i++)cout<<nxt[i]<<" "; puts("");
		for(int i=0;i<n;i++)f[i]=-1;
		for(int i=-1;i<n-1;i++)
		{
			if (i!=-1)putchar(' ');
			if (i==-1){ printf("%d",base[0]); continue; }
			dfs(i);
			if (f[i]==0)printf("%d",base[i]);
			else printf("%d",f[i]+m);
		}
		puts("");
	}
	return 0;
}
