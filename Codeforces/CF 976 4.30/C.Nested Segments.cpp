#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=3e5+5;

int n;
struct Segment
{
	int l,r,id;
	bool operator <(const Segment &x)const{
		return l==x.l?r>x.r:l<x.l;
	}
}s[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) s[i].l=read(),s[i].r=read(),s[i].id=i;
	std::sort(s+1,s+1+n);
	int mxr=0, pos, ansi=-1, ansj=-1;
	for(int i=1; i<=n; ++i)
		if(mxr>=s[i].r) {ansj=s[pos].id, ansi=s[i].id; break;}
		else if(mxr<s[i].r) mxr=s[i].r, pos=i;
	printf("%d %d",ansi,ansj);

	return 0;
}
