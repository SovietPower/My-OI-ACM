/*
https://www.cnblogs.com/SovietPower/p/9688048.html
ö��ÿ���ߣ��������Ĺ��ס�
��ô����Ҫ�ж��ж�����������ĵ��������ߣ��������㣬������ȥ���������ߵ�����ֱ��ж��ٸ��������䡣
��ô��Ȼ��$O(n^2)$������������ÿ����DFS�������࣬ö��һ��ÿһ����������䡣
���ǻ�����DFS�����������ÿ����������Ҫ�����������ں��������������������
���������ڵĵ㣬���鼯��Ȼ�ǿ���ά���ģ�ÿ�κϲ����ڵ��Ϊһ����������ʱ�²������������������㣬������������size�ĳ˻�����
����������ĵ���ô���ء����ǿ����ȼ���������Ϊ$1,2,...,n$��������Щ���䡣����ÿ���������м����ʱ���Ͱ�����������ļ��ϵĵ���ɾ�����������������ٵ���������
���Ƿ��ֲ���Ҫn��Ԫ�صļ��ϣ�Ҳ����Ҫ����ɾ����һ����ʼֻ��0��n+1�Ŀռ����ÿ�μ��������ڵĵ㣬Ȼ����㣬Ҳ�ǵȼ۵ġ�
����������Ҫ��ÿ�������ϲ����鼯������set��
������dsu on tree��ÿ���ȴ���������ӵ�������ÿ�δ����궼����ǿ������Ĺ���/״̬�����鼯��set����������ض���������������������״̬��
������������������Ҳ��������ñߴ𰸺󣩣��ٰ�����������δ����������������벢�鼯��set��
dsu�ĸ��Ӷ���$O(n\log n)$�ģ������ϱ�ģ����Ӷ�Ϊ$O(n\log^2n)$��
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 150000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define Calc(x) (1ll*(x)*(x-1)>>1ll)//������� 
typedef long long LL;
const int N=1e5+5;

int n,Enum,H[N],nxt[N<<1],to[N<<1],fa[N],sz[N],son[N],Fa[N],size[N];
bool vis[N];//���������ڵ��������䣨�Ƿ��������Ѵ������ڵģ�
LL Ans,sum1,sum2;
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void AE(int u,int v)
{
	to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum;
	to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum;
}
void DFS1(int x)
{
	int mx=0; sz[x]=1;
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x])
		{
			fa[v]=x, DFS1(v), sz[x]+=sz[v];
			if(sz[v]>mx) mx=sz[v], son[x]=v;
		}
}
int Find(int x)
{
	return x==Fa[x]?x:Fa[x]=Find(Fa[x]);
}
void Upd(int x)
{
	st.insert(x);//����ô�ǵ��з���ֵ(iterator)��...
	std::set<int>::iterator it=st.find(x),pre=it,nxt=++it;
	--pre;
	sum2-=Calc(*nxt-*pre-1);//��������ǰ���������䱻�ָ� 
	sum2+=Calc(x-*pre-1)+Calc(*nxt-x-1);

	vis[x]=1;
	if(vis[x-1])
	{
		int r1=Find(x-1),r2=Find(x);//����֮ǰ��Ȼ������һ�����ϰ�������֮��ֻ����һ�Σ�Ҫô�Ǽ�x-1����ǰ��x��Ҫô�Ǽ�x����ǰ��x-1����
		sum1+=1ll*size[r1]*size[r2];
		Fa[r1]=r2, size[r2]+=size[r1];
	}
	if(vis[x+1])
	{
		int r1=Find(x+1),r2=Find(x);
		sum1+=1ll*size[r1]*size[r2];
		Fa[r1]=r2, size[r2]+=size[r1];
	}
}
void Clear(int x)
{
	Fa[x]=x, size[x]=1, vis[x]=0;
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) Clear(to[i]);
}
void Update(int x)
{
	Upd(x);
	for(int i=H[x]; i; i=nxt[i])
		if(to[i]!=fa[x]) Update(to[i]);
}
void DFS2(int x)
{
	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x]&&v!=son[x])
		{
			DFS2(v), Clear(v);
			st.clear(), st.insert(0), st.insert(n+1);
			sum1=0, sum2=Calc(n);//������DFS��������ͳ�ʼ���� 
		}
	if(son[x]) DFS2(son[x]);

	for(int i=H[x],v; i; i=nxt[i])
		if((v=to[i])!=fa[x]&&v!=son[x]) Update(v);

	Upd(x);
	Ans+=Calc(n)-sum1-sum2;
}

int main()
{
//	freopen("treecnt.in","r",stdin);
//	freopen("treecnt.out","w",stdout);

	n=read();
	for(int i=1; i<n; ++i) AE(read(),read());
	for(int i=1; i<=n; ++i) Fa[i]=i,size[i]=1;//!
	st.insert(0), st.insert(n+1);//�߽�.
	sum1=0, sum2=Calc(n), DFS1(1), DFS2(1), printf("%lld\n",Ans);

	return 0;
}
