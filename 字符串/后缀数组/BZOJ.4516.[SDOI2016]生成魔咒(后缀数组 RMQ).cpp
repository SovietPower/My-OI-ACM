/*
13228kb	1000ms
��׺�����ǿ�������: ���ʲ�ͬ���ַ����ĸ���Ϊ $�Ӵ�����-\sum_{ht[i]}$���� $\frac{n(n+1)}{2}-\sum_{ht[i]}$.
�����ÿ������߲����ַ�����ı�SA[]���������ǰ�߲����ַ����൱��ֻ������һ����׺��
�������ߣ���ԭ����������
ÿ�β���һ���ַ���������һ��ǰ׺i�����Ĺ�����$len-max(lcp(pre,i),lcp(i,nxt))$������$pre,nxt$Ϊ���׺$i$(��ǰ)�������ڵ���������
��setά����ǰ��������RMQ��lcp��������д$O(n)$��ά������ջ���������飩
���˼�����׺�����ˣ���Ȼ��ûд��lcp(~~Ҳ����̫����~~)��
$10^5$�����ױ�int!
*/
#include <set>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define gc() getchar()
const int N=1e5+5,B=17;

int n,cnt,A[N],ref[N],tm[N],sa[N],sa2[N],rk[N],ht[N],log2[N],st[N][18];
std::set<int> set_rk;
std::set<int>::iterator it;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
int Find(int x)
{
	int l=1,r=cnt,mid;
	while(l<r)
		if(ref[mid=l+r>>1]<x) l=mid+1;
		else r=mid;
	return l;
}
void Get_SA()
{
	int *x=rk,*y=sa2,m=n+1;
	for(int i=0; i<=m; ++i) tm[i]=0;
	for(int i=1; i<=n; ++i) ++tm[x[i]=A[i]];
	for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
	for(int i=n; i; --i) sa[tm[x[i]]--]=i;
	for(int k=1,p=0; k<n; k<<=1,m=p,p=0)
	{
		for(int i=n-k+1; i<=n; ++i) y[++p]=i;
		for(int i=1; i<=n; ++i) if(sa[i]>k) y[++p]=sa[i]-k;

		for(int i=0; i<=m; ++i) tm[i]=0;
		for(int i=1; i<=n; ++i) ++tm[x[i]];
		for(int i=1; i<=m; ++i) tm[i]+=tm[i-1];
		for(int i=n; i; --i) sa[tm[x[y[i]]]--]=y[i];

		std::swap(x,y), x[sa[1]]=p=1;
		for(int i=2; i<=n; ++i)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p>=n) break;
	}
	for(int i=1; i<=n; ++i) rk[sa[i]]=i;
	ht[1]=0;
	for(int k=0,p,i=1; i<=n; ++i)
	{
		if(rk[i]==1) continue;
		if(k) --k;
		p=sa[rk[i]-1];
		while(i+k<=n && p+k<=n && A[i+k]==A[p+k]) ++k;
		ht[rk[i]]=k;
	}
}
void Init_RMQ()
{
	for(int i=1; i<=n; ++i) st[i][0]=ht[i];
	log2[1]=0;
	for(int i=2; i<=n; ++i) log2[i]=log2[i>>1]+1;
	for(int j=1; j<=log2[n]; ++j)
		for(int i=n-(1<<j-1); i; --i)
			st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
}
int LCP(int l,int r)
{
	if(l>r) std::swap(l,r);
	++l; int k=log2[r-l+1];
	return std::min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) ref[i]=A[i]=read();
	std::sort(ref+1,ref+1+n), cnt=1;
	for(int i=2; i<=n; ++i) if(ref[i]!=ref[i-1]) ref[++cnt]=ref[i];
	for(int i=1; i<=n; ++i) A[i]=Find(A[i]);
//	for(int i=1,lim=n>>1; i<=lim; ++i) std::swap(A[i],A[n-i+1]);//���� ��Ȼд���� ����дreverse��  
	std::reverse(A+1,A+1+n);//reverse����첻�٣� ��ࡣ
	Get_SA(), Init_RMQ();
	long long res=0;
	set_rk.insert(0);
	for(int tmp,i=n; i; --i)//��ͷ��ʼ�����ַ�(ǰ׺)��
	{
		tmp=0, it=set_rk.upper_bound(rk[i]);
		if(it!=set_rk.end()) tmp=LCP(rk[i],*it);
		if((--it)!=set_rk.begin()) tmp=std::max(tmp,LCP(*it,rk[i]));
		res+=n-i+1-tmp, set_rk.insert(rk[i]);
		printf("%lld\n",res);
	}

	return 0;
}
