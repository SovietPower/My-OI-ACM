#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=30;

int cnt,bit[N];
LL f[N][5];
bool vis[N][5];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
LL DFS(int x,bool lim,int t)
{
	if(t>3) return 0;
	if(!x) return t<=3;
	if(!lim&&vis[x][t]) return f[x][t];
	LL res=0; int up=lim?bit[x]:9;
	for(int i=0; i<=up; ++i)
		res+=DFS(x-1,lim&&i==up,t+(i!=0));
	if(!lim) vis[x][t]=1, f[x][t]=res;
	return res;
}
LL Calc(LL x)
{
	memset(vis,0,sizeof vis);
	cnt=0;
	for(LL v=x; v; v/=10) bit[++cnt]=v%10;
	return DFS(cnt,1,0);
}

int main()
{
	LL l,r;
	for(int T=read(); T--; l=read(),r=read(),printf("%I64d\n",Calc(r)-Calc(l-1)));
	return 0;
}
