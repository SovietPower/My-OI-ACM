/*
342ms	11700KB
$Description$
����һ������$h_i$����$\max_{1\leq i<j\leq n}(h_i+h_j)*(j-i)$��
$n\leq10^6$��
$Solution$
���������⿼�Ƿ��Σ�������$mid$������Ĵ𰸡�
���Է��ֶ��������ֻ�е�����$h_i$�����õģ�ͬ���ұ�����ֻ��Ҫ���ǵݼ���$h_i$��
�ҳ���������Щ$h_i$��Ϊ$A_i$��Ȼ���Ƕ��������ÿ��$A_i$�ҵ��ұ�����ƥ����Ǹ�λ��$p_i$����ô$p_i$�ǵ������ӵġ������������άƽ�������㹹�ɵľ�����������߸������һ�£�
Ҳ����������ߵ����ԡ����λ�һ��д������Ū���������еĵ�����$h_i$��Ȼ��ֱ�ӱ��������ǰ����$mid$������ƥ���$p$��Ȼ���$[l,mid-1]$��$[mid+1,r]$�����ٵݹ飬���迼�ǵľ��߷�ΧΪ$[L,p]$��$[p,R]$��
ÿ�θ��Ӷ�$O(���߷�Χ)$����ÿ��$O(n)$��ÿ���ɾ$1,2,4,...$��Ԫ��������$O(\log)$�㣬���Ӷ�$O(n\log n)$��
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
typedef long long LL;
const int N=1e6+5;

int A1[N],A2[N],h[N];
LL Ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
#define Calc(p) (1ll*(h[A1[mid]]+h[A2[p]])*(A2[p]-A1[mid]))
void Solve(int l1,int r1,int l2,int r2)
{
	if(l1>r1) return;
	int mid=l1+r1>>1,pos=l2;
	for(int i=l2+1; i<=r2; ++i)
		if(Calc(i)>Calc(pos)) pos=i;
	Ans=std::max(Ans,Calc(pos));
	Solve(l1,mid-1,pos,r2), Solve(mid+1,r1,l2,pos);
}

int main()
{
	int n=read();
	for(int i=1; i<=n; ++i) h[i]=read();
	int cnt1=1,cnt2=1; A1[1]=1, A2[1]=n;
	for(int i=2; i<=n; ++i)
		if(h[i]>h[A1[cnt1]]) A1[++cnt1]=i;
	for(int i=n-1; i; --i)
		if(h[i]>h[A2[cnt2]]) A2[++cnt2]=i;
	Solve(1,cnt1,1,cnt2), printf("%lld\n",Ans);

	return 0;
}
