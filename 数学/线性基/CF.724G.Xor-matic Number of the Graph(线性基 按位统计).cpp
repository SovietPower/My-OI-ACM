/*
343ms	11200KB
$Description$
����һ�Ŵ���Ȩ����ͼ��������u->v��һ��·��ʹ�þ����ߵı�Ȩ����Ϊs����Ȩ�����Σ������(u,v,s)Ϊinteresting triple��
��ͼ������interesting triple��s�ĺ͡�
$Solution$
ͬ[WC2011]Xor����������·����Xor�������Ǽ�(����һ��)��·���ĺ�XorһЩ���ĺ͡�so�����ȴ�������ϵĺͣ��������Ի���������һ����·������ֱ����������ڵ��dis[]��
���˸����dis��Ȼ�����������λͳ�ƴ𰸡�ͳ��dis����λ��Ϊ0/1�ĵ�������sizeΪ���Ի�������������
����������dis��һ��0һ��1����ôҪ�����Ի���ȡһ��0�������Ի�����һλ����1����������ʣ�µ�size-1��������������ϣ����ݵõ��Ľ������ȷ�����1�Ƿ�ȡ�������в�ͬ��2^{size-1}�ַ����������λû��1���Ǿ���2^{size}�ַ�����
���������disͬΪ1/0����Ҫȡһ��1��������Ի�����һλ��1��ͬ�� ��2^{size-1}�ַ�����
ע��ͼ���ܲ���ͨ��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Bit 59
#define mod (1000000007)
typedef long long LL;
const int N=1e5+5,M=4e5+5;

int n,m,Enum,H[N],nxt[M],to[M],cnt[2],t,pw[66],size;
LL len[M],dis[N],base[66],q[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline LL readll()
{
	LL now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(LL w,int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Insert(LL x)
{
	for(int i=Bit; ~i; --i)
		if(x>>i & 1)
		{
			if(base[i]) x^=base[i];
			else {base[i]=x, ++size; break;}
		}
}
void DFS(int x,int f)
{
	vis[x]=1, q[++t]=dis[x];
	for(int v,i=H[x]; i; i=nxt[i])
		if(!vis[v=to[i]]) dis[v]=dis[x]^len[i], DFS(v,x);
		else if(v!=f) Insert(dis[x]^dis[v]^len[i]);
}
LL Calc()
{
	LL ans=0;
	for(int i=Bit; ~i; --i)
	{
		bool flag=0; LL tmp;
		for(int j=0; j<=Bit; ++j)
			if(base[j]>>i&1) {flag=1; break;}
		cnt[0]=cnt[1]=0;
		for(int j=1; j<=t; ++j) ++cnt[q[j]>>i&1];
		if(!flag&&(!cnt[1]||!cnt[0])) continue;

		if(flag)
		{
			tmp=((1ll*cnt[0]*(cnt[0]-1)>>1)+(1ll*cnt[1]*(cnt[1]-1)>>1))%mod;
			ans+=1ll*tmp*pw[size-1]%mod*pw[i]%mod;
		}
		tmp=1ll*cnt[0]*cnt[1]%mod;
		if(flag) ans+=1ll*tmp*pw[size-1]%mod*pw[i]%mod;
		else ans+=1ll*tmp*pw[size]%mod*pw[i]%mod;
	}
	return ans%mod;
}

int main()
{
	n=read(), m=read(), pw[0]=1;
	for(int i=1; i<=Bit; ++i) pw[i]=pw[i-1]<<1, pw[i]>=mod&&(pw[i]-=mod);
	while(m--) AddEdge(readll(),read(),read());
	LL ans=0;
	for(int i=1; i<=n; ++i)
		if(!vis[i]) memset(base,0,sizeof base), size=t=0, DFS(i,i), ans+=Calc();
	printf("%I64d",ans%mod);

	return 0;
}
