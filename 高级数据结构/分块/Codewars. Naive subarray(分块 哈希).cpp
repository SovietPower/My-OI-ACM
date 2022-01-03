/*
$Description$
给定长为$n$的序列$A_i$，求有多少个区间，满足区间中所有数的出现次数为奇数。
$n\leq 2\times10^5,\ A_i\leq 10^5$。

$Solution$
为每个数赋值一个随机权值$val_i$。则区间所有数出现次数为奇数，等价于 区间所有权值的异或和 等于 区间出现过的权值的异或和。
设$i$为当前计算区间的右端点，$[j,i]$所有权值异或和为$f_j$，$[j,i]$出现过的权值异或和为$g_j$，以$i$为右端点的合法区间数为$\sum_{j\leq i}[f_j=g_j]$。记$las_x$为$x$上次出现过的位置。
那么每次枚举前缀$[1,i]$时，操作即为：对$f_1, ..., f_i$异或$val_{A_i}$，对$g_{las_{A_i}+1}, ..., g_i$异或$val_{A_i}$，求$f_j=g_j$即$f_j\ \mathbb{xor}\ g_j=0$的个数。
令$h_j=f_j\ \mathbb{xor}\ g_j$，则操作即为：对$h_1, ..., h_{las_{A_i}}$异或$val_{A_i}$，求$h_j=0$的个数。

所以就是：区间异或一个值，求区间等于0的数的个数。可以分块。
记$cnt[b][k]$表示块$b$中数$k$的出现次数，则每次修改，对整块更新$tag[b]$，对零散部分将改变的值从$cnt[b]$里删掉并更新；每次询问，对整块查$cnt[b][tag[b]]$，对零散部分暴力查值为$tag[b]$的个数。

$cnt[b]$可以用map，也可以哈希（如果用哈希，在更新$cnt[b]$时不妨直接将整个$cnt[b]$哈希表清空。哈希表不太好删除）。
复杂度$O(n\sqrt n\log n)$或$O(n\sqrt n)$。
*/
#include <bits/stdc++.h>
#define pc putchar
#define gc() getchar()
#define pb emplace_back

inline int read()
{
	int now=0,f=1; char c=gc();
	for(;!isdigit(c);c=='-'&&(f=-1),c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now*f;
}

typedef long long LL;
typedef unsigned long long ull;
const int N=2e5+5,M=1e5+5,B=450,B_size=450;
const int mod=2099;

int las[M],bel[N],L[B],R[B];
ull val[M],seq[N],tag[B];
std::mt19937_64 Rand(19511016);

struct Hash
{
	int Enum,Time,time[mod+2],H[mod+2],nxt[B_size+2],cnt[B_size+2];
	ull to[B_size+2];

	inline void AE(int u,ull v,int t)
	{
		to[++Enum]=v, nxt[Enum]=H[u], cnt[Enum]=t, H[u]=Enum;
	}
	void Clear()
	{
		++Time, Enum=0;
//		memset(H,0,sizeof H);
	}
	void Init(int v)
	{
		Clear();
		Get_head(0), AE(0, 0, v);//注意在插入0前，更新0的表头！其实应该用Insert(0)去插入。
	}
	int Get_head(int x)
	{
		return time[x]==Time?H[x]:(time[x]=Time,H[x]=0);
	}
	int Query(ull v)
	{
		for(int i=Get_head(v%mod); i; i=nxt[i])
			if(to[i]==v) return cnt[i];
		return 0;
	}
	void Insert(ull v)
	{
		for(int i=Get_head(v%mod); i; i=nxt[i])
			if(to[i]==v) return void(++cnt[i]);
		AE(v%mod, v, 1);
	}
}cnt[B];

void Update(int p,ull v)
{
	if(!p) return;
	int b=bel[p];
	for(int i=1; i<b; ++i) tag[i]^=v;
	
	cnt[b].Clear();
	for(int i=L[b]; i<=p; ++i) cnt[b].Insert(seq[i]^=v);
	for(int i=R[b]; i>p; --i) cnt[b].Insert(seq[i]);
}
int Query(int p)
{
	int b=bel[p], ans=0; ull v=tag[b];
	for(int i=1; i<b; ++i) ans+=cnt[i].Query(tag[i]);
	for(int i=L[b]; i<=p; ++i) ans+=(seq[i]==v);
	return ans;
}
template<std::size_t S>
LL solve(std::array<int,S> A)//注意A下标从0开始！
{
	int n=A.size();
	for(int i=1; i<=n; ++i) seq[i]=0, las[A[i-1]]=0;
	for(int i=1; i<=n; ++i) if(!val[A[i-1]]) val[A[i-1]]=Rand();

	for(int i=1; i<=n; ++i) bel[i]=(i-1)/B_size+1;
	int tot=bel[n];
	for(int i=1; i<=tot; ++i) L[i]=(i-1)*B_size+1, R[i]=i*B_size;
	R[tot]=std::min(R[tot], n);

	for(int i=1; i<=tot; ++i) tag[i]=0, cnt[i].Init(R[i]-L[i]+1);

	LL ans=0;
	for(int i=1; i<=n; ++i)
		Update(las[A[i-1]],val[A[i-1]]), ans+=Query(i), las[A[i-1]]=i;
	return ans;
}

int main()
{
	std::array<int, 27> A2 = {6,1,7,4,6,7,1,4,7,1,4,6,6,7,4,1,6,4,7,1,4,5,3,2,1,6,9};
	printf("%lld\n",solve(A2));//114
	std::array<int, 15> A = {2, 5, 2, 3, 6, 7, 8, 23, 23, 13, 65, 31, 3, 4, 3};
	printf("%lld\n",solve(A));//53
	

	return 0;
}
