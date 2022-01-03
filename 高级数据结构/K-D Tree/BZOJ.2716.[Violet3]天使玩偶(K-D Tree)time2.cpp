//65576kb	12412ms
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define alpha (0.75)
const int N=5e5+5,INF=0x7fffffff;

char IN[MAXIN],*SS=IN,*TT=IN;
namespace KD_Tree
{
	int n,Q,root,Now_d,top,sk[N<<1],Ans;
	struct Point{
		int d[2];
	}p[N<<1];
	struct Node{
		int Min[2],Max[2],ls,rs,sz;
		Point pt;
	}t[N*3];//??
	
	inline bool Cmp_d(const Point &a,const Point &b){
		return a.d[Now_d]<b.d[Now_d];
	}
	inline int New_Node(){
		return top?sk[top--]:++n;
	}
	inline void Init(int rt)
	{
		t[rt].sz=1;
		for(int i=0; i<2; ++i)
			t[rt].Min[i]=t[rt].Max[i]=t[rt].pt.d[i];
	}
	inline void Update(int rt)
	{
		int ls=t[rt].ls,rs=t[rt].rs;
		t[rt].sz=t[ls].sz+t[rs].sz+1;
		for(int i=0; i<2; ++i){
			if(ls) t[rt].Min[i]=std::min(t[rt].Min[i],t[ls].Min[i]),t[rt].Max[i]=std::max(t[rt].Max[i],t[ls].Max[i]);
			if(rs) t[rt].Min[i]=std::min(t[rt].Min[i],t[rs].Min[i]),t[rt].Max[i]=std::max(t[rt].Max[i],t[rs].Max[i]);
		}
	}
	int Build(int l,int r,int D)
	{
		if(l>r) return 0;
		int mid=l+r>>1,k=New_Node();
		Now_d=D, std::nth_element(p+l,p+mid,p+r+1,Cmp_d);
		t[k].pt=p[mid], Init(k);
		t[k].ls=Build(l,mid-1,D^1), t[k].rs=Build(mid+1,r,D^1);
		Update(k); return k;
	}
	void DFS(int rt,int num)
	{
		if(t[rt].ls) DFS(t[rt].ls,num);
		p[num+t[t[rt].ls].sz+1]=t[rt].pt, sk[++top]=rt;
		if(t[rt].rs) DFS(t[rt].rs,num+t[t[rt].ls].sz+1);
	}
	inline void Check(int &k,int D){
		if(t[k].sz*alpha<t[t[k].ls].sz||t[k].sz*alpha<t[t[k].rs].sz)
			DFS(k,0), k=Build(1,t[k].sz,D);
	}
	void Insert(Point p,int &k,int D)
	{
		if(!k) {t[k=New_Node()].pt=p, Init(k), t[k].ls=t[k].rs=0; return;}
		if(p.d[D]<=t[k].pt.d[D]) Insert(p,t[k].ls,D^1);
		else Insert(p,t[k].rs,D^1);
		Update(k), Check(k,D);
	}
	int Dis_node(Point a,int k)
	{
		int res=0;
		for(int i=0; i<2; ++i)
			res+=std::max(0,a.d[i]-t[k].Max[i])+std::max(0,t[k].Min[i]-a.d[i]);
		return res;
	}
	int Dis(Point a,Point b){
		return std::abs(a.d[0]-b.d[0])+std::abs(a.d[1]-b.d[1]);
	}
	void Query(Point p,int k)
	{
		Ans=std::min(Ans,Dis(p,t[k].pt));
		int dl=t[k].ls?Dis_node(p,t[k].ls):INF;
		int dr=t[k].rs?Dis_node(p,t[k].rs):INF;
		if(dl<dr){
			if(dl<Ans) Query(p,t[k].ls);
			if(dr<Ans) Query(p,t[k].rs);
		}
		else{
			if(dr<Ans) Query(p,t[k].rs);
			if(dl<Ans) Query(p,t[k].ls);
		}
	}
}
using namespace KD_Tree;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),Q=read();
	for(int i=1; i<=n; ++i) p[i].d[0]=read(),p[i].d[1]=read();
	root=Build(1,n,0); Point tmp;
	while(Q--)
		if(read()==1) tmp.d[0]=read(),tmp.d[1]=read(),Insert(tmp,root,0);
		else tmp.d[0]=read(),tmp.d[1]=read(),Ans=INF,Query(tmp,root),printf("%d\n",Ans);

	return 0;
}
