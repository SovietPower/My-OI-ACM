/*
10236kb	364ms
̰�ģ�ÿ��ѡ��ֵ����һ�������������Ƚ���Ȼ����ѡ�ײ�ѡ����
�������ά��������̡�һ����ļ�ֵѡ�˾�û���ˣ�����ֻ��Ӱ����������ĵ㣬������DFS��+�߶����޸ġ��������ֵҲ�������߶�����
ÿ����ֻ�ᱻȡһ�Σ�����ֵҲֻ�ᱻ���һ�Ρ�����ÿѡһ�����ͱ�����������ֱ����һ����չ��ĵ㣬˳�����߶������޸ľ����������Ȩֵ�Ϳ����ˡ�
���Ӷ�$O((n+k)\log n)$��
ʵ���ϣ�ÿ����ֻ��ͳ��һ�Σ�����ѡ$k$����Ĳ��ཻ����������̬�Ǵ��ϵ��µģ���
���Կ����뵽�����ʷ֡���·��Ȩֵ����Ϊ��ȣ�ѡ���$k$�����������ˡ�
��`nth_element`�Ϳ��԰�����ĸ��Ӷ�Ҳʡ��233.
���Ը��Ӷ�$O(n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5;

int Enum,H[N],nxt[N],to[N],A[N],son[N],cnt;
LL mxd[N],val[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int v,int u)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
}
void DFS1(int x)
{
	LL mx=0;
	for(int i=H[x],v; i; i=nxt[i])
		DFS1(v=to[i]), mxd[v]>mx&&(mx=mxd[v],son[x]=v);
	mxd[x]=mx+A[x];
}
void DFS2(int x,int top)
{
	if(x==top) val[++cnt]=mxd[x];
	if(!son[x]) return;
	DFS2(son[x],top);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=son[x]) DFS2(to[i],to[i]);
}

int main()
{
	int n=read(),K=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	DFS1(1), DFS2(1,1);
	K=std::min(K,cnt), std::nth_element(val+1,val+cnt-K+1,val+1+cnt);
	LL ans=0;
	for(int i=cnt-K+1; i<=cnt; ++i) ans+=val[i];
	printf("%lld\n",ans);

	return 0;
}
