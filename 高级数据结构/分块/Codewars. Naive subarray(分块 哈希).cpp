/*
$Description$
������Ϊ$n$������$A_i$�����ж��ٸ����䣬�����������������ĳ��ִ���Ϊ������
$n\leq 2\times10^5,\ A_i\leq 10^5$��

$Solution$
Ϊÿ������ֵһ�����Ȩֵ$val_i$�����������������ִ���Ϊ�������ȼ��� ��������Ȩֵ������ ���� ������ֹ���Ȩֵ�����͡�
��$i$Ϊ��ǰ����������Ҷ˵㣬$[j,i]$����Ȩֵ����Ϊ$f_j$��$[j,i]$���ֹ���Ȩֵ����Ϊ$g_j$����$i$Ϊ�Ҷ˵�ĺϷ�������Ϊ$\sum_{j\leq i}[f_j=g_j]$����$las_x$Ϊ$x$�ϴγ��ֹ���λ�á�
��ôÿ��ö��ǰ׺$[1,i]$ʱ��������Ϊ����$f_1, ..., f_i$���$val_{A_i}$����$g_{las_{A_i}+1}, ..., g_i$���$val_{A_i}$����$f_j=g_j$��$f_j\ \mathbb{xor}\ g_j=0$�ĸ�����
��$h_j=f_j\ \mathbb{xor}\ g_j$���������Ϊ����$h_1, ..., h_{las_{A_i}}$���$val_{A_i}$����$h_j=0$�ĸ�����

���Ծ��ǣ��������һ��ֵ�����������0�����ĸ��������Էֿ顣
��$cnt[b][k]$��ʾ��$b$����$k$�ĳ��ִ�������ÿ���޸ģ����������$tag[b]$������ɢ���ֽ��ı��ֵ��$cnt[b]$��ɾ�������£�ÿ��ѯ�ʣ��������$cnt[b][tag[b]]$������ɢ���ֱ�����ֵΪ$tag[b]$�ĸ�����

$cnt[b]$������map��Ҳ���Թ�ϣ������ù�ϣ���ڸ���$cnt[b]$ʱ����ֱ�ӽ�����$cnt[b]$��ϣ����ա���ϣ��̫��ɾ������
���Ӷ�$O(n\sqrt n\log n)$��$O(n\sqrt n)$��
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
		Get_head(0), AE(0, 0, v);//ע���ڲ���0ǰ������0�ı�ͷ����ʵӦ����Insert(0)ȥ���롣
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
LL solve(std::array<int,S> A)//ע��A�±��0��ʼ��
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
