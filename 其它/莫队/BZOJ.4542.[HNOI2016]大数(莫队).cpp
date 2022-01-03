/*
���������Ǻ��鷳�ģ������ܲ��ܽ����������� 
һ������[l,r]|p����num[l,r]|p������ǰ׺���Ǻ�׺suf[i]��ʾ[i,n]����������������� 
������ suf[l]-suf[r+1]|p  ->  (suf[l]-suf[r+1])%p = 0  ->  suf[l] ��suf[r+1](mod p) 
����suf[r+1]%p = suf[l]%p����num[l,r]|p 
�������ǿ��԰ѷ�Χ������p���ڣ������Ƿ���%p��ȵ����� -> Ī�� 
��������ģ����ͬ�Ķ���+1����СZ������ 
������ʵ�������� (suf[l]-suf[r+1])*10^{n-r}%p = 0 
�����и�10���ݣ����n-r>0 ����p(p|10)��Ȼ����[l,r]��ʲô������������ 
����p=2,5ʱҪ��һ���жϷ�ʽ����Ȼ����һλA[i]����A[i]|p����֮ǰ��A[j](����A[i]�Լ�)����������Ϊ��β���Դ��������� 
������(����l-1)a,b,c,d,e�У�A[a,d,e]|p�����Ϊe+d+a-3*(l-1) 
����������Ϳ����� (��������֪�������Ī��Ϊʲô�����𡣡�)

����Ҫע��p��Χ������Ҫ�Գ��ֵ�������ɢ�� 
Ȼ�����p��ģ��p������ Ҫע�⣡��p����longlong 
Ҫע�����A[n+1]����ɢ��Ҫע���������Ĭ��0��
����p<Pʱ����Ϊʲô���ԡ���
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
//	if(++tm[p]>1) Now+=tm[p]-1;//��Ҫ��ʲôtm[]>1֮������Ÿ��´𰸣���Ϊtm[]���м�����ǿ��Դ��ڸ����� 
}
inline void Subd(int p){
	if(!p) return;
	--tm[p], Now-=tm[p];
//	if(--tm[p]) Now-=tm[p];//��һд��Ч��һ��(��Ϊֻ����!=0) ��������ôд 
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
//	if(p>P) Discrete();//���if��
	Discrete();
	std::sort(q+1,q+1+m);
//	if(p==2||p==5) Spec();
//	else Normal();
	Normal();
	for(int i=1; i<=m; ++i) printf("%lld\n",Ans[i]);

	return 0;
}
