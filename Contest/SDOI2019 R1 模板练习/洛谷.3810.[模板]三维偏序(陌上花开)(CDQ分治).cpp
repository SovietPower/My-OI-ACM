//6196KB	688MS(308ms	5560KB)
//https://www.cnblogs.com/SovietPower/p/8574905.html
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,M=2e5+5;

int Ans[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Node
{
	int x,y,z,cnt,ans;
	bool operator <(const Node &a)const
	{
		return x==a.x?(y==a.y?z<a.z:y<a.y):x<a.x;
	}
	bool operator !=(const Node &a)const
	{
		return x!=a.x||y!=a.y||z!=a.z;
	}
}q[N],tmp[N];
struct BIT
{
	int n,t[M];//M!
	#define lb(x) (x&-x)
	inline void Add(int p,int v)
	{
		for(; p<=n; p+=lb(p)) t[p]+=v;
	}
	inline int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
	inline void Clear(int p)
	{
		for(; p<=n&&t[p]; p+=lb(p)) t[p]=0;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
void CDQ(int l,int r)
{
	if(l<r)
	{
		int m=l+r>>1; CDQ(l,m), CDQ(m+1,r);
		int p1=l,p2=m+1,p=l;
		while(p1<=m&&p2<=r)
		{
			if(q[p1].y<=q[p2].y) T.Add(q[p1].z,q[p1].cnt), tmp[p++]=q[p1++];//q[p1].cnt!
			else q[p2].ans+=T.Query(q[p2].z), tmp[p++]=q[p2++];
		}
		while(p2<=r) q[p2].ans+=T.Query(q[p2].z), tmp[p++]=q[p2++];
		for(int i=l; i<p1; ++i) T.Clear(q[i].z);//<p1
		while(p1<=m) tmp[p++]=q[p1++];
		for(int i=l; i<=r; ++i) q[i]=tmp[i];
	}
}

int main()
{
	int n=read(); T.n=read();
	for(int i=1; i<=n; ++i) q[i]=(Node){read(),read(),read(),1,0};//cnt²»ÄÜÊÇ0°¡= = 
	std::sort(q+1,q+1+n); int cnt=1;
	for(int i=2; i<=n; ++i)
		if(q[i]!=q[i-1]) q[++cnt]=q[i];
		else ++q[cnt].cnt;
	CDQ(1,cnt);
	for(int i=1; i<=cnt; ++i) Ans[q[i].ans+q[i].cnt-1]+=q[i].cnt;
	for(int i=0; i<n; ++i) printf("%d\n",Ans[i]);

	return 0;
}
