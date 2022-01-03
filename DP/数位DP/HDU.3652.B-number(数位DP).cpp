/*
15MS 1520K
$Description$
求$1~n$中十进制表示包含"13"这个子串，且能整除13的数的个数。
$Solution$
数位DP: dp[位][s(pre/have13)][remainder],上界由DFS状态记录.
*/
#include <cstdio>

int n,A[13],f[13][3][13];
bool vis[13][3][13];

int DFS(int pos,int s,int mod,bool lim)
{
	if(!pos) return (s==2)&&(!mod);
	if(!lim && vis[pos][s][mod]) return f[pos][s][mod];
	int up=lim?A[pos]:9,res=0;
	for(int i=0; i<=up; ++i)
		if(s==2||(i==3&&s==1)) res+=DFS(pos-1,2,(mod*10+i)%13,i==up&&lim);
		else res+=DFS(pos-1,i==1?1:0,(mod*10+i)%13,i==up&&lim);
	if(!lim) vis[pos][s][mod]=1,f[pos][s][mod]=res;
	return res;
}
int Solve(int n)
{
	for(A[0]=0; n; n/=10) A[++A[0]]=n%10;
	return DFS(A[0],0,0,1);
}

int main()
{
	while(~scanf("%d",&n))
		printf("%d\n",Solve(n));
	return 0;
}
