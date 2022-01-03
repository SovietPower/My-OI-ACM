/*
26132kb	15528ms
**Ī�� ǰ׺�� ����ջ��**�������⣬����O2 70�֣���O2~~�Լ�BZOJ����ʱ��~~����A��
��������һ��[HNOI2016 ����](https://www.cnblogs.com/SovietPower/p/10286483.html)������������Ҳ����ô���Ļ����о������ǵ���ļ�ǿ�档��Ϊ���Ҫ��ά���öණ������
������������׷���������Ҫά��ʲô�ˡ���������Ҫ��$[l,r-1]$ת�Ƶ�$[l,r]$�������ҵ��������ֵ$p$��λ�ã�Ȼ��$[l,p]$֮��Ĺ��׺ܺ��㣬ά������ǰ׺�ͱ�ʾǰ��/����ĵ����������У���������ж��ٸ����鷳����$[p+1,r]$�����...
�տ�ʼ�������ά������ǰ׺�ͣ���ѯ��ʱ����һ��$[L[r]+1,r-1]$��$L[x]$Ϊ$x$��ߵ�һ����$A_x$��������е����ֵ����ͬ��ͳ��һ�¡�
Ȼ��ϸ������ô�࣬д+����3h������LOJ����O2��T��һ����= =����ȵ����ˣ��ж�����
�Ա�[$mjt$�Ĵ���](https://www.cnblogs.com/mjtcn/p/10072954.html)���֣�orz����Ī��ת�Ƶ�ʱ�����һ�β�ѯ��СֵӰ���ر�󡣡�
�������뷢��һ��ǰ׺�;Ϳ��ԣ�Ȼ���ָ�+��~~+��~~��2h=-=�������ܵıȽϿ���~~����O2Ҳ��$70$����~~��$mjt$$30$��2333����
���Ǻܺý��ͣ����ܺ���⣬ֻ��ϸ�����⡣��
���Ӷ�$O(n\sqrt n)$��
*/
#include <cmath>
#include <cstdio>
#include <cctype>
#include <algorithm>
//#define gc() getchar()
#define MAXIN 300000
#define gc() (SS==TT&&(TT=(SS=IN)+fread(IN,1,MAXIN,stdin),SS==TT)?EOF:*SS++)
typedef long long LL;
const int N=2e5+5,INF=1<<30;

int P1,P2,bel[N],A[N],ref[N],st[18][N],Log[N],sk[N],L[N],R[N],sl[N],sr[N];
char IN[MAXIN],*SS=IN,*TT=IN;
struct Quries
{
	int l,r,id;
	bool operator <(const Quries &x)const
	{
		return bel[l]==bel[x.l]?r<x.r:bel[l]<bel[x.l];
	}
}q[N];

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-48,c=gc());
	return now;
}
inline int Query(int l,int r)//return pos
{
	int k=Log[r-l+1];
	return ref[std::max(st[k][l],st[k][r-(1<<k)+1])];//��дA[x]>A[y]?x:y ��0.4s+...
}
void Init_ST(const int n)
{
	for(int i=2; i<=n; ++i) Log[i]=Log[i>>1]+1;
	for(int j=1; j<=Log[n]; ++j)
		for(int t=1<<j-1,i=n-t; i; --i)
			st[j][i]=std::max(st[j-1][i],st[j-1][i+t]);
}
inline LL UpdL(int l,int r)
{
	if(l==r) return 0;
	int p=Query(l+1,r),R=std::min(p,::R[l]),tot=R-l,num=sl[l+1]-sl[R]+1;
	return (LL)num*P1+(tot-num)*P2+(R<p?(sl[R]-sl[p])*P2:(::R[l]>r)?(r-p)*P2:0);
}
inline LL UpdR(int l,int r)
{
	if(l==r) return 0;
	int p=Query(l,r-1),L=std::max(p,::L[r]),tot=r-L,num=sr[r-1]-sr[L]+1;
	return (LL)num*P1+(tot-num)*P2+(L>p?(sr[L]-sr[p])*P2:(::L[r]<l)?(p-l)*P2:0);
}

int main()
{
	static LL Ans[N];

//	freopen("sf.in","r",stdin);
//	freopen("sf.out","w",stdout);

	const int n=read(),Q=read(),P1=read(),P2=read(),size=sqrt(n); ::P1=P1,::P2=P2;
	for(int i=1; i<=n; ++i) st[0][i]=A[i]=read(), ref[A[i]]=i, bel[i]=i/size;
	for(int i=1; i<=Q; ++i) q[i]=(Quries){read(),read(),i};
	std::sort(q+1,q+1+Q);

	Init_ST(n);
	A[sk[0]=0]=INF;
	for(int i=1,top=0; i<=n; ++i)//sr[i]:�ݼ��������У�i����ж��ٸ���������� sr2[i]:����2 
	{
		while(A[sk[top]]<=A[i]) --top;//R[sk[top--]]=i;
		sr[i]=sr[L[i]=sk[top]]+1, sk[++top]=i;//sr2[i]=sr2[sk[top]]+(i-sk[top]-1)*P2+P1,
	}
	A[sk[0]=n+1]=INF;
	for(int i=n,top=0; i; --i)
	{
		while(A[sk[top]]<=A[i]) --top;//L[sk[top--]]=i;
		sl[i]=sl[R[i]=sk[top]]+1, sk[++top]=i;//sl2[i]=sl2[sk[top]]+(sk[top]-i-1)*P2+P1,
	}
	LL Now=0;
	for(int l=1,r=0,i=1; i<=Q; ++i)
	{
		int ln=q[i].l,rn=q[i].r;
		while(l>ln) Now+=UpdL(--l,r);
		while(r<rn) Now+=UpdR(l,++r);
		while(l<ln) Now-=UpdL(l++,r);
		while(r>rn) Now-=UpdR(l,r--);
		Ans[q[i].id]=Now;
	}
	for(int i=1; i<=Q; printf("%lld\n",Ans[i++]));

	return 0;
}
