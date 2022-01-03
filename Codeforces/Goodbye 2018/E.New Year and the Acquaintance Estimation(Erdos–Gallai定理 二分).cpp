/*
187ms	8200KB
~~��˵EֻҪ������Erdos�CGallai����Ȼ���뵽���֣���������ô...��~~
������ǣ����$d_{n+1}$���ڶ���ʱ����������$d_1,d_2,...,d_{n+1}$�ɼ�ͼ����
����ö��$d_{n+1}$������һ�����������ж����Ƿ�Ϸ�������Erdos�CGallai�������Ӷ�$O(n)$���������ڵĸ��Ӷ���$O(n^2)$�ġ�
�����������ǻ����Բ��벢��֤��
1. �����ֶ�����������ͼ�����е�Ķ���֮��Ϊż������$d_{n+1}$����ż�Կ���ȷ����
2. ����������$d_{n+1}$һ����һ�����������䡣
�������ǾͿ��Զ����ˡ�
����Ҫ�õ�����ĳ�����䣬�ֱ�������Ҷ˵㣬������Ҫ����һ�¡�
��$n=n+1$��дһ��Erd?s�CGallai�����ʽ�ӣ�$$\sum_{i=1}^kd_i\leq k(k-1)+\sum_{i=k+1}^n\min(d_i,k)$$
����$n$�Ķ���$d_n=mid$��Ȼ��$sort$һ�¶������С�
��С����ö��$k$��ʱ�򣬼�$left$Ϊ��ʽ��ֵ��$right$Ϊ��ʽ��ֵ����һֱ��$left\leq right$����Ȼ$mid$���С�
������$left>right$������Ҫô��С$left$��Ҫô����$right$����Ψһ�ܸı�ľ���$n$�Ķ���$mid$��
����������$mid\geq d_k$��Ӱ����ʽ�������ǿ��Լ�С$mid$ʹ�����кϷ���Ҳ���Ǵ�ƫ��
��$mid<d_k$��Ӱ����ʽ������������$mid$��Ҳ���Ǵ�ƫС��
����ȷ����ƫ��ƫС���Ϳ��Զ��ֳ������ˡ����Ӷ�$O(n\log n)$��
[����һЩԤ����Ҳ��������$O(n)$](http://codeforces.com/contest/1091/submission/47777020)��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 500000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=5e5+5;

int A[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Check(const int n,const int mid)
{
	static int d[N];
	static LL sum[N];
	A[n]=-1;
	for(int i=1,p=1; i<=n; ++i) d[i]=(p==i&&mid>A[p])?mid:A[p++], sum[i]=sum[i-1]+d[i];
	LL vl,vr;
	for(int k=1,p=n; k<=n; ++k)
	{
		while(p>k && d[p]<k) --p;
		vl=sum[k], vr=1ll*k*(k-1)+1ll*(std::max(p,k)-k)*k+sum[n]-sum[std::max(p,k)];
		if(vl>vr) return mid<d[k]?-1:1;
	}
	return 0;
}

int main()
{
	int n=read(),parity=0;
	for(int i=1; i<=n; ++i) parity^=(A[i]=read())&1;
	std::sort(A+1,A+1+n,std::greater<int>());

	int l=0,r=n-parity>>1,L=0,R=-1,mid;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)>=0) L=mid, r=mid-1;
		else l=mid+1;
	l=0,r=n-parity>>1;
	while(l<=r)
		if(Check(n+1,(mid=l+r>>1)*2+parity)<=0) R=mid, l=mid+1;
		else r=mid-1;

	if(L>R) puts("-1");
	else for(int i=L; i<=R; ++i) printf("%d ",i*2+parity);

	return 0;
}
