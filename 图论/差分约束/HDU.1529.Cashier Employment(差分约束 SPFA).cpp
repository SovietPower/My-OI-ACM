/*
15MS	1580K
$Description$
����һ��24h ÿСʱ��Ҫ��Ա������Ri����n��Ա������֪ÿ��Ա����ʼ������ʱ��ti(ti��[0,23])��ÿ��Ա������������8h��
���ܷ�����һ����������ܣ����������Ҫ����Ա����
$Solution$
��Ȼ�����ǿ�ʼ����ʱ�䣬��ô���ȸ��ݿ�ʼʱ���� 
��Ai��ʾ��iʱ��ʼ����������(δ֪)��Bi��ʾiʱ�ɹ�������������(��֪) 
��ô��:��ע����Կ��죩 
A[i-7]+A[i-6]+...+A[i-1]+A[i] >= R[i] (7 <= i < 24)
A[17+i]+A[18+i]+...+A[23]+A[0]+A[1]+...+A[i] >= R[i] (0 <= i < 7)
0 <= A[i] <= B[i]

��S[i]=A[0]+A[1]+...+A[i]���涨S[-1]=0�����ϱ�ʽ��ת��һ����: 
S[i]-S[i-8] >= R[i] (7 <= i < 24)
S[23]-S[16+i]+S[i] >= R[i] (0 <= i < 7)
0 <= S[i]-S[i-1] <= B[i]
�۲첻��ʽ����������δ֪����S[23]�Ǹ�δ֪���������޷�ת��Ϊ���Լ����������ֻ������������i�йأ��������Ƕ�S[23]����ö�٣���S[23]=T 
S[i]-S[i-8] >= R[i] (7 <= i < 24)
S[i]-S[16+i] >= R[i]-T (0 <= i < 7)
S[i]-S[i-1] >= 0 
S[i-1]-S[i] >= -B[i]
�����ͽ�ԭ����ת��Ϊ����-1 -> 23���· 
���ǻ���һ��������������S[23]=T������Ҳ��Ҫ����ת��Ϊ����ʽ����ΪS[-1]=0������S[23]-S[-1]=T������ת��Ϊ��������ʽ 
S[23]-S[-1] >= T
S[-1]-S[23] >= -T
��-1 -> 23���·=T����ôT��������������һ���⡣��С����ö�� ��һ�����еļ�Ϊ�𰸡�
����Ա��������Ȼ�ǵ����ģ����Կ��Զ���T (�����������ǲ����ڸ���) 
ע: T(S[23]=A[0]+A[1]+...)���Ͻ���n��not B[23] 
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=50,M=1e4+5,T=24,INF=0x3f3f3f3f;

int n,B[N],R[N],Enum,H[N],nxt[M],to[M],val[M],dis[N],tm[N];
bool inq[N];
std::queue<int> q;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AddEdge(int u,int v,int w){
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, val[Enum]=w;
}
bool SPFA()
{
	for(int i=1; i<=T; ++i) dis[i]=-INF,tm[i]=0;
	tm[0]=dis[0]=0, q.push(0);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		inq[x]=0;
		for(int i=H[x]; i; i=nxt[i])
			if(dis[to[i]]<dis[x]+val[i])
			{
				dis[to[i]]=dis[x]+val[i];
				if(!inq[to[i]])
				{
					if(++tm[to[i]]>T) return 0;
					inq[to[i]]=1,q.push(to[i]);
				}
			}
	}
	return 1;
}
bool Check(int x)
{
	Enum=0, memset(H,0,sizeof H);
	for(int i=1; i<8; ++i) AddEdge(16+i,i,R[i]-x);
	for(int i=8; i<=T; ++i) AddEdge(i-8,i,R[i]);
	for(int i=1; i<=T; ++i) AddEdge(i,i-1,-B[i]),AddEdge(i-1,i,0);
	AddEdge(0,T,x), AddEdge(T,0,-x);
	return SPFA();
}

int main()
{
	int t=read();
	while(t--)
	{
		memset(B,0,sizeof B);
		for(int i=1; i<=T; ++i) R[i]=read();
		n=read();
		for(int i=1; i<=n; ++i) ++B[read()+1];
		int l=0,r=n+1,mid;
		while(l<r)
			if(Check(mid=l+r>>1)) r=mid;
			else l=mid+1;
		l>n ? puts("No Solution") : printf("%d\n",l);
	}
	return 0;
}
