//求三堆石子的SG函数，异或起来就是整个游戏的SG值 
#include <cstdio>
#include <cstring>
const int N=1005;

int n,m,p,cnt,F[N],sg[N+2];
bool vis[N+2];

void Init()
{
	F[0]=F[1]=1;
	for(cnt=2; F[cnt-1]<N*2; ++cnt) F[cnt]=F[cnt-2]+F[cnt-1];
	for(int i=1; i<N; ++i)
	{
		memset(vis,0,sizeof vis);
		for(int j=1; F[j]<=i; ++j)
			vis[sg[i-F[j]]]=1;//所有后继的sg值的mex 
		for(int j=0; ; ++j)
			if(!vis[j]) {sg[i]=j; break;}
	}
}

int main()
{
	Init();
	while(scanf("%d%d%d",&n,&m,&p),n&&m&&p)
		puts(sg[n]^sg[m]^sg[p]?"Fibo":"Nacci");
	return 0;
}
