#include <set>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp std::make_pair
#define pr std::pair<int,int>
#define pc putchar
#define gc() getchar()
#define mod 4294967296ll
typedef long long LL;
typedef unsigned int uint;
const int N=2e7+7;

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline uint readu()
{
	uint now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
//void Solve2()
//{
//	static int AA[N],sk[N];
//	sk[0]=1;
//	int n=read();
//	for(int i=1; i<=n; ++i) AA[i]=read();
//	LL Ans=1e18;
//	int A1=AA[1],A2=AA[2],nmn=0,pmn=0,pmx=0,top=0;
//	bool exist_neg=0,exist_z=0;//A1<0||A2<0;
//
//	if(A1<0) nmn=A1, exist_neg=1, sk[++top]=A1;
//	else if(A1>0) pmn=pmx=A1;
//	else exist_z=1;
//
//	int A=A2;
//	if(exist_neg && !A) Ans=std::min(Ans,0ll);
//	else if(exist_z && A>0) Ans=std::min(Ans,0ll);
//	if(A>0)
//	{
//		if(nmn) Ans=std::min(Ans,1ll*nmn*A);
//		else if(pmn<A) Ans=std::min(Ans,1ll*pmn*A);
//		if(pmn) pmn=std::min(pmn,A), pmx=std::max(pmx,A);
//		else pmn=pmx=A;
//	}
//	else if(A<0)
//	{
//		sk[top]<A && (Ans=std::min(Ans,1ll*A*sk[top]));
//		while(sk[top]<A) --top;
//		sk[++top]=A;
//		if(A1<A) Ans=std::min(Ans,1ll*A1*A);
//		if(nmn) nmn=std::min(nmn,A);
//		else nmn=A;
//	}
//	else if(!A) exist_z=1;
//
//	for(int i=3,A; i<=n; ++i)
//	{
//		A=AA[i];
////		printf("AA[%d]=%d\n",i,A);
//		if(exist_neg && !A) Ans=std::min(Ans,0ll);
//		else if(exist_z && A>0) Ans=std::min(Ans,0ll);
//		if(A>0)
//		{
//			if(nmn) Ans=std::min(Ans,1ll*nmn*A);
//			else if(pmn<A) Ans=std::min(Ans,1ll*pmn*A);
//			if(pmn) pmn=std::min(pmn,A), pmx=std::max(pmx,A);
//			else pmn=pmx=A;
//		}
//		else if(A<0)
//		{
//			while(top && sk[top-1]<A) --top;
//			sk[top]<A && (Ans=std::min(Ans,1ll*A*sk[top]));
////			printf("top:%d sk[top]:%d\n",top,sk[top]);
//			while(sk[top]<A) --top;
//			sk[++top]=A;
//			if(nmn) nmn=std::min(nmn,A);
//			else nmn=A;
//		}
//		else if(!A) exist_z=1;
//	}
//	if(Ans==1e18) puts("IMPOSSIBLE");
//	else printf("%I64d\n",Ans);
//}
#define int LL
void Solve()
{
	static int sk[N];
	sk[0]=1;
	int top=0,n=read(),l=read(),r=read(); uint x=readu(),y=readu(),z=readu(),b1=readu(),b2=readu();
	LL Ans=9e18;
	LL len=(LL)r-l+1; int A1=b1%len+l,A2=b2%len+l,nmn=0,pmn=0,pmx=0;
	bool exist_neg=0,exist_z=0;//A1<0||A2<0;

	if(A1<0) nmn=A1, exist_neg=1, sk[++top]=A1;
	else if(A1>0) pmn=pmx=A1;
	else exist_z=1;

	int A=A2;
	if(exist_neg && !A) Ans=std::min(Ans,0ll);
	else if(exist_z && A>0) Ans=std::min(Ans,0ll);
	if(A>0)
	{
		if(nmn) Ans=std::min(Ans,1ll*nmn*A);
		else if(pmn<A) Ans=std::min(Ans,1ll*pmn*A);
		if(pmn) pmn=std::min(pmn,A), pmx=std::max(pmx,A);
		else pmn=pmx=A;
	}
	else if(A<0)
	{
		sk[top]<A && (Ans=std::min(Ans,1ll*A*sk[top]));
		while(sk[top]<A) --top;
		sk[++top]=A;
		exist_neg=1;
		if(A1<A) Ans=std::min(Ans,1ll*A1*A);
		if(nmn) nmn=std::min(nmn,A);
		else nmn=A;
	}
	else if(!A) exist_z=1;

	uint b;
	for(int i=3,A; i<=n; ++i)
	{
		b=(b1*x+b2*y+z)%mod, A=b%len+l;
//		printf("A[%d]=%d\n",i,A);
		if(exist_neg && !A) Ans=std::min(Ans,0ll);
		else if(exist_z && A>0) Ans=std::min(Ans,0ll);
		if(A>0)
		{
			if(nmn) Ans=std::min(Ans,1ll*nmn*A);
			else if(pmn<A) Ans=std::min(Ans,1ll*pmn*A);
			if(pmn) pmn=std::min(pmn,A), pmx=std::max(pmx,A);
			else pmn=pmx=A;
		}
		else if(A<0)
		{
			while(top && sk[top-1]<A) --top;
			sk[top]<A && (Ans=std::min(Ans,1ll*A*sk[top]));
//			printf("top:%d sk[top]:%d\n",top,sk[top]);
			while(sk[top]<A) --top;
			sk[++top]=A;
			exist_neg=1;
			if(nmn) nmn=std::min(nmn,A);
			else nmn=A;
		}
		else if(!A) exist_z=1;
		b1=b2, b2=b;
	}
	if(Ans==9e18) puts("IMPOSSIBLE");
	else printf("%I64d\n",Ans);
}

signed main()
{
	for(int T=read(); T--; Solve());
	return 0;
}
