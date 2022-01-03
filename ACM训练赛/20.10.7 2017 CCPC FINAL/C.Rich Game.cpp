//¼òµ¥¶þ·Ö¡£
#include <bits/stdc++.h>
#define gc() getchar()
typedef long long LL;
const int N=1e5+5;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
bool Check(int win,int x,int y,int k)
{
	int now=11*(k-win)*y, tmp=11*x-9*y;
	return 1ll*win*tmp>=now;
}

int main()
{
	for(int Ts=1,TS=read(); Ts<=TS; ++Ts)
	{
		int y=read(),x=read(),K=read();
		if(x<y) {printf("Case #%d: %d\n",Ts,K); continue;} 
		int l=0,r=K,mid,ans=0;
		while(l<=r)
			if(Check(mid=l+r>>1,x,y,K)) ans=mid, l=mid+1;
			else r=mid-1;
		printf("Case #%d: %d\n",Ts,ans);
	}

	return 0;
}
