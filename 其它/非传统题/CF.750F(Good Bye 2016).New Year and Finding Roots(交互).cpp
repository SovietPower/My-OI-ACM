/*
$Description$
��һ�ø߶�Ϊ$h$���������������$1$��$2^h-1$��ţ����򣩡�ÿ�������ѯ��һ����ı�ţ�������᷵���������ڽӵ�ı�š�����Ҫ��$16$��ѯ����ȷ����������ڵ�ı�š�
$h\leq 7$��
$Solution$
���������һ���㣬Ȼ�������Ҹ����ڵ��ߡ���������������ߣ�����������һֱ�ߵ�һ��Ҷ�ӣ������������飬��չ��һ��Ҷ�ӵ�Ҷ�ӵ������Ϳ���������չ�ˡ����������չ$1+2+\ldots+7=28$���㣬����ȷ�����ڵ�͹��ˣ���$21$����
���ǲ��С�����ȱȽ�ǳʱ���ۻ�Ƚϸߣ��������ǳ����������ڵ�͸���������������㹻��������Ϊ$2$��ֱ��BFS����������Ϊ$10+1+2+4=17$���������һ���㲻��Ҫ��֪���ˣ�����Ϊ$16$��
˼·�ܺ���⣬���Ǵ������д�����������ˡ��ο����ɡ�orzyanQval.
Ҫ�Գ�ʼ��DFS���Σ�����·����Σ����Ǽ�������·����������c1,c2������Ⱦ���(c1+c2)/2+1�������һ��������ڵ�����(c1!=c2)���Ϳ���ֱ����������·����������ĵ㡣
֮��֤ÿ�������ߣ���֮ǰ����Ⱥ���·���ĵ���ͬ��������������ֶ�BFS��
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define gc() getchar()
const int N=150;

int h,dgr[N],son[N][3],A1[N],A2[N];
bool vis[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
#define Check(x) if(dgr[x]==2) return x
inline void Query(int x)
{
	vis[x]=1;
	printf("? %d\n",x), fflush(stdout);
	dgr[x]=read();
	for(int i=0; i<dgr[x]; ++i) son[x][i]=read();
}
inline int Step(int x)
{
	for(int i=0; i<dgr[x]; ++i) if(!vis[son[x][i]]) return son[x][i];
	return son[x][0];
}
int Solve()
{
	memset(vis,0,sizeof vis);
	int h=read(), x=rand()%((1<<h)-1)+1, dep;
	Query(x); Check(x);
	if(dgr[x]==1) dep=1;
	else
	{
		int cnt1=0, cnt2=0;
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A1[++cnt1]=v; Check(v);
			if(dgr[v]==1) break;
		}
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A2[++cnt2]=v; Check(v);
			if(dgr[v]==1) break;
		}
		dep=(cnt1+cnt2>>1)+1;
		if(cnt1>cnt2) x=A1[cnt1-dep+1];
		else if(cnt1<cnt2) x=A2[cnt2-dep+1];
	}
	for(int cnt=0; dep<4/*not 5*/; cnt=0)
	{
		for(int v=Step(x); ; v=Step(v))
		{
			Query(v), A1[++cnt]=v; Check(v);
			if(dgr[v]==1) break;
		}
		dep=dep+cnt+1>>1, x=A1[cnt-dep+1];
	}
	int a,b,c,d,e;
	if(dep<h)
	{
		x=Step(x), Query(x); Check(x);
	}
	if(dep<h-1)
	{
		a=Step(x), Query(a); Check(a);
		b=Step(x), Query(b); Check(b);
	}
	if(dep<h-2)
	{
		c=Step(a), Query(c); Check(c);
		d=Step(a), Query(d); Check(d);
		e=Step(b), Query(e); Check(e);
		return Step(b);
	}
	return x;
}

int main()
{
	for(int T=read(); T--; printf("! %d\n",Solve()),fflush(stdout));
	return 0;
}
