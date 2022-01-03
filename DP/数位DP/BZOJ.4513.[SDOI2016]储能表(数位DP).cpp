/*
828kb	1532ms
�����ַ֣����$k=0$��������$\sum_{i=0}^n\sum_{j=0}^mi\ \mathbb{xor}\ j$��������ݷ�Χ������λDP������ʵͳ��һ��$\leq n$��$\leq m$��ÿλΪ$1$�����ж��ٸ�������...��
�������[�ֽ���������Ӫ������ D.The Easiest One]��û����Ҳ�У����Ϳ����뵽ö��ÿһλ��ʱ��ͬʱö��$x,y$��һλѡɶ������һ�¹��׾����ˡ�
����$k$�����ƣ�ͬ����$k$�����Ʒֽ⣬ת��ʱ��һ�������ǰ$<k$ʱ`continue`������...
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define gc() getchar()
typedef long long LL;
const int N=66,INF=1e9+7;

int P,bitx[N],bity[N],bitk[N];
LL pw[N];
pr f[N][8];
bool vis[N][8];

inline LL read()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
pr DFS(int x,int s)//pair(�ͣ�������)
{//0:==k 1:>k
	if(x==-1) return mp(0,1);
	if(vis[x][s]) return f[x][s];
	int upx=s&1?bitx[x]:1, upy=s&2?bity[x]:1, sk=s&4;
	LL f1=0,f2=0;
	for(int i=0; i<=upx; ++i)
		for(int j=0; j<=upy; ++j)
		{
			int val=(i^j)-bitk[x];
			if(!sk && val<0) continue;
			pr v=DFS(x-1,(s&1&&i==upx)|((s&2&&j==upy)<<1)|((sk||val>0)<<2));
			if(val) f1+=val*pw[x]*v.second%P;
			f1+=v.first, f2+=v.second;
		}
	return vis[x][s]=1,f[x][s]=mp((f1%P+P)%P,f2%P);
}
void Calc(LL x,LL y,LL k)
{
	memset(vis,0,sizeof vis);
	memset(bitx,0,sizeof bitx);
	memset(bity,0,sizeof bity);
	memset(bitk,0,sizeof bitk);
	int t1=0,t2=0,t3=0;
	for(; x; x>>=1) bitx[t1++]=x&1;
	for(; y; y>>=1) bity[t2++]=y&1;
	for(; k; k>>=1) bitk[t3++]=k&1;
	printf("%d\n",DFS(std::max(t1,std::max(t2,t3))-1,3).first);
}

int main()
{
	freopen("table.in","r",stdin);
	freopen("table.out","w",stdout);

	for(int T=read(); T--; )
	{
		LL n=read()-1,m=read()-1,K=read(); int P=read(); ::P=P;
		for(int i=0; i<63; ++i) pw[i]=(1ll<<i)%P;
		Calc(n,m,K);
	}

	return 0;
}
