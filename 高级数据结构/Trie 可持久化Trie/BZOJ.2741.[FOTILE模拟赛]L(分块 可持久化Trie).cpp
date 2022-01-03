/*
11020kb	8232ms
���ȼ�sumΪǰ׺���ͣ���ô����s[l,r]=sum[l-1]^sum[r]����һ���������Ϳ���תΪ�������������͡�
��ô��[l,r]��ѯ�ʼ���[l-1,r]��ĳ�������������ֵ��
������ĳһ��������֪��һ�����������ֵ�����ÿɳ־û�Trie O(logv)��������Ծ���ȷ��һ���������������������ֵ��
�������ݷ�Χ�������ǿ��Էֿ顣
��head[i]��ʾ��i��Ŀ�ͷλ�ã�Max(l,r,x)��ʾx��[l,r]��ĳһ�����������ֵ��f[i][j]��ʾ�ӵ�i��Ŀ�ʼ��λ��j��ĳ�������������ֵ�Ƕ��١�
��ô f[i][j] = max(f[i-1][j-1], Max(head[i], j-1, A[j]))��������$O(nsqrt(n)logv)$ʱ����Ԥ������A[]��ǰ׺�ͣ�
��ѯ��ʱ����x��ʾl����ĵ�һ�飬��l,r��ͬһ����� ans = Max(l, r, A[i]), i��[l,r]�����԰� ���Լ����Ҳûʲô���壩
���� ans = max(f[x][r], Max(l, r, A[i]))��i��[l,begin[x]-1]��
��[1,r]��ѯ�ʣ����ܻ���ͬ��һ��һ���ı߽����⣨�������0������A[0]=0Ҳ��һ������ˡ���
���Ӷ�ͬ��$O(qsqrt(n)logv)$��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
#define MAXIN 500000//Ϊʲô50000WA+TLE�� QAQ 
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
#define BIT 30
typedef long long LL;
const int N=12005,M=111;

int root[N],A[N],bel[N],H[N],f[M][N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Trie
{
	#define S N*32
	int tot,son[S][2],sz[S];
	void Insert(int x,int y,int v)
	{
		for(int i=BIT; ~i; --i)
		{
			int c=v>>i&1;
			son[x][c]=++tot, son[x][c^1]=son[y][c^1];
			x=tot, y=son[y][c];
			sz[x]=sz[y]+1;
		}
	}
	int Query(int x,int y,int v)
	{
		int res=0;
		for(int i=BIT; ~i; --i)
		{
			int c=(v>>i&1)^1;
			if(sz[son[y][c]]-sz[son[x][c]]>0)
				x=son[x][c], y=son[y][c], res|=1<<i;
			else
				c^=1, x=son[x][c], y=son[y][c];
		}
		return res;
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}

int main()
{
	int n=read(),Q=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i)
		bel[i]=(i-1)/size+1, T.Insert(root[i]=++T.tot,root[i-1],A[i]=A[i-1]^read());//^����+ == 

	H[1]=1;
	for(int i=2,lim=bel[n]; i<=lim; ++i) H[i]=H[i-1]+size;
	for(int i=1,lim=bel[n]; i<=lim; ++i)
		for(int j=H[i]+1,rtl=root[H[i]-1]; j<=n; ++j)
			f[i][j]=std::max(f[i][j-1],T.Query(rtl,root[j-1],A[j]));

	for(int l,r,x,y,ans=0; Q--; )
	{
		x=((LL)read()+ans)%n+1, y=((LL)read()+ans)%n+1;//read()%n+ans%n �����ܱ�int����and LLҪ���������档��
		l=std::min(x,y), r=std::max(x,y);
		--l, ans=0;
		if(bel[l]==bel[r])
			for(int i=l,rtl=root[std::max(0,l-1)],rtr=root[r]; i<=r; ++i)
				ans=std::max(ans,T.Query(rtl,rtr,A[i]));
		else
		{
			ans=f[bel[l]+1][r];
			for(int i=l,lim=H[bel[l]+1]-1,rtl=root[std::max(0,l-1)],rtr=root[r]; i<=lim; ++i)
				ans=std::max(ans,T.Query(rtl,rtr,A[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
