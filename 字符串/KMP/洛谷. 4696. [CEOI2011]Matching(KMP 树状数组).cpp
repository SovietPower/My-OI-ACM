/*
3.77s	27.32MB
$Description$
给定一个$1\sim n$的排列$p_i$和长为$m$的序列$h_i$，求$h$有多少个字串匹配$p$。$A$匹配$p$指：$A,p$等长且将$A$从小到大排序后，依次为$A_{p_1},A_{p_2},...,A_{p_n}$。
$n,m\leq 10^6$。
$Solution$
**做法1：**
令$pos[p[i]]=i$，$A$匹配$p$，只需满足，$A$和$pos$每个位置在前缀中的排名相等，也就是：$\forall i\in[1,n]$，$A_1,...,A_{i-1}$中小于$A_i$的数的个数 等于 $pos_1,...,pos_{i-1}$中小于$pos_i$的数的个数（不是$p$！）。
记$a_1,...,a_{i-1}$中小于$a_i$的数的个数为$rk_i$，两个串的$rk_i$能直接比较判断串是否相等，也可以用来定义KMP的相等：

* 对$p$求$fail$时，令$j=fail[i-1]$，即当前$border$后缀长为$j$，若**该后缀中**小于$pos_i$的数的个数等于当前匹配的前缀$pos_1\sim pos_j$中的$rk_{j+1}$，则$fail[i]=j+1$；否则$j=fail[j]$，当前匹配后缀缩短（$pos_{i-j}\sim pos_{i-fail[j]-1}$不再对之后$rk_i$产生贡献）。
* 匹配时，维护当前匹配的串的$rk$，判断是否与$p$串的$rk$相等。相等就$++j$，否则$j=fail[j]$，当前串缩短（且$a_{i-j}\sim a_{i-fail[j]-1}$不再对之后$rk_i$产生贡献）。

所以就是KMP改一下判断方式并维护当前$rk$。动态维护$rk$可以直接树状数组，或者麻烦点双向链表。
复杂度$O(n\log n)$或$O(n)$。

**做法2：**
对每个$i$，求出$p_i$前面第一个比$p_i$小的数$pre_{p_i}$，及$p_i$后面第一个比$p_i$小的数$nxt_{p_i}$（用一个双向链表）。
因为匹配的时候**已确定的是$A_1\sim A_{i-1}$，即$p_j=1\sim i-1$的部分**，利用**这个前缀**可以考虑：$A$匹配$p$，只需满足 $\forall i\in[1,n]$，$A_{pre_i}<A_i<A_{nxt_i}$。（写的时候可令$pre_i=pre_i-i$，匹配时设当前下标$x$，$x+pre_i$即当前匹配串中$x$对应$pre_i$位置）
这个东西大概是因为是相对关系，所以也可以维护$border$。
因为匹配是对$p_i=1,2,3,...$的$p_i$依次匹配，**实际是对$pos$匹配而不是$p$**。所以对$pos$求$fail$，过程中匹配与否同样通过$pos_{pre_i}<pos_i<pos_{nxt_i}$决定。

所以可用KMP做，修改一下匹配的条件即可。（但感觉还是好神![/kel](https://img2018.cnblogs.com/blog/1143196/201811/1143196-20181130101416718-194739313.png)）

（只需对KMP的等号匹配修改一下，其它不变）复习一下KMP就两种都写一遍。
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

int P[N],pos[N],rk[N],A[N],Ref[N],fail[N];
struct BIT
{
	int n,t[N];
	#define lb(x) (x&-x)
	void Clear()
	{
		memset(t,0,n+1<<2);
	}
	void Add(int p)
	{
		for(; p<=n; p+=lb(p)) ++t[p];
	}
	void Subd(int p)
	{
		for(; p<=n; p+=lb(p)) --t[p];
	}
	int Query(int p)
	{
		int res=0;
		for(; p; p^=lb(p)) res+=t[p];
		return res;
	}
}T;

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

int main()
{
	const int n=read(),m=read();
	for(int i=1; i<=n; ++i) pos[P[i]=read()]=i;
	for(int i=1; i<=m; ++i) Ref[i]=A[i]=read();
	std::sort(Ref+1,Ref+1+m);
	for(int i=1; i<=m; ++i) A[i]=std::lower_bound(Ref+1,Ref+1+m,A[i])-Ref;
//GetRank
	T.n=n;
	for(int i=1; i<=n; ++i) rk[i]=T.Query(pos[i]), T.Add(pos[i]);
//GetFail
	T.Clear(), rk[n+1]=-1;
	for(int i=2,j=0; i<=n; ++i)
	{
		while(j && T.Query(pos[i])!=rk[j+1])
		{
			for(int k=i-fail[j]-1; k>=i-j; --k) T.Subd(pos[k]);
			j=fail[j];
		}
		if(T.Query(pos[i])==rk[j+1]) ++j, T.Add(pos[i]);
		fail[i]=j;
	}
//Match
	T.Clear(), T.n=m;//值域！
	std::vector<int> ans;
	for(int i=1,j=0; i<=m; ++i)
	{
		while(j && T.Query(A[i])!=rk[j+1])
		{
			for(int k=i-fail[j]-1; k>=i-j; --k) T.Subd(A[k]);
			j=fail[j];
		}
		if(T.Query(A[i])==rk[j+1])
		{
			T.Add(A[i]);
			if(++j==n) ans.pb(i-n+1);
		}
	}
	printf("%d\n",ans.size());
	for(auto v:ans) printf("%d ",v); pc('\n');

	return 0;
}
