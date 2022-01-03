//WA
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=2e5+5;

int n,a,b;
struct Node
{
	int hp,dmg,delta;
	bool operator <(const Node &x)const{
		return delta==x.delta?dmg<x.dmg:delta>x.delta;
	}
}c[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read(),a=read(),b=read();
	for(int i=1; i<=n; ++i) c[i].hp=read(),c[i].dmg=read(),c[i].delta=c[i].hp-c[i].dmg;
	long long sum=0,mx=0,aa=1ll<<a,v;
	std::sort(c+1,c+1+n);
	int pos=0;
	if(a&&b)
		for(int i=1; i<=n; ++i)
			if((v=1ll*aa*c[i].hp-c[i].dmg)>=mx && v>c[i].delta) mx=v, pos=i;
	if(mx>0) sum=mx+c[pos].dmg, --b;
	int i=1;
	for(; i<=n&&b&&c[i].delta>0; ++i)
		if(i!=pos) sum+=c[i].hp, --b;
	for(; i<=n; ++i)
		if(i!=pos) sum+=c[i].dmg;
	printf("%I64d",sum);

	return 0;
}
