/*
439ms	46MB
$Description$
ÿ��λ����һ��$3\times3$�ľ���Ҫ��֧�����丳ֵ��������˻���
$n,q\leq10^5$��

$Solution$
����߶���+�����������$O(3^3q\log^2n)$�ģ���Ϊά������˵Ļ������丳ֵΪ����$A$��ʱ��Ҫ��ֵ$A^{r-l+1}$����һ�������ݡ�
������ô���Ǹ�������ȥ�������ֶ��ڳ���Ϊ$n$���߶��������䳤��ֻ��$O(\log n)$�֣�����Ԥ�����$A$��������ݣ�ֱ�Ӹ�ֵ��
��ͬ����ĳ��ȿ��ܱȽ��ң����ǰ��߶������Ȳ���$2^k$���ͺ�����ά���ˡ�
���Ӷ�$O(3^3(n+q)\log n)$��
д�������Ĵ��봿����...
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
#define mod 998244353
#define gc() getchar()
#define MAXIN 300000
//#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=(1<<17)+7,M=1e5+5,BIT=17;

int ref[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read();
struct Matrix
{
	int a[3][3];
	inline void Read()
	{
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j) a[i][j]=read();
	}
	Matrix operator *(const Matrix &x)
	{
		Matrix res;
		for(int i=0; i<3; ++i)
			for(int j=0; j<3; ++j)
			{
				LL tmp=0;
				for(int k=0; k<3; ++k) tmp+=1ll*a[i][k]*x.a[k][j]%mod;
				res.a[i][j]=tmp%mod;
			}
		return res;
	}
}A[N],pw[M][BIT+1];
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int tag[S];
	Matrix t[S];
	#undef S
	#define Upd(rt,id,l) t[rt]=pw[id][ref[l]], tag[rt]=id
	#define Update(rt) t[rt]=t[ls]*t[rs]
	inline void PushDown(int rt,int m)
	{
		Upd(ls,tag[rt],m>>1), Upd(rs,tag[rt],m>>1), tag[rt]=0;
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {t[rt]=A[l]; return;}
		int m=l+r>>1; Build(lson), Build(rson), Update(rt);
	}
	void Modify(int l,int r,int rt,int L,int R,int id)
	{
		if(L<=l && r<=R) {Upd(rt,id,r-l+1); return;}
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m) Modify(lson,L,R,id);
		if(m<R) Modify(rson,L,R,id);
		Update(rt);
	}
	Matrix Query(int l,int r,int rt,int L,int R)
	{
		if(L<=l && r<=R) return t[rt];
		if(tag[rt]) PushDown(rt,r-l+1);
		int m=l+r>>1;
		if(L<=m)
			if(m<R) return Query(lson,L,R)*Query(rson,L,R);
			else return Query(lson,L,R);
		return Query(rson,L,R);
	}
}T;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}

int main()
{
	#define S 1,lim,1
	int n=read()-1,Q=read(),lim=1,bit=0;
	for(int i=1; i<=n; ++i) A[i].Read();
	while(lim<n) lim<<=1, ++bit;
	for(int i=0; i<=bit; ++i) ref[1<<i]=i;
	T.Build(S);
	for(int t=0; Q--; )
		switch(read())
		{
			case 1:
			{
				int l=read(),r=read(); pw[++t][0].Read();
				for(int i=1; i<=bit; ++i) pw[t][i]=pw[t][i-1]*pw[t][i-1];
				T.Modify(S,l,r,t); break;
			}
			case 2:
			{
				int l=read(),r=read();
				Matrix res=T.Query(S,l,r-1); LL ans=0;
				for(int i=0; i<3; ++i)
					for(int j=0; j<3; ++j) ans+=res.a[i][j];
				printf("%d\n",(int)(ans%mod)); break;
			}
		}

	return 0;
}
