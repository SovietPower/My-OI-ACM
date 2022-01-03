/*
6696kb	10744ms
$Description$
长度为n的数列，m次询问，每次询问一段区间最大的A_i*tm_i(重要度*出现次数) 
$Solution$
好像可以用莫队做，但是取max的操作普通莫队是不好撤销的(Subd部分) 
于是可以用不带删除的莫队: 回滚莫队 
询问依旧是按(左端点所在块，右端点)排序 
1.对于同在一块的询问，暴力查询，最差O(sqrt(n)) 
2.对于不在同一块的询问(左端点ql在左边，右端点qr在右边的某块) 
我们对左端点相同的询问一起考虑，这时r一定是单调递增的 
令l为下一块的开头，r为当前块的最右端点 
先将r移动到当前询问qr处(只需要加入元素)，记录当前答案bef=Now；
然后将l向左移动到ql处，统计答案，得到ans[i]；
然后将l重新从ql移动到之前的l处，消除刚才询问的影响，然后Now=bef。
这样对于每次块的询问，r最多每次移动O(n),总O(nsqrt(n))；对于每次询问，l最多移动O(sqrt(n))，总O(msqrt(n)) 

对于每一块别忘清空tm与Now，回滚只是消除的l的影响 
tm[],ref[]开longlong后真的相当慢 
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
//#define gc() getchar()
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=1e5+5,MAXIN=2e6;

int n,m,size,A[N],ref[N],tm[N],bel[N],B_tm[N];
LL Ans[N],Now;
char IN[MAXIN],*SS=IN,*TT=IN;
struct Ask
{
	int l,r,id;
	bool operator <(const Ask &a)const{
		return bel[l]==bel[a.l]?r<a.r:bel[l]<bel[a.l];
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x,int r)
{
	int l=1,mid;
	while(l<r)
		if(ref[mid=l+r>>1]>=x) r=mid;
		else l=mid+1;
	return l;
}
void Discrete()
{
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i],cnt);
}
inline void Add(int p){
	Now=std::max(Now,1ll*++tm[p]*ref[p]);
}
inline void Subd(int p){
	--tm[p];
}
LL Query_Bits(int l,int r)
{
	LL mx=0;
	for(int i=l; i<=r; ++i)
		mx=std::max(mx,1ll*++B_tm[A[i]]*ref[A[i]]);
	for(int i=l; i<=r; ++i) --B_tm[A[i]];
//	while(sk[0]) B_tm[sk[sk[0]--]]=0;//快不了多少 
	return mx;
}
int Update(int i,int blo)
{
	int r=std::min(blo*size,n),l=r+1,L=l;
	memset(tm,0,sizeof tm);
	Now=0;//置0！
	for(; bel[q[i].l]==blo; ++i)
	{
		if(bel[q[i].l]==bel[q[i].r]) Ans[q[i].id]=Query_Bits(q[i].l,q[i].r);
		else
		{
			while(r<q[i].r) Add(A[++r]);
			LL bef=Now;
			while(l>q[i].l) Add(A[--l]);
			Ans[q[i].id]=Now;
			while(l<L) Subd(A[l++]);
			Now=bef;
		}
	}
	return i;
}

int main()
{
	n=read(),m=read(),size=sqrt(n);
	for(int i=1; i<=n; ++i) bel[i]=(i-1)/size+1;
	Discrete();
	for(int i=1; i<=m; ++i) q[i].l=read(),q[i].r=read(),q[i].id=i;
	std::sort(q+1,q+1+m);
	for(int now=1,i=1; i<=bel[n]; ++i) now=Update(now,i);
	for(int i=1; i<=m; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
