/*
6696kb	10744ms
$Description$
����Ϊn�����У�m��ѯ�ʣ�ÿ��ѯ��һ����������A_i*tm_i(��Ҫ��*���ִ���) 
$Solution$
���������Ī����������ȡmax�Ĳ�����ͨĪ���ǲ��ó�����(Subd����) 
���ǿ����ò���ɾ����Ī��: �ع�Ī�� 
ѯ�������ǰ�(��˵����ڿ飬�Ҷ˵�)���� 
1.����ͬ��һ���ѯ�ʣ�������ѯ�����O(sqrt(n)) 
2.���ڲ���ͬһ���ѯ��(��˵�ql����ߣ��Ҷ˵�qr���ұߵ�ĳ��) 
���Ƕ���˵���ͬ��ѯ��һ���ǣ���ʱrһ���ǵ��������� 
��lΪ��һ��Ŀ�ͷ��rΪ��ǰ������Ҷ˵� 
�Ƚ�r�ƶ�����ǰѯ��qr��(ֻ��Ҫ����Ԫ��)����¼��ǰ��bef=Now��
Ȼ��l�����ƶ���ql����ͳ�ƴ𰸣��õ�ans[i]��
Ȼ��l���´�ql�ƶ���֮ǰ��l���������ղ�ѯ�ʵ�Ӱ�죬Ȼ��Now=bef��
��������ÿ�ο��ѯ�ʣ�r���ÿ���ƶ�O(n),��O(nsqrt(n))������ÿ��ѯ�ʣ�l����ƶ�O(sqrt(n))����O(msqrt(n)) 

����ÿһ��������tm��Now���ع�ֻ��������l��Ӱ�� 
tm[],ref[]��longlong������൱�� 
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
//	while(sk[0]) B_tm[sk[sk[0]--]]=0;//�첻�˶��� 
	return mx;
}
int Update(int i,int blo)
{
	int r=std::min(blo*size,n),l=r+1,L=l;
	memset(tm,0,sizeof tm);
	Now=0;//��0��
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
