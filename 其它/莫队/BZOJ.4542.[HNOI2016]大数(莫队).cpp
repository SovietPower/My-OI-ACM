/*
大数除法是很麻烦的，考虑能不能将其条件化简 
一段区间[l,r]|p，即num[l,r]|p，类似前缀，记后缀suf[i]表示[i,n]的这段区间代表的数字 
于是有 suf[l]-suf[r+1]|p  ->  (suf[l]-suf[r+1])%p = 0  ->  suf[l] ≡suf[r+1](mod p) 
即若suf[r+1]%p = suf[l]%p，则num[l,r]|p 
于是我们可以把范围控制在p以内，查找是否有%p相等的区间 -> 莫队 
任意两对模数相同的都是+1，即小Z的袜子 
这样的实际意义是 (suf[l]-suf[r+1])*10^{n-r}%p = 0 
后面有个10的幂，如果n-r>0 对于p(p|10)显然无论[l,r]是什么都会满足条件 
于是p=2,5时要换一种判断方式。显然若有一位A[i]满足A[i]|p，则之前的A[j](包括A[i]自己)都可以以它为结尾并对答案做出贡献 
若数列(都加l-1)a,b,c,d,e中，A[a,d,e]|p，则答案为e+d+a-3*(l-1) 
这个在线做就可以了 (另外有人知道这个我莫队为什么不对吗。。)

另外要注意p范围不定，要对出现的余数离散化 
然后参数p和模数p会重着 要注意！读p别忘longlong 
要注意会有A[n+1]，离散化要注意这个变量默认0！
另外p<P时特判为什么不对。。
*/
#include <cmath>
#include <cctype>
#include <cstdio>
#include <algorithm>
#define gc() getchar()
typedef long long LL;
const int N=2e5+5,P=1e6;

int n,m,size,tm[P+5],Cnt;
LL p/*LL!*/,A[N],suf[N],ref[N],Now,Ans[N],sum[N],num[N];
struct Ask
{
	int l,r,id;
	bool operator <(const Ask &a)const {
		return l/size==a.l/size?r<a.r:l/size<a.l/size;
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
inline void Update(int pos,int delta){
	if(!(A[pos]%p)) Now+=delta*pos, Cnt+=delta;
}
void Spec()
{
	for(int i=1; i<=n; ++i)
		if(A[i]%p) sum[i]=sum[i-1],num[i]=num[i-1];
		else sum[i]=sum[i-1]+i,num[i]=num[i-1]+1;
	for(LL l,r,i=1; i<=m; ++i)
		l=read(),r=read(), printf("%lld\n",sum[r]-sum[l-1]-(num[r]-num[l-1])*(l-1));
//	for(int l=1,r=0,i=1; i<=m; ++i)
//	{
//		while(l<q[i].l) Update(l,-1),++l;
//		while(l>q[i].l) --l,Update(l,1);
//		while(r<q[i].r) ++r,Update(r,1);
//		while(r>q[i].r) Update(r,-1),--r;
//		Ans[q[i].id]=Now-Cnt*(q[i].l-1);
//	}
}
inline void Add(int p){
	if(!p) return;
	Now+=tm[p], ++tm[p];
//	if(++tm[p]>1) Now+=tm[p]-1;//不要判什么tm[]>1之类满足才更新答案，因为tm[]在中间过程是可以存在负数的 
}
inline void Subd(int p){
	if(!p) return;
	--tm[p], Now-=tm[p];
//	if(--tm[p]) Now-=tm[p];//这一写法效果一样(因为只判了!=0) 但不能这么写 
}
void Normal()
{
	for(int l=1,r=0,i=1; i<=m; ++i)
	{
		while(l<q[i].l) Subd(suf[l++]);
		while(l>q[i].l) Add(suf[--l]);
		while(r<q[i].r) Add(suf[++r]);
		while(r>q[i].r) Subd(suf[r--]);
		Ans[q[i].id]=Now;
	}
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
	for(int i=1; i<=n; ++i) ref[i]=suf[i];
	std::sort(ref+1,ref+1+n);
	int cnt=1;
	for(int i=2; i<=n; ++i)
		if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) suf[i]=Find(suf[i],cnt);
	suf[n+1]=ref[1]?0:1;
}

int main()
{
	scanf("%lld",&p);
	char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);A[++n]=c-'0',c=gc());
	m=read(), size=sqrt(n);
	if(p==2||p==5) {Spec(); return 0;}
	for(int i=1; i<=m; ++i)
		q[i].l=read(),q[i].r=read()+1,q[i].id=i;//q:r+1
	LL pw10=1;//longlong! 
	for(int i=n; i; --i)
		suf[i]=(A[i]*pw10%p+suf[i+1])%p, pw10=pw10*10%p;
//	if(p>P) Discrete();//这个if？
	Discrete();
	std::sort(q+1,q+1+m);
//	if(p==2||p==5) Spec();
//	else Normal();
	Normal();
	for(int i=1; i<=m; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
