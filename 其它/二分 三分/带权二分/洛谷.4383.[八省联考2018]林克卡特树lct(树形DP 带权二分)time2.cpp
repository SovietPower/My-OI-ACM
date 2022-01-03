/*
$Description$
����һ�ñߴ�Ȩ��������ɾ��K���ߡ�������K��ȨΪ0�ıߺ����������ֱ����
$n,K\leq3\times10^5$��
$Solution$
��Ŀ����ת��Ϊ�������ϲ��ཻ��$k+1$������ʹ�����ǵı�Ȩ�����(�Ѳ�����˵ʲô�ˡ���)��
ѡ������Խ�࣬��������Խ�������ٵ�ʱ�򻹻���ٵ�Խ�죬���γ���һ��$K-Ans_K$����͹���������û�����������ƣ�DP�Ǻ����׵�(�������ü�һά$k$)��
��Ȩ���֡�DP��$f[x][0/1/2]$��ʾ��$x$����Ϊ$0/1/2$ʱ�����Ž⣬��һ����������µ�������

**DPϸ�ڣ�**
$f[x][1]$������Ϊ$1$ʱ������Ϊ���Ļ��ѣ����Ǻϲ�ʱ���ϣ�������ɡ�
�����$f[x][0]$ �� ��$f[x][1]$����������$f[x][2]$ȡ��$\max$����ʾ����״̬���������ϸ��µ�����״̬��������Ͽ�����
�ṹ��д��Ȼ�������㵫��̫��д�ˡ���������Ȼ��ô���ô...
ע����$K+1$��_�� 

**[Update] 19.2.11**
���ֱ߽��ǣ�ʹ�ñ߽��㹻���ܱ�֤ÿһ����Ʒ������ѡ��Ҳ����ÿ����Ʒ��������ֵ�Ϳ����ˡ�������[CF739E](https://www.cnblogs.com/SovietPower/p/9163792.html)��Ȩֵ0~1�͹���
Ȼ��...���ֵ�ʱ��ֻҪ��֤ǡ��ȡ��$k$���Ϳ����ˣ�б�ʾ����Ƕ�������ν...�ɡ�
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=3e5+5;
const LL INF=1ll<<60;

int Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1];
LL C;
struct Node
{
	LL val; int cnt;
	inline Node operator +(int v)
	{
		return (Node){val+v,cnt};
	}
	inline Node operator +(const Node &x)
	{
		return (Node){val+x.val,cnt+x.cnt};
	}
	inline bool operator <(const Node &x)const
	{
		return val==x.val?cnt>x.cnt:val<x.val;
	}
}f[N][3];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
inline Node Upd(const Node &x)
{
	return (Node){x.val-C,x.cnt+1};
}
void DFS(int x,int fa)
{
	f[x][0]=f[x][1]=(Node){0,0}, f[x][2]=(Node){-INF,0};
	//f[x][1]=0��ֱ�Ӻϲ���
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa)
		{
			DFS(v,x);
			f[x][2]=std::max(f[x][2]+f[v][0],Upd(f[x][1]+f[v][1]+len[i]));
			f[x][1]=std::max(f[x][1]+f[v][0],f[x][0]+f[v][1]+len[i]);
			f[x][0]=f[x][0]+f[v][0];
		}
	f[x][0]=std::max(f[x][0],std::max(Upd(f[x][1]),f[x][2]));//Ϊ����ֱ�Ӱ�f[x][0]��Ϊ��x���Ͽ�������ֵ���ɡ�
}

int main()
{
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);

	const int n=read(),K=read()+1;
	LL s1=0,s2=0;
	for(int i=1,u,v,w; i<n; ++i) u=read(),v=read(),w=read(),w>0?s1+=w:s2-=w,AE(u,v,w);
	LL r=std::max(s1,s2),l=-r,mid;
	while(l<r)
	{
		if(C=mid=l+r>>1,DFS(1,1),f[1][0].cnt>K) l=mid+1;
		else r=mid;
	}
	C=l, DFS(1,1);
	printf("%lld\n",f[1][0].val+C*K);

	return 0;
}
