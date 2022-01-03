/*
8152kb	1656ms
�����$1$��ʼ����ÿ��ʱ��$t_i$��ȥ$i$����ȡ����$\max\{t_i-i\}$����ȡ�����ֵ��λ����$p$������$t_p+1+n-1-p=\max\{t_i-i\}+1+n-1$��
�ѻ��������ÿ��ѯ�ʾͿ���$O(n)$���ˣ��������ڣ���

������ôά���𰸣�$\min\limits_{i=1}^n\{\max\limits_{j=i}^{i+n-1}\{t_j-j\}+i\}+n-1$��
�ſ�һ����������$Ans=\min\limits_{i=1}^n\{\max\limits_{j=i}^{2n}\{t_j-j\}+i\}+n-1$�����߶���ά������$\max\{t_i-i\}$����Ҫ���Ǹ���׺���ֵ�����Ժϲ���ʱ����һ���������������Ĺ���ά��$\min$�Ϳ����ˣ�ͬ[BZOJ2957]¥���ؽ�����Ȼûд��...����
���壺ά������$\max\{t_i-i\}$����Сֵ$ans[rt]$����Сֵ��ʱֻ���ǵ�ǰ�ڵ���������������Ӱ�죩���ϲ���ʱ����ֵ�ǰ����������ֵ$val$��Ӱ�쵽��������ĸ�λ�ã�����������ĳ��$mx[rson]\geq val$���������׺���ֵ��Ӱ�����$mx[rson]$��ֱ����$ans[rt]$����һ��Ȼ��ݹ������䣻�������������Сֵ����$val+mid+1$���ݹ������䡣
������Ҳ���ԣ��ҵ���һ��$>val$��λ��$p$��Ȼ����$val+p+1$��$p$֮ǰ��$ans$���´𰸣�

����ע�⵽���Ĵ𰸾�����$[n+1,2n]$�����ֵ��$[1,n]$�ж��ֵõ��ģ���$[n+1,2n]$�����ֵ����$[1,n]$�����ֵ$-n$������ֻά��$[1,n]$���߶����Ϳ����ˣ���ѯ��ʱ����$[1,n]$�����ֵ$-n$��$[1,n]$����һ�¡�

���Ӷ�$O(n\log^2n)$��
*/
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int tm[N];
char IN[MAXIN],*SS=IN,*TT=IN;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
struct Segment_Tree
{
	#define ls rt<<1
	#define rs rt<<1|1
	#define lson l,m,ls
	#define rson m+1,r,rs
	#define S N<<2
	int ans[S],mx[S];
	#undef S
	int Query(int l,int r,int rt,int val)
	{
		if(l==r) return mx[rt]>val?val+l+1:INF;
		int m=l+r>>1;
		return mx[rs]>val?std::min(ans[rt],Query(rson,val)):Query(lson,val);//�ҵ�һ��>val��λ�� 
//		if(l==r) return l+std::max(mx[rt],val);//both are ok...
//		int m=l+r>>1;
//		return mx[rs]>=val?std::min(ans[rt],Query(rson,val)):std::min(val+m+1,Query(lson,val));//����val��Ӱ�� 
	}
	void Update(int l,int r,int rt)
	{
		mx[rt]=std::max(mx[ls],mx[rs]);
		ans[rt]=Query(l,l+r>>1,ls,mx[rs]);
	}
	void Build(int l,int r,int rt)
	{
		if(l==r) {/*ans[rt]=tm[l],*/ mx[rt]=tm[l]-l; return;}
		int m=l+r>>1;
		Build(lson), Build(rson), Update(l,r,rt);
	}
	void Modify(int l,int r,int rt,int p,int v)
	{
		if(l==r) {/*ans[rt]=v,*/ mx[rt]=v-l; return;}
		int m=l+r>>1;
		p<=m ? Modify(lson,p,v) : Modify(rson,p,v);
		Update(l,r,rt);
	}
}T;

int main()
{
//	freopen("circle.in","r",stdin);
//	freopen("circle.out","w",stdout);

	const int n=read(),m=read(),P=read();
	for(int i=1; i<=n; ++i) tm[i]=read();
	T.Build(1,n,1);
	int ans; printf("%d\n",ans=T.Query(1,n,1,T.mx[1]-n)+n-1);
	for(int i=1; i<=m; ++i)
	{
		int x=read(),y=read();
		if(P) x^=ans, y^=ans;
		T.Modify(1,n,1,x,y);
		printf("%d\n",ans=T.Query(1,n,1,T.mx[1]-n)+n-1);
	}

	return 0;
}
