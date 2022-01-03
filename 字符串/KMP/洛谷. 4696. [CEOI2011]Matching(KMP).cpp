/*
912ms	31.11MB
$Description$
����һ��$1\sim n$������$p_i$�ͳ�Ϊ$m$������$h_i$����$h$�ж��ٸ��ִ�ƥ��$p$��$A$ƥ��$p$ָ��$A,p$�ȳ��ҽ�$A$��С�������������Ϊ$A_{p_1},A_{p_2},...,A_{p_n}$��
$n,m\leq 10^6$��
$Solution$
**����1��**
��$pos[p[i]]=i$��$A$ƥ��$p$��ֻ�����㣬$A$��$pos$ÿ��λ����ǰ׺�е�������ȣ�Ҳ���ǣ�$\forall i\in[1,n]$��$A_1,...,A_{i-1}$��С��$A_i$�����ĸ��� ���� $pos_1,...,pos_{i-1}$��С��$pos_i$�����ĸ���������$p$������
��$a_1,...,a_{i-1}$��С��$a_i$�����ĸ���Ϊ$rk_i$����������$rk_i$��ֱ�ӱȽ��жϴ��Ƿ���ȣ�Ҳ������������KMP����ȣ�

* ��$p$��$fail$ʱ����$j=fail[i-1]$������ǰ$border$��׺��Ϊ$j$����**�ú�׺��**С��$pos_i$�����ĸ������ڵ�ǰƥ���ǰ׺$pos_1\sim pos_j$�е�$rk_{j+1}$����$fail[i]=j+1$������$j=fail[j]$����ǰƥ���׺���̣�$pos_{i-j}\sim pos_{i-fail[j]-1}$���ٶ�֮��$rk_i$�������ף���
* ƥ��ʱ��ά����ǰƥ��Ĵ���$rk$���ж��Ƿ���$p$����$rk$��ȡ���Ⱦ�$++j$������$j=fail[j]$����ǰ�����̣���$a_{i-j}\sim a_{i-fail[j]-1}$���ٶ�֮��$rk_i$�������ף���

���Ծ���KMP��һ���жϷ�ʽ��ά����ǰ$rk$����̬ά��$rk$����ֱ����״���飬�����鷳��˫������
���Ӷ�$O(n\log n)$��$O(n)$��

**����2��**
��ÿ��$i$�����$p_i$ǰ���һ����$p_i$С����$pre_{p_i}$����$p_i$�����һ����$p_i$С����$nxt_{p_i}$����һ��˫��������
��Ϊƥ���ʱ��**��ȷ������$A_1\sim A_{i-1}$����$p_j=1\sim i-1$�Ĳ���**������**���ǰ׺**���Կ��ǣ�$A$ƥ��$p$��ֻ������ $\forall i\in[1,n]$��$A_{pre_i}<A_i<A_{nxt_i}$����д��ʱ�����$pre_i=pre_i-i$��ƥ��ʱ�赱ǰ�±�$x$��$x+pre_i$����ǰƥ�䴮��$x$��Ӧ$pre_i$λ�ã�
��������������Ϊ����Թ�ϵ������Ҳ����ά��$border$��
��Ϊƥ���Ƕ�$p_i=1,2,3,...$��$p_i$����ƥ�䣬**ʵ���Ƕ�$pos$ƥ�������$p$**�����Զ�$pos$��$fail$��������ƥ�����ͬ��ͨ��$pos_{pre_i}<pos_i<pos_{nxt_i}$������

���Կ���KMP�����޸�һ��ƥ����������ɡ������о����Ǻ���![/kel](https://img2018.cnblogs.com/blog/1143196/201811/1143196-20181130101416718-194739313.png)��

��ֻ���KMP�ĵȺ�ƥ���޸�һ�£��������䣩��ϰһ��KMP�����ֶ�дһ�顣
```cpp
void GetFail(char *s)//pattern
{
	int m=strlen(s+1);
	for(int i=2,j=0; i<=m; ++i)
	{
		while(j && s[i]!=s[j+1]) j=fail[j];
		fail[i]=s[i]==s[j+1]?++j:0;
	}
}
void Match(char *p,char *s)
{
	int j=0,n=strlen(s+1),m=strlen(p+1);
	for(int i=1; i<=n; ++i)
	{
		while(j && s[i]!=p[j+1]) j=fail[j];
		if(s[i]==p[j+1]) ++j;
		if(j==m) printf("%d\n",i-m+1);
	}
}
```
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back
typedef long long LL;
const int N=1e6+5;

int P[N],pos[N],L[N],R[N],pre[N],nxt[N],A[N],fail[N];

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}
inline bool OK(int *A,int x,int i)
{
	return A[x+pre[i]]<=A[x]&&A[x+nxt[i]]>=A[x];
//	return (!pre[i]||A[x+pre[i]]<A[x])&&(!nxt[i]||A[x+nxt[i]]>A[x]);
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) pos[P[i]=read()]=i;
	for(int i=1; i<=m; ++i) A[i]=read();
//Get Pre/Next
	for(int i=1; i<=n; ++i) L[i]=i-1, R[i]=i+1;
	R[n]=0;//
	for(int i=n; i; --i)
	{
		int x=pos[i];
		if(L[x]) pre[i]=P[L[x]]-i;
		if(R[x]) nxt[i]=P[R[x]]-i;
		L[R[x]]=L[x], R[L[x]]=R[x];
	}
//GetFail
	for(int i=2,j=0; i<=n; ++i)
	{
		while(j && !OK(pos,i,j+1)) j=fail[j];
		fail[i]=OK(pos,i,j+1)?++j:0;
	}
//Match
	std::vector<int> ans;
	for(int i=1,j=0; i<=m; ++i)
	{
		while(j && !OK(A,i,j+1)) j=fail[j];
		if(OK(A,i,j+1)) ++j==n&&(ans.pb(i-n+1),j=fail[j]);//��Ϊ�ж����⣬ƥ����Ҫ�ֶ���һ��j��
	}
	printf("%d\n",ans.size());
	for(auto v:ans) printf("%d ",v); pc('\n');

	return 0;
}
