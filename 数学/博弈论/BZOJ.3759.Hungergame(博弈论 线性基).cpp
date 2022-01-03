/*
$Description$
有n堆锁定的石子，每次操作可以解锁某些堆石子，或是从一堆已解锁的石子堆中拿任意多个(>0)，最后无法操作者输。问先手是否必胜。
$Solution$
如果不考虑未解锁的，现在有一些已解锁的石子，先手想要必胜 可以在他操作完后使(已解锁的)石子堆异或和为0。但是如果未解锁的石子堆中存在异或和为0的，后手解锁它们可以使先手面临必败态。
所以如果有异或和为0的某些石子堆，先手会在最初把它们都解锁掉，不给后手翻盘机会，那他必胜。
而如果不存在异或和为0的某些石子堆，即先手要解锁一些石子堆开始，那把上面过程的先手、后手交换下，状态为无未解锁的异或和为0的石子堆，可知先手必败。
所以直接用线性基判断有无异或和为0的某些石子堆。
*/
#include <cstdio>
#include <cctype>
#include <cstring>
#define gc() getchar()
#define Bit 29

int base[33];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline bool Insert(int x,bool f)
{
	if(f) return 1;
	for(int i=Bit; ~i; --i)
		if(x>>i&1)
			if(base[i]) x^=base[i];
			else {base[i]=x; break;}
	return x==0;
}

int main()
{
	int T=read();
	while(T--)
	{
		memset(base,0,sizeof base);
		int n=read(); bool f=0;
		while(n--) f|=Insert(read(),f);
		puts(f?"Yes":"No");
	}
	return 0;
}
