/*
发现在n>56的时候比较麻烦。。无脑判一波就行了。
注意是车不是卒，可以跨越多个格子。。
*/
#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define gc() getchar()
#define pc putchar
#define mp std::make_pair
#define pr std::pair<int,int>
typedef long long LL;
const int N=105;

pr s[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
void GetCol(int &cnt,int c1,int c2,int mx)
{
	int now=8;
	while(now>=8-mx+1) s[++cnt]=mp(c1,now--);
	now=8-mx+1;
	while(now<=8) s[++cnt]=mp(c2,now++);
}

int main()
{
	int n=read(),cnt=0,N=n; s[n]=mp(8,8);
	if(n<=8)
	{
		int now=8; --n;
		while(n) s[n--]=mp(1,now), --now;
	}
	else if(n<=56)
	{
		int now=2,col=2;
		if(n&1)
		{
			n-=7, now=3;
			while(now<=8) s[++cnt]=mp(1,now++);
		}
		else
		{
			n-=8;
			while(now<=8) s[++cnt]=mp(1,now++);
		}
		for(int lim=8; lim; --lim)
			while(n>=lim*2) n-=lim*2, GetCol(cnt,col,col+1,lim),col+=2;
	}
	else
	{
		int now=2,col=2;
		n-=8;
		while(now<=8) s[++cnt]=mp(1,now++);
//		for(int lim=8; lim; --lim)
//			while(n>=lim*2) n-=lim*2, GetCol(cnt,col,col+1,lim),col+=2;
		if(n>=16) n-=16, GetCol(cnt,col,col+1,8),col+=2;
		if(n>=16) n-=16, GetCol(cnt,col,col+1,8),col+=2;
		now=8; n-=8;
		while(now) s[++cnt]=mp(6,now--);
		if(n==9)
		{
			s[++cnt]=mp(7,1);
			s[++cnt]=mp(7,2);
			s[++cnt]=mp(8,2);
			s[++cnt]=mp(8,1);
			s[++cnt]=mp(8,3);//
			s[++cnt]=mp(8,4);
			s[++cnt]=mp(8,5);
			s[++cnt]=mp(8,6);
			s[++cnt]=mp(8,7);
		}
		else
		{
			s[++cnt]=mp(7,1);
			for(int i=1; i<=7; ++i) s[++cnt]=mp(8,i);
			s[++cnt]=mp(7,7);
			n-=10; now=6;
			while(n) s[++cnt]=mp(7,now--),--n;
			s[++cnt]=mp(7,8);
		}
	}
	s[0].first=1, s[0].second=1;
	for(int i=0; i<=N; ++i) pc(s[i].first+'a'-1),pc(s[i].second+'0'),pc(' ');

	return 0;
}
