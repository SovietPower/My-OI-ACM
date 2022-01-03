/*
���ǵ�ʱ��Ĵ���... ûʱ����д�ˡ�
����������������Ϊ��Χ��С...
��ÿ���ߣ�Ҫʹ �������б�ȨС�����ıߺ�ͼ�Բ�����ͨ�������������ߺ������ͨ��
�����������ߵ������˵���ΪԴ��㣬�����б�ȨС�����ı߼���ͼ�У�����С�Ϊ���Ĵ𰸡�
*/
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1005;

int fa[N];
bool tag[N];
std::vector<int> vec[N];
struct Edge
{
	int type,u,v,w;//type:1>0
	bool operator <(const Edge &x)const
	{
		return w==x.w?type>x.type:w<x.w;
	}
}e[N],e2[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(; !isdigit(c); c=='-'&&(f=-1),c=gc());
	for(; isdigit(c); now=now*10+c-48,c=gc());
	return now*f;
}
int Find(int x)
{
	return fa[x]==x?x:fa[x]=Find(fa[x]);
}
void Init(int n,int m)
{
	for(int i=1; i<=n; ++i) fa[i]=i;
	for(int i=1; i<=m; ++i) tag[i]=0;
}
inline void Merge(int u,int v)
{
	fa[Find(u)]=Find(v);
}
int Solve(int x,int n,int m)
{
	Init(n,m);
	int U=e[x].u,V=e[x].v;
	tag[x]=1, Merge(U,V);
	for(int i=1,cnt=2; i<=m; ++i)
	{
		int u=e[i].u,v=e[i].v;
		if(Find(u)!=Find(v))
		{
			tag[i]=1, Merge(u,v);
			if(++cnt==n) break;
		}
	}
	Init(n,0);
	for(int i=1; i<=m; ++i) e2[i]=e[i], e2[i].type=tag[i];
	std::sort(e2+1,e2+1+m);
	int res=0;
	for(int i=1,cnt=1; i<=m; ++i)
	{
		int u=e[i].u,v=e[i].v;
		printf("u:%d v:%d U:%d V:%d\n",u,v,U,V);
		u=Find(u),v=Find(v),U=Find(U),V=Find(V);
		if(u>v) std::swap(u,v);
		if(U>V) std::swap(U,V);
		printf("u:%d v:%d U:%d V:%d\n",u,v,U,V); printf("i:%d type:%d\n",i,e2[i].type);
		if(u!=v)
		{
			if(!e2[i].type && u==U && v==V) {++res, puts("Add!"); continue;}
			else if(!e2[i].type) ++res, puts("Add!");
			else
			{
				Merge(u,v);  puts("Merge!");
				if(++cnt==n) break;
			}
		}
	}
	printf("Solve(%d)=%d\n\n",x,res);
	return res;
}
int Solve2(int n,int m,int I,int x,int w)
{
	int cnt=2,res=0;
	Init(n,m);
	for(int i=1; i<=m&&e[i].w<w; ++i)
	{
		if(i==I) continue;
		int u=e[i].u,v=e[i].v;
		if(Find(u)!=Find(v))
		{
			if(e[i].u==x||e[i].v==x) res+=e[i].w<w, tag[i]=1;
			else Merge(u,v), ++cnt;
		}
	}
//	printf("\npreSolve(%d,%d,%d):%d cnt:%d\n",I,x,w,res,cnt);
	if(cnt==n) return res;
//	Merge(e[I].u,e[I].v);
	int U=e[I].u,V=e[I].v;
	for(int i=1; i<=m&&cnt!=n; ++i)
		if(tag[i])
		{
			int u=e[i].u,v=e[i].v;
			u=Find(u),v=Find(v),U=Find(U),V=Find(V);
			if(u>v) std::swap(u,v);
			if(U>V) std::swap(U,V);
			if(u==U && v==V) continue;
			if(Find(u)!=Find(v)) Merge(u,v), --res, ++cnt;
			else --res;
		}
		else
		{
			int u=e[i].u,v=e[i].v;
			u=Find(u),v=Find(v),U=Find(U),V=Find(V);
			if(u>v) std::swap(u,v);
			if(U>V) std::swap(U,V);
			if(u==U && v==V) continue;
			if(Find(u)!=Find(v)) Merge(u,v), ++cnt;
		}
//	printf("Solve(%d,%d,%d):%d cnt:%d\n",I,x,w,res,cnt);
	return cnt==n?res:0;
}

int main()
{
	int n=read(),m=read();
	if(n==1) return puts("0"),0;
	for(int i=1; i<=m; ++i) e[i]=(Edge){0,read(),read(),read()};
	std::sort(e+1,e+1+m);
//	for(int i=1; i<=m; ++i) printf("%d:(%d,%d,%d)\n",i,e[i].u,e[i].v,e[i].w);
	for(int i=1; i<=m; ++i) vec[e[i].u].push_back(i), vec[e[i].v].push_back(i);
	if(n==2)
	{
		int ans=0;
		for(int i=1; i<=m; ++i) if(e[i].w>e[1].w) ++ans;
		return printf("%d\n",ans),0;
	} 
	int ans=0;
	for(int i=1; i<=m; ++i) ans+=std::min(Solve2(n,m,i,e[i].u,e[i].w),Solve2(n,m,i,e[i].v,e[i].w));
	printf("%d\n",ans);

	return 0;
}
