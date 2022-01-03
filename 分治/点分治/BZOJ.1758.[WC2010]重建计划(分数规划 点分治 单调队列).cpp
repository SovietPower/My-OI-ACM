/*
36744kb	5548ms(û��O2��һ��vector������...)
$Description$
����һ���������м�ֵ$v_i$������Ϊ$1$���󳤶�$len$��$[l,r]$���·����ʹ����$\frac{\sum val}{len}$���
$n\leq 10^5,\ v_i\leq 10^6$��

$Solution$
���ִ𰸣�Ȼ���ж��Ƿ����һ��������[L,R]��·������Ȩֵ�ͷǸ������Ե���Ρ�
���ڣ��൱ǰ���ڵ㣩���Ϊd��һ��·�����������������������[L-d,R-d]�ڵ����ֵ���¡�������õ�������ά����
����Ҫ�����еĵ㰴dep�ź��򡣿�����BFS��ʡ��sort��
ֱ�������Ļ���ÿ����֮ǰ���������µ�ǰ����ʱ��ÿ�θ��Ӷ���$O(\max\{dep\})$�ģ�֮ǰ������������ȣ����ܱ�����$O(n^2\log n)$��
�����ٶ�ÿ������������������������򣬴�С�Ŀ�ʼ���㣬�������ӶȾͻ���$O(\sum dep)$���ܸ��Ӷ�$O(n\log n\log v)$��
���ǳ���Ҳ�Ƚϴ�
�ڶ���ǰҪ�Ƚ��������������ֱ����vector��ÿ������Ϊ��ʱ�����������������ˣ���
���ֱ߽�����Ż��¡�
�����2������L���������Ż�������...(8400->5500)
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 200000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define eps 1e-9
typedef long long LL;
const int N=1e5+5;
const double INF=1ll<<60;

int L,R,Enum,H[N],nxt[N<<1],to[N<<1],len[N<<1],Min,root,sz[N];
bool vis[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int dep; LL dis;
};
struct Block//ÿ����ͨ�� 
{
	int mxd;
	std::vector<Node> vec;
	bool operator <(const Block &x)const
	{
		return mxd<x.mxd;
	}
};
std::vector<Block> bl[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v,int w)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, len[Enum]=w;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, len[Enum]=w;
}
void Find_root(int x,int fa,int tot)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]&&v!=fa)
			Find_root(v,x,tot), sz[x]+=sz[v], mx=std::max(mx,sz[v]);
	mx=std::max(mx,tot-sz[x]);
	if(mx<Min) Min=mx, root=x;
}
void BFS(int s,int rt,int sl)
{
	static int q[N],pre[N],dep[N];
	static LL dis[N];
	int h=0,t=0; q[t++]=s, pre[s]=rt, dep[s]=1, dis[s]=sl;
	bl[rt].push_back(Block());
	std::vector<Block>::iterator it=--bl[rt].end();
	while(h<t)
	{
		int x=q[h++]; it->vec.push_back((Node){dep[x],dis[x]});
		for(int i=H[x],v; i; i=nxt[i])
			if(!vis[v=to[i]]&&v!=pre[x])
				pre[v]=x, dep[v]=dep[x]+1, dis[v]=dis[x]+len[i], q[t++]=v;
	}
	it->mxd=dep[q[h-1]];
	std::reverse(it->vec.begin(),it->vec.end());//dep�Ӵ�С ��֤ƥ�������ǵ����ģ��ݼ��Ļ��߽粻���Ұɣ���
}
void Solve(int x)
{
	vis[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) BFS(v,x,len[i]);
	std::sort(bl[x].begin(),bl[x].end());
	for(int i=H[x],v; i; i=nxt[i])
		if(!vis[v=to[i]]) Min=N, Find_root(v,x,sz[v]), Solve(root);
}
void Init(int n)
{
	Min=N, Find_root(1,1,n), Solve(root);
}
bool Check(int n,double X)
{
	static int q[N];
	static double mx[N];
	for(int i=1; i<=n; ++i) mx[i]=-INF;
	std::vector<Node>::iterator it2,ed2;
	std::vector<Block>::iterator it1,ed1;
	for(int s=1; s<=n; ++s)
	{
		if(!bl[s].size()||2*(--bl[s].end())->mxd<L) continue;//�����2������L���������Ż�������...
		bool vic=0;
		for(it1=bl[s].begin(),ed1=bl[s].end(); it1!=ed1; ++it1)
		{
			int mxd=it1->mxd,now=1,h=1,t=0;
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)//�õ�ǰ������ֵ��֮ǰ��������ƥ�� 
			{
				int l=std::max(0,L-it2->dep),r=std::min(mxd,R-it2->dep);//��ǰ����ƥ���·������ 
				if(l>r) continue;
				while(now<=r)
				{
					while(h<=t && mx[q[t]]<mx[now]) --t;
					q[++t]=now++;
				}
				while(h<=t && q[h]<l) ++h;
				if(mx[q[h]]+it2->dis-X*it2->dep>eps) {vic=1; goto Skip;}
			}
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)//�õ�ǰ��������״̬��˳���ж�һ���Ƿ��е����ڵ������������·����
			{
				int d=it2->dep; mx[d]=std::max(mx[d],it2->dis-X*d);
				if(L<=d && d<=R && mx[d]>eps) {vic=1; goto Skip;}
			}
		}
		Skip: ;
		for(it1=bl[s].begin(),ed1=bl[s].end(); it1!=ed1; ++it1)
			for(it2=it1->vec.begin(),ed2=it1->vec.end(); it2!=ed2; ++it2)
				mx[it2->dep]=-INF;
		if(vic) return 1;
	}
	return 0;
}

int main()
{
	int n=read(),mn=1e6,mx=0; L=read(),R=read();
	for(int i=1,u,v,w; i<n; ++i) u=read(),v=read(),w=read(),AE(u,v,w),mn=std::min(mn,w),mx=std::max(mx,w);
	Init(n);
	double l=mn,r=mx,mid;
	for(int T=1; T<=31; ++T)
		if(Check(n,mid=(l+r)*0.5)) l=mid;
		else r=mid;
	printf("%.3lf\n",l);

	return 0;
}
