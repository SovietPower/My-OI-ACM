/*
56872kb	1472ms
题意：给出$1\sim n$的一个排列的一个最长上升子序列，求原排列可能的种类数。
$n\leq 15$。
$n$很小，参照[HDU 4352]这道题，我们直接把求$LIS$时的状态存下来做DP数组的状态。
状态就是那个单调递增的单调栈。每个数会有三种可能：没入过栈，现在在栈中，之前在栈中但是被替换掉了。
所以用一个$n$位三进制数表示单调栈的状态$s$。然后枚举状态$s$，再枚举一个没出现过的数，很好转移。
转移时注意$LIS$长度不能超过$k$，以及要能形成给定的$LIS$即可（现在加入的数如果在给定的$LIS$中，那它在$LIS$中的前一个数要出现过，后一个数没出现过）。
复杂度$O(n3^n)$。加点剪枝问题不大。
其实可以把非$0$的状态扔到一个`queue`里，不用$3^n$地`for`。
*/
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int N=20;

int main()
{
	static int A[N],id[N],pw[N],sta[N],lis[N],f[14348909];

	int n,K; scanf("%d%d",&n,&K);
	for(int i=1; i<=K; ++i) scanf("%d",&A[i]), id[--A[i]]=i;
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*3;

	int ans=0;
	f[0]=1, sta[A[0]=n]=1, sta[A[K+1]=n+1]=0;
	for(int s=0,v; s+1<pw[n]; ++s)
		if((v=f[s]))
		{
			int cnt=0,tot=0;
			for(int i=0,tmp=s; i<n; ++i,tmp/=3)
				tot+=((sta[i]=tmp%3)>0), sta[i]==1&&(lis[cnt++]=i);
			if(tot==n) {ans+=v; continue;}//三进制啊...最后答案不只是f[pw[n]-1] 
			lis[cnt]=20;
			for(int i=0; i<n; ++i)
				if(!sta[i])
				{
					if(id[i] && (!sta[A[id[i]-1]]||sta[A[id[i]+1]])) continue;
					int j=0;
					while(lis[j]<i) ++j;
					if(j==K) continue;//length>K
					f[s+pw[i]+(j==cnt?0:pw[lis[j]])]+=v;//pw[lis[j]] not pw[j]..
				}
		}
	printf("%d\n",ans);

	return 0;
}
