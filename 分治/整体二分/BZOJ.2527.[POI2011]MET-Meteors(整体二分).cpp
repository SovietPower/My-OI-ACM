/*
20048kb	11292ms
1316ms	24.8MB
$Description$
��$n$�����ң�����һ����$m$���ռ�վ���гɻ���$k$�β���ÿ�ζ�����$[l_i,r_i]$�еĿռ�վ��Ӧ�Ĺ�����ֵ��$a_i$����ÿ������$i$�����ڼ��β�������ֵ$\geq$������$need_i$����ʼΪ$0$����
$n,m,k\leq3\times10^5$��
$Solution$
ÿ�����ҵĴ𰸿��Զ���+��ǰ׺�ͣ����ǿ����뵽������֡�
��ÿ��Solve()��Ҫ�������й��ҵõ���ֵ����ͬλ�õĿռ�վ��Ӧ��ͬ���ұȽ��鷳��
ע�⵽ÿ��Solve()����������������С��صģ�so���ݹ��Ҵ���������¿ռ�վ��ֵ����vectorö�ٶ�Ӧ�ռ�վ�õ�ÿ�����ҵ�ֵ��(or�߱�)
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define lb(x) (x&-x)
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=3e5+5,INF=1e9;

int n,m,K,A[N],Ans[N],q[N],q1[N],q2[N];
std::vector<int> v[N];
char IN[MAXIN],*SS=IN,*TT=IN;
inline int read();
struct Operation
{
	int l,r,v;
	inline void Input(){
		l=read(),r=read(),v=read();
	}
}op[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
namespace T//�����޸� �����ѯ 
{
	int n;
	LL t[N];

	inline void Modify(int p,int v){
		while(p<=n) t[p]+=v, p+=lb(p);
	}
	inline void Modify_Range(int l,int r,int v)
	{
		Modify(l,v), Modify(r+1,-v);
		if(l>r) Modify(1,v);//Modify(n+1,-v)
	}
	inline void Clear(int p)
	{
		for(; p<=n; p+=lb(p))
			if(t[p]) t[p]=0; else break;
	}
	inline void Clear_Range(int l,int r)
	{
		Clear(l), Clear(r+1);//�����ٰ� 
		if(l>r) Clear(1);
	}
	inline LL Query(int p)
	{
		LL res=0; while(p) res+=t[p], p^=lb(p);
		return res;
	}
}
void Solve(int l,int r,int h,int t)
{
	if(h>t) return;
	if(l==r){
		for(int i=h; i<=t; ++i) Ans[q[i]]=l;
		return;
	}
	int mid=l+r>>1, t1=0, t2=0;
	for(int i=l; i<=mid; ++i) T::Modify_Range(op[i].l,op[i].r,op[i].v);
	for(int i=h,now=q[i]; i<=t; now=q[++i])//now:may be q[n+1]
	{
		LL tmp=0;
		for(int j=0,lim=v[now].size(); j<lim; ++j)
			if((tmp+=T::Query(v[now][j]))>=A[now]) break;//tmp���ܱ�longlong��������Ҳ�Ǹ���֦��
		if(tmp>=A[now]) q1[t1++]=now;
		else A[now]-=tmp, q2[t2++]=now;
	}
	for(int i=l; i<=mid; ++i) T::Clear_Range(op[i].l,op[i].r);//T::Modify_Range(op[i].l,op[i].r,-op[i].v);
	//T::Clear(op[i].l), T::Clear(op[i].r);//T::Clear(std::min(op[i].l,op[i].r));//��Ϊ��l>r�����������Ҫ��յ�λ�ñȽ��鷳������һ�е����ֶ��Ǵ�ġ�(����Ӧ��r+1)
	for(int i=0; i<t1; ++i) q[h+i]=q1[i];
	for(int i=0; i<t2; ++i) q[h+t1+i]=q2[i];
	Solve(l,mid,h,h+t1-1), Solve(mid+1,r,h+t1,t);
}

int main()
{
	n=read(),T::n=m=read();
	for(int i=1; i<=m; ++i) v[read()].push_back(i);
	for(int i=1; i<=n; ++i) A[i]=read(), q[i]=i;
	K=read();
	for(int i=1; i<=K; ++i) op[i].Input();
	op[++K]=(Operation){m+1,m+1,0};
	Solve(1,K,1,n);
	for(int i=1; i<=n; ++i) Ans[i]==K?puts("NIE"):printf("%d\n",Ans[i]);

	return 0;
}
