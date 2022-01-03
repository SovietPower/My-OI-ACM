/*
218ms	32600KB
$Description$
����һ��$n$����$m$���ߵ�����ͼ���������Ի��رߡ������ټӶ������ߺ�����ڴ�$1$�������ص�$1$��ŷ����·��
ע�⣬ŷ����·��ָҪ�������бߣ��ޱߣ��߰����Ի�������Ĺ����㲻��Ҫ���ǡ�����$1$һ��Ҫ������
$n,m\leq10^6$��

$Solution$
���ͼ��ͨ����������������߼��ɡ�
���ͼ����ͨ������ÿ�����������Ҫ������һ���ߣ�û������������ͨ��������һ���������������ߡ�����ǿ��ѡ$1$���ɡ�
����ͳ�Ƶı�������$2$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e6+6;

int Enum,H[N],nxt[N<<1],to[N<<1],fa[N],dgr[N],cnt[N];
bool tag[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) fa[i]=i;
	tag[1]=1;
	for(int i=1,u,v; i<=m; ++i)
	{
		int r1=Find(u=read()),r2=Find(v=read());
		fa[r1]=r2, ++dgr[u], ++dgr[v], tag[u]=tag[v]=1;
	}
	for(int i=1; i<=n; ++i) cnt[Find(i)]+=dgr[i]&1;
	int ans=0,two=0,tot=0;
	for(int i=1; i<=n; ++i)
		if(tag[i] && Find(i)==i)
		{
			++tot;
			if(cnt[i]) ans+=cnt[i];
			else ++two;
		}
	printf("%d\n",tot==1?ans>>1:(ans>>1)+two);

	return 0;
}
