/*
7276kb	824ms
���ⲻ�Ѱ�������ô����ôɵ�������һ���ڵ�ȥģ�⡣��

����ֻ��Ҫ�ܹ�ά��������Сֵ�����ֵת������ģ��һ�·��֣�������Сֵ��������������Ȳ��䣨������ڣ�������ڵ����ȫ��$+1$���ҳ��Ҷ��������е�ĸ��ӹ�ϵ����ı䡣���ֵͬ��
��Ϊ��������������������е��ֵ���������ģ����԰�ֵ��Ϊ�±�ά���߶���������Ӽ��ɡ�
������ôά���������ķ�Χ��������$(val_x,val_{fa[x]})$�𡣡�
�����ɾ��������ת�����󣬶����е����$-1$���ɡ�

������β��롣�����λ�ÿ϶�������ǰ�����֮�䰡��������`set`���ʱ���߶����ҵ�ǰ����̣��ڶ�Ӧλ�ò�������ˣ��߶����ƺ���Щ�鷳����Ȼ�����߶����ϸ���һ��$dep$��
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5;

int n,root,val[N],ref[N],fa[N],son[N][2],opt[N];
std::set<int> st;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int val[S];
	#undef S
	#define Upd(rt,v) val[rt]+=v
//	#define Update(rt) exist[rt]=exist[ls]||exist[rs]
	inline void PushDown(int rt)
	{
		Upd(ls,val[rt]), Upd(rs,val[rt]), val[rt]=0;
	}
	void Modify(int l,int r,int rt,int L,int R,int v)
	{
		if(L<=l && r<=R) {Upd(rt,v); return;}
		if(val[rt]) PushDown(rt);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,v);
		if(m<R) Modify(rson,L,R,v);
	}
	void Set(int l,int r,int rt,int p,int v)
	{
		while(l!=r)
		{
			if(val[rt]) PushDown(rt);
			int m=l+r>>1;
			p<=m ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		val[rt]=v;
	}
	int Query(int l,int r,int rt,int p)
	{
		while(l!=r)
		{
			if(val[rt]) PushDown(rt);
			int m=l+r>>1;
			p<=m ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return val[rt];
	}
	pr Query2(int l,int r,int rt,int p)
	{
		while(l!=r)
		{
			if(val[rt]) PushDown(rt);
			int m=l+r>>1;
			p<=m ? (r=m,rt=ls) : (l=m+1,rt=rs);
		}
		return mp(rt,val[rt]);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Find(int x)
{
	int l=1,r=n,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
#define S 1,n,1
int Insert(int x)
{
	if(st.empty()) {st.insert(root=x), T.Set(S,x,1); return 1;}
	std::set<int>::iterator it=st.upper_bound(x);
	int p,v;
	if(it!=st.end()&&!son[*it][0]) son[p=*it][0]=x;
	else son[p=*(--it)][1]=x;
	st.insert(x), fa[x]=p, T.Set(S,x,v=T.Query(S,p)+1);
	return v;
}
int RotateMin()
{
	int x=*st.begin();
	if(!fa[x]) return 1;
	pr v=T.Query2(S,x);
	T.Modify(S,fa[x],n,1), T.val[v.first]=1;//T.Set(S,x,1);
	son[fa[x]][0]=son[x][1], fa[son[x][1]]=fa[x], fa[x]=0;
	son[x][1]=root, fa[root]=x, root=x;
	return v.second;
}
int RotateMax()
{
	int x=*st.rbegin();
	if(!fa[x]) return 1;
	pr v=T.Query2(S,x);
	T.Modify(S,1,fa[x],1), T.val[v.first]=1;//T.Set(S,x,1);
	son[fa[x]][1]=son[x][0], fa[son[x][0]]=fa[x], fa[x]=0;
	son[x][0]=root, fa[root]=x, root=x;
	return v.second;
}
int DeleteMin()
{
	int v=RotateMin(),x=*st.begin();
	st.erase(x), T.Modify(S,1,n,-1), fa[root=son[x][1]]=0, son[x][1]=0;
	return v;
}
int DeleteMax()
{
	int v=RotateMax(),x=*st.rbegin();
	st.erase(x), T.Modify(S,1,n,-1), fa[root=son[x][0]]=0, son[x][0]=0;
	return v;
}

int main()
{
//	freopen("splay.in","r",stdin);
//	freopen("splay.out","w",stdout);

	const int Q=read(); int n=0;
	for(int i=1; i<=Q; ++i)
		if((opt[i]=read())==1) ++n, val[n]=ref[n]=read();
	std::sort(ref+1,ref+1+n), ::n=n;
	for(int i=1,t=0; i<=Q; ++i)
		switch(opt[i])
		{
			case 1: printf("%d\n",Insert(Find(val[++t]))); break;
			case 2: printf("%d\n",RotateMin()); break;
			case 3: printf("%d\n",RotateMax()); break;
			case 4: printf("%d\n",DeleteMin()); break;
			case 5: printf("%d\n",DeleteMax()); break;
		}
	return 0;
}
