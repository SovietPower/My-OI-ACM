//直接上vector(本机还是比较慢的...) 某块size较大时O(n)重构 
//注意细节 
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#define gc() getchar()
#define pb push_back
typedef long long LL;
const int N=1e5+5;

int n,size,tmp[N<<1],bel;
std::vector<int> v[500];
std::vector<int>::iterator it;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline int Get_Pos(int &p)
{
	for(int i=1; i<=bel; ++i)
		if((p-=v[i].size())<=0) {p+=v[i].size(); return i;}
}
void Rebuild()
{
	int tot=0;
	for(int i=1; i<=bel; ++i)
	{
		for(it=v[i].begin(); it!=v[i].end(); ++it) tmp[++tot]=*it;
		v[i].clear();
	}
	size=sqrt(tot);
	for(int i=1; i<=tot; ++i) bel=(i-1)/size+1, v[bel].pb(tmp[i]);
}
void Insert(int p,int val)
{
	int id=Get_Pos(p);
	v[id].insert(v[id].begin()+p-1,val);
	if(v[id].size()>size*15) Rebuild();
}

int main()
{
	n=read(), size=sqrt(n);
	for(int i=1; i<=n; ++i) bel=(i-1)/size+1,v[bel].pb(read());
	for(int opt,l,r,c,id,i=1; i<=n; ++i)
	{
		opt=read(),l=read(),r=read(),c=read();
		if(opt) id=Get_Pos(r),printf("%d\n",v[id][r-1]);
		else Insert(l,r);
	}
	return 0;
}
