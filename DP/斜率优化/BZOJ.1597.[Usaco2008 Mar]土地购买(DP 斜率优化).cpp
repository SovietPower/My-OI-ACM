/*
����������غ������DP 
����ͬһ�飬��ֵΪmax{ai}*max{bi}����Ȼ����С������������ǲ����������� 
�����Ƕ����������лᱻ���������ض����������� 
�Ȱ�Ai��Bi�������򣬵�һ�ؼ���Ai����ô����B[i-1]<Bi�ľͿ���ɾ���� 
���ʣ�µ�Ai����������Bi���ǽ����� 
Ȼ��Ϳ���DP�� 

ע: Biһ�������彵��ģ�������ֻ�Ƚ��������� 
*/
#include<cstdio>
#include<cctype>
#include<algorithm>
#define gc() getchar()
typedef long long LL;
const int N=5e4+5;

int n,cnt,q[N];
LL f[N];
struct Land
{
	LL a,b;
	inline bool operator <(const Land &x)const {return a==x.a?b<x.b:a<x.a;}
}A[N];

inline int read()
{
	int now=0,f=1;register char c=gc();
	for(;!isdigit(c);c=gc()) if(c=='-') f=-1;
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now*f;
}
inline LL X(int j,int k) {return A[k+1].b-A[j+1].b;}
inline LL Y(int j,int k) {return f[j]-f[k];}
inline LL Calc(int i,int p) {return f[p]+A[i].a*A[p+1].b;}
inline double Slope(int i,int j) {return 1.0*Y(i,j)/X(i,j);}

int main()
{
	n=read();
	for(int i=1;i<=n;++i) A[i].a=read(),A[i].b=read();
	std::sort(A+1,A+1+n);
	for(int i=1;i<=n;++i)
	{
		while(cnt && A[i].b>=A[cnt].b) --cnt;
		A[++cnt]=A[i];
	}
//WA:for(int i=1;i<n;++i)
//		if(t[i].b>t[i+1].b)
//			A[++cnt]=t[i].a, B[cnt]=t[i].b;
//	A[++cnt]=t[n].a, B[cnt]=t[n].b;
	int h=1,t=1;
	for(int i=1;i<=cnt;++i)
	{
		while(h<t && Y(q[h+1],q[h])<A[i].a*X(q[h+1],q[h])) ++h;
		f[i]=Calc(i,q[h]);
		while(h<t && Y(i,q[t])*X(q[t],q[t-1])<=Y(q[t],q[t-1])*X(i,q[t])) --t;
//		while(h<t && Slope(i,q[t])<=Slope(q[t],q[t-1])) --t;//a little slower
		q[++t]=i;
	}
	printf("%lld",f[cnt]);

	return 0;
}
