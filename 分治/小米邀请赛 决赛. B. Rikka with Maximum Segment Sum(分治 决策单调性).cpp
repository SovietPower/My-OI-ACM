/*
25ms	2444kb
$Description$
��$mss(A)$Ϊ����A������Ӷκͣ���$\sum_{1\leq i\leq j\leq n}mss([A_i,...,A_j])$��
$n\leq 10^5$��
$Solution$
�ǲ����ܹ����߶�������Ҳ���ǿ�������ϲ����ģ������Կ��ǹ�����$mid$�Ĵ𰸰���Ҳ���Ƿ��Σ���
�뵽���ξ����׵��ˡ�

����������Ӷκ͵Ĺ��̣����Ƿ��Ρ�
���ǹ�$mid$������$[l,r]$����Ҫô��$[l,mid]$������һ�Σ�Ҫô��$[mid+1,r]$������һ�Σ�Ҫô��$[l',mid]$��$[mid+1,r']$�����κ͡���$r$���ҹ����д𰸻�����һ���������ٱ���������
��һ��ֱ���㡣
�ڶ������׷��֣����Ž��ȡֵ�����ɸ���$p_i$����Խ�������Ž�$f(p_i)=\text{mss}(mid+1,p_i)$Խ��Ҳ����$r$��$[p_{i-1}+1,p_i]$��ʱ�ڶ�������Ĵ𰸾���$f(p_i)$��
������ͬ��$\max_{l'}[l',mid]$ֱ����$[mid+1,r']$���Ž��ȡֵҲ�����ɸ���$p_i$��Խ����$g(p_i)=\text{sum}(mid+1,p_i)$Խ��$r$��$[p_{i-1}+1,p_i]$�д�Ϊ$g(p_i)$��
��$l$��������Ĺ����е�һ������Ĺ����ǵ����ģ������и���λ�õ�$r$ѡ���һ��������𰸶���ѡ�������ͬ����������׵�����ѡ����λ�õ�$r$����ࡣ���Կ����õ����Ի�������Զ��������Ϊ���Ž��$r$���䣬�������һ�¸������ɡ�
��û��Ҫ�ҳ����ŵ���Щ$p_i$����$f(i)=\max\{f(i),f(i-1)\},\ g(i)=\max\{g(i),g(i-1)\}$Ȼ��Ϳ��Ե�����/����λ�ã�
���Ӷ�$O(n\log n)$��$O(n\log^2n)$�����������״��������ɵ�ˣ�

˼·�ܼ򵥣�ϸ�ڿ����е�ࣿ����д��һ������ͦ����˼�ġ�
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb push_back
typedef long long LL;
typedef unsigned long long ull;
const int N=1e5+5,INF=1e9+10;

int A[N];
LL f[N],g[N];
ull Ans;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
void Solve(const int l,const int r)
{
	if(l>r) return;
	if(l==r) {Ans+=A[l]; return;}
	int m=l+r>>1;
//R //�����ô����д�о����а� 
	{
		LL sum=0,mxMR=-INF,now=0,ansR=-INF;
		for(int i=m+1; i<=r; ++i)//f:��mid������mss  g:������mid������mss 
		{
			sum+=A[i], mxMR=std::max(sum,mxMR);
			now=std::max(now,0ll)+A[i], ansR=std::max(ansR,now);
			f[i]=mxMR, g[i]=ansR;//f:f g:d
		}
	}
//L
	{
		LL sum=0,mxLM=-INF,now=0,ansL=-INF;
		for(int i=m; i>=l; --i)
		{
			sum+=A[i], mxLM=std::max(sum,mxLM);
			now=std::max(now,0ll)+A[i], ansL=std::max(ansL,now);
			f[i]=mxLM, g[i]=ansL;
		}
	}
	ull now=0,res=0;//ull!
	for(int i=l; i<=m; ++i) res+=g[i];//[l~mid,mid]
	for(int i=m+1; i<=r; ++i) now+=g[i];

	int p1=m+1,p2=m+1,cnt1=0,cnt2=0;
	//[mid+1,p1):g[i]*cnt1  [p1,p2):(f[i]+f[r])*cnt2  [p2,r]:g[r]
	//g[p] -> f[i]+f[p] -> g[i]
	//��ߵ�f[i],g[i]��Ҫ��cntά�����뵱ǰi�йأ����ұߵ���nowά������i�޹أ� 
	for(int i=m; i>=l; --i)
	{
		while(p2<=r && g[p2]<f[i]+f[p2]) now+=f[p2]-g[p2], ++p2, ++cnt2;
		while(p1<p2 && f[i]+f[p1]<g[i]) now-=f[p1], ++p1, --cnt2, ++cnt1;
		while(p2<=r && p1==p2 && g[p2]<g[i]) now-=g[p2], ++p1, ++p2, ++cnt1;
		res+=now+g[i]*cnt1+f[i]*cnt2;
	}
	Ans+=res;
	Solve(l,m-1), Solve(m+1,r);
}

int main()
{
	const int n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	Solve(1,n), printf("%llu\n",Ans);

	return 0;
}
