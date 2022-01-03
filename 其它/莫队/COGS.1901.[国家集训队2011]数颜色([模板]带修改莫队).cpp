/*
Add和Subd函数中的vis不能直接设为=1或=0 
比如 l=1,r=0 -> l=3,r=5 时，[1,5]的vis标记全都是1 
所以要进行取反 
*/
#include<cmath>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e4+5,M1=1e4+5,M2=1005,MAX=1e6+5;

int n,m,size,A[N],Ans[M1],times[MAX],qn,mn,belong[N],now;
int H[N];
bool vis[N];
struct QUERY
{
	int l,r,id,t;//t:修改了几次后的 
	bool operator <(const QUERY &x)const
	{
		if(belong[l]==belong[x.l])
		{
			if(belong[r]==belong[x.r]) return t<x.t;
			return r<x.r;
		}
		return l<x.l;
	}
}q[M1];
struct MODIFT
{
	int pos,val,bef;
}optm[M2];

inline int read()
{
	int now=0,f=1;register char c=getchar();
	for(;!isdigit(c);c=getchar())
	  if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=getchar());
	return now*f;
}

void Change(int t)
{
	int pos=optm[t].pos;
	if(vis[pos])//在询问区间内 
	{
		--times[A[pos]];
		if(!times[A[pos]]) --now;
	}
	optm[t].bef=A[pos],
	A[pos]=optm[t].val;//记录下改之前的值，然后更新 
	if(vis[pos])
	{
		if(!times[A[pos]]) ++now;
		++times[A[pos]];
	}
}
void Unchange(int t)//改回来 
{
	int pos=optm[t].pos;
	if(vis[pos])
	{
		--times[A[pos]];
		if(!times[A[pos]]) --now;
	}
	A[pos]=optm[t].bef;
	if(vis[pos])
	{
		if(!times[A[pos]]) ++now;
		++times[A[pos]];
	}
}
//void Change(int p,int v)//Change和Unchange可以由这一个函数代替 
//{
//	if(vis[p])
//		Calc(p), A[p]=v, Calc(p);
//	else
//		A[p]=v;
//}
void Add(int p)
{
	if(!times[A[p]]) ++now;
	++times[A[p]];
	vis[p]^=1;
//	vis[p]=1;//加入访问区间 //错的！ 
}
void Subd(int p)
{
	--times[A[p]];
	if(!times[A[p]]) --now;
	vis[p]^=1;
//	vis[p]=0;//从区间中删掉 //错的！ 
}
void Calc(int p)
{
	if(vis[p])
	{
		if(--times[A[p]]==0)
			--now;
	}
	else if(++times[A[p]]==1)
		++now;
	vis[p]^=1;
//	vis[p]=!vis[p];
}

int main()
{
	freopen("nt2011_color1.in","r",stdin);
	freopen("nt2011_color.out","w",stdout);

	n=read(),m=read();
	size=pow(n,2.0/3.0)*0.7;//取小一点更优 
	for(int i=1;i<=n;++i)
		A[i]=read(), H[i]=A[i], belong[i]=(i-1)/size+1;
	char opt[3];
	for(int a,b,i=1;i<=m;++i)
	{
		scanf("%s",opt);a=read(),b=read();
		if(opt[0]=='Q')
			q[++qn]=(QUERY){a,b,qn,mn};//注意编号 
		else
			optm[++mn].pos=a, optm[mn].val=b;//, optm[mn].bef=H[a], H[a]=b;
	}
	sort(q+1,q+1+qn);
	for(int i=1,l=1,r=0,t=0;i<=qn;++i)
	{
		int ln=q[i].l,rn=q[i].r,tn=q[i].t;
		while(t<tn) Change(++t);
		while(t>tn) Unchange(t--);
//		while(t<tn) ++t,Change(optm[t].pos,optm[t].val);//++t不能放在参数里写！ 
//		while(t>tn) Change(optm[t].pos,optm[t].bef),--t;
		
		while(l<ln) Calc(l++);
		while(l>ln) Calc(--l);
		while(r<rn) Calc(++r);
		while(r>rn) Calc(r--);
//		while(l<ln) Subd(l++);
//		while(l>ln) Add(--l);
//		while(r<rn) Add(++r);
//		while(r>rn) Subd(r--);
		Ans[q[i].id]=now;
	}
	for(int i=1;i<=qn;++i)
		printf("%d\n",Ans[i]);

	fclose(stdin);fclose(stdout);
	return 0;
}
