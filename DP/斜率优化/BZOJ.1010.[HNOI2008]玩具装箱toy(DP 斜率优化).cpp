//斜率优化 不说了 
#include<cstdio>
#include<cctype>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e4+5,MAXIN=1e5;

int n,C,S[N],q[N];
char IN[MAXIN],*SS=IN,*TT=IN;
LL f[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL Squ(LL x) {return x*x;}
inline LL X(int j,int k)
{
	return (S[j]-S[k])<<1;
}
inline LL Y(int j,int k)
{
	return f[j]+Squ(S[j]+C)-(f[k]+Squ(S[k]+C));
}

int main()
{
	n=read(),C=read()+1;
	for(int i=1;i<=n;++i) S[i]=S[i-1]+read()+1;
//	for(int i=1;i<=n;++i) S[i]+=i;
	int h=1,t=1; q[1]=0;
	for(int i=1;i<=n;++i)
	{
		while(h<t && Y(q[h+1],q[h])<=S[i]*X(q[h+1],q[h])) ++h;
		f[i]=f[q[h]]+Squ(S[i]-S[q[h]]-C);
		while(h<t && Y(i,q[t])*X(q[t],q[t-1])<=Y(q[t],q[t-1])*X(i,q[t])) --t;
		q[++t]=i;
	}
	printf("%lld",f[n]);

	return 0;
}
