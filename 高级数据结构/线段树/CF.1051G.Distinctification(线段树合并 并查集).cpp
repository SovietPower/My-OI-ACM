/*
483ms	161100KB
$Description$
����$n$������$A_i,B_i$������Խ���������������ֲ�����
1. ѡ��һ��λ��$i$����$A_i=A_i+1$������$B_i$���������һ��λ��$j$������$A_i=A_j,\ i\neq j$���ſ��Խ��С�
2. ѡ��һ��λ��$i$����$A_i=A_i-1$������$-B_i$���������һ��λ��$j$������$A_i=A_j+1$���ſ��Խ��С�
����Ҫ��������$i\in[1,n]$����ʹ��$A_1,A_2,...,A_i$������ͬ����С�����Ƕ��١�
$n,A_i\leq2\times10^5,\ 1\leq B_i\leq n�һ�����ͬ$��

$Solution$
�������$A_i$������ͬ��������$A_i+1=A_j$������Խ���$A_i,A_j$������Ϊ$B_i-B_j$������������лᱻ�ֳ�$A_i$���������ɶΣ���ÿ��$B_i$�ݼ���
���$A_i$�п�����ͬ�������Ȱ�$A_i$��ɻ�����ͬ������ͬ��λ���ϵ����Ƶ��������ε��Ҷ˵�$+1$�������鼯ά�������ٽ���ͬ���Ĳ�����

����$A_i$���ձ����$A_i'$����$B_i$����󱻷ŵ���$A_i'$λ��ȥ�������Ƿ���$i$�Ĺ��׾���$(A_i'-A_i)\times B_i$��Ҳ�����������Ĺ�����$\sum_i A_i'\times B_i-\sum_i A_i\times B_i$����������ֻ��Ҫ�ڰ�$B_i$����Ĺ�����ά��ÿ��Ԫ���µ�λ�ü����ף���ʵά��λ�þ���ά�����������е�������ֱ�Ӳ��뼴�ɣ���
������ǣ�����һ�������Σ���$B_i$Ϊ�±꽨�߶��������$B_i$�ǵݼ��ģ�����ÿ������Ĺ��׾��ǣ�$�������\sum B_i\times �������Ԫ�ظ���$����Ȼ��ֻ�Ƕ�����������ı�Ĺ��ף����������廹�� $��������˵�\times\sum B_i$�Ĺ��ף���

����һ��$A_i$ʱ�����ܰ����������κϲ���һ�𡣰�ԭ�����������εĹ��׼�����Ȼ���߶����ϲ����Σ��ټ��Ϻϲ���ĶεĹ��׼��ɡ�

���Ӷ�$O(n\log n)$��Ϊɶ$Tutorial$��д����$O(n\log^2n)$...��ûϸ��...����

ע�������СҪ��$4e5$������$2e5$����ֵ�������
������WA 8���ҷ����������һ����ʱ�򣬻�������RE��= = ��������
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=4e5+3;//4e5 not 2e5!

int fa[N],R[N],root[N];
LL Ans;
struct Segment_Tree
{
	#define ls son[x][0]
	#define rs son[x][1]
	#define lson ls,l,m
	#define rson rs,m+1,r
	#define S N*20
	int tot,sz[S],son[S][2];
	LL sum[S];
	#undef S
	#define Update(x) sz[x]=sz[ls]+sz[rs], sum[x]=sum[ls]+sum[rs]
	void Insert(int &x,int l,int r,int pos)
	{
		if(!x) x=++tot;
		if(l==r) {sz[x]=1, sum[x]=pos; return;}
		int m=l+r>>1;
		pos<=m ? Insert(lson,pos) : Insert(rson,pos);
		Update(x);
	}
	int Merge(int x,int y)
	{
		if(!x||!y) return x|y;
		Ans-=sum[ls]*sz[rs]+sum[son[y][0]]*sz[son[y][1]];
		ls=Merge(ls,son[y][0]), rs=Merge(rs,son[y][1]);
		Ans+=sum[ls]*sz[rs], sz[x]+=sz[y], sum[x]+=sum[y];// Update(x); ��ҪдUpdate...����Ȼ�����ܹ���
		return x;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
int Find(int x)
{
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Merge(int x,int y)
{
	x=Find(x), y=Find(y), fa[y]=x;
	Ans-=T.sum[root[x]]*x+T.sum[root[y]]*y;
	root[x]=T.Merge(root[x],root[y]);
	Ans+=T.sum[root[x]]*x;
	R[x]=R[y];
}

int main()
{
	const int n=read();
	for(int i=1; i<N; ++i) R[i]=i, fa[i]=i;
	for(int i=1; i<=n; ++i)
	{
		int a=read(),b=read(),p=root[a]?R[Find(a)]+1:a;
		Ans-=1ll*a*b, T.Insert(root[p],1,n,b), Ans+=1ll*p*b;
		if(root[p-1]) Merge(p-1,p);
		if(root[p+1]) Merge(p,p+1);
		printf("%I64d\n",Ans);
	}

	return 0;
}
