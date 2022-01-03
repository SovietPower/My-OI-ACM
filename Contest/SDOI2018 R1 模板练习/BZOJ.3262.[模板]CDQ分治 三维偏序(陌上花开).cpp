/*
5904kb	840ms
是对x,y,z都相同的元素去重，不是对z。。sb了。
去重后的贡献是q[p].cnt!
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define lb(x) (x)&-(x)
const int N=1e5+5,MAXN=2e5+5;

int n,Ans[N];
int read();
struct Node
{
	int x,y,z,cnt,ans;
	void Init(){
		x=read(),y=read(),z=read(),cnt=1;
	}
	bool operator <(const Node &a)const{
		return x==a.x?(y==a.y?z<a.z:y<a.y):x<a.x;
	}
}q[N],tmp[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace BIT
{
	int n,val[MAXN];
	inline void Add(int p,int v){
		while(p<=n) val[p]+=v,p+=lb(p);
	}
	inline int Query(int p){
		int res=0;
		while(p) res+=val[p],p-=lb(p);
		return res;
	}
	inline void Clear(int p){
		while(p<=n)
			if(val[p]) val[p]=0,p+=lb(p);
			else break;
	}
}
void CDQ(int l,int r)
{
	if(l<r){
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,t=0;
		while(p1<=m&&p2<=r)
		{
			if(q[p1].y<=q[p2].y) BIT::Add(q[p1].z,q[p1].cnt), tmp[t++]=q[p1++];//只是排y，别去管什么z。。
			else q[p2].ans+=BIT::Query(q[p2].z), tmp[t++]=q[p2++];
		}
		if(p1<=m){
			for(int i=l; i<p1; ++i) BIT::Clear(q[i].z);
			while(p1<=m) tmp[t++]=q[p1++];
		}
		else if(p2<=r){
			while(p2<=r) q[p2].ans+=BIT::Query(q[p2].z), tmp[t++]=q[p2++];
			for(int i=l; i<=m; ++i) BIT::Clear(q[i].z);
		}
		for(int i=0; i<t; ++i) q[l+i]=tmp[i];
	}
}

int main()
{
	n=read(),BIT::n=read();
	for(int i=1; i<=n; ++i) q[i].Init();
	std::sort(q+1,q+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(q[i].z!=q[i-1].z||q[i].y!=q[i-1].y||q[i].x!=q[i-1].x) q[++cnt]=q[i];
		else ++q[cnt].cnt;
	CDQ(1,cnt);
	for(int i=1; i<=cnt; ++i) Ans[q[i].ans+q[i].cnt-1]+=q[i].cnt;
	for(int i=0; i<n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
